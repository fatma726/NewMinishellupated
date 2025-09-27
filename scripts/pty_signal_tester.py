#!/usr/bin/env python3
import os
import pty
import select
import signal
import sys
import time

# Simple PTY-based signal tester for minishell/minishell_bonus.
# Usage: scripts/pty_signal_tester.py ./minishell   or   ./minishell_bonus

READ_CHUNK = 4096
TIMEOUT = 2.0

def read_until(fd, substr, timeout=TIMEOUT):
    buf = b""
    end = time.time() + timeout
    while time.time() < end:
        r, _, _ = select.select([fd], [], [], 0.05)
        if fd in r:
            try:
                chunk = os.read(fd, READ_CHUNK)
            except OSError:
                break
            if not chunk:
                break
            buf += chunk
            if substr in buf:
                return buf
    return buf

def write_str(fd, s):
    os.write(fd, s.encode())

def send_ctrl(fd, ch):
    # Map to control character (e.g., 'C' -> 0x03)
    code = ord(ch.upper()) - ord('@')
    os.write(fd, bytes([code]))

def run_shell(shell_path):
    pid, master_fd = pty.fork()
    if pid == 0:
        os.execv(shell_path, [shell_path])
        os._exit(127)
    return pid, master_fd

def wait_child(pid, timeout=TIMEOUT):
    end = time.time() + timeout
    while time.time() < end:
        try:
            wpid, status = os.waitpid(pid, os.WNOHANG)
        except ChildProcessError:
            return True, 0
        if wpid == pid:
            if os.WIFEXITED(status):
                return True, os.WEXITSTATUS(status)
            if os.WIFSIGNALED(status):
                return True, 128 + os.WTERMSIG(status)
        time.sleep(0.05)
    return False, None

def test_ctrl_c_at_prompt(fd):
    send_ctrl(fd, 'C')
    out = read_until(fd, b"$ ", timeout=1.0)
    write_str(fd, "echo $?\n")
    out2 = read_until(fd, b"\n", timeout=1.0)
    return b"130" in out2

def test_ctrl_c_sleep(fd):
    write_str(fd, "sleep 5\n")
    time.sleep(0.2)
    send_ctrl(fd, 'C')
    out = read_until(fd, b"$ ", timeout=1.5)
    write_str(fd, "echo $?\n")
    out2 = read_until(fd, b"\n", timeout=1.0)
    return b"130" in out2

def test_ctrl_bs_prompt(fd):
    # Ctrl-\ should be ignored at prompt (no Quit: 3)
    send_ctrl(fd, '\\')
    out = read_until(fd, b"$ ", timeout=0.5)
    return b"Quit: 3" not in out

def test_ctrl_bs_cat(fd):
    write_str(fd, "cat\n")
    read_until(fd, b"\n", timeout=0.5)  # give it a moment
    send_ctrl(fd, '\\')
    out = read_until(fd, b"$ ", timeout=1.5)
    return b"Quit: 3" in out

def test_ctrl_d_exit(fd, pid):
    # produce non-zero last status
    write_str(fd, "false\n")
    read_until(fd, b"$ ", timeout=0.8)
    # send EOF
    send_ctrl(fd, 'D')
    ok, status = wait_child(pid, timeout=1.5)
    return ok and status == 1

def main():
    if len(sys.argv) < 2:
        print("Usage: pty_signal_tester.py <path-to-minishell>")
        return 2
    shell_path = sys.argv[1]
    pid, fd = run_shell(shell_path)
    # Let prompt render
    read_until(fd, b"$ ", timeout=1.0)
    results = {
        'Ctrl-C at prompt': test_ctrl_c_at_prompt(fd),
        'Ctrl-C during sleep': test_ctrl_c_sleep(fd),
        'Ctrl-\\ at prompt': test_ctrl_bs_prompt(fd),
        'Ctrl-\\ during cat': test_ctrl_bs_cat(fd),
        'Ctrl-D exit (after false)': test_ctrl_d_exit(fd, pid),
    }
    # If still alive, ask it to exit
    alive, _ = wait_child(pid, timeout=0.1)
    if not alive:
        try:
            write_str(fd, "exit\n")
        except OSError:
            pass
        wait_child(pid, timeout=1.0)
    ok = True
    for name, passed in results.items():
        print(f"{name}: {'OK' if passed else 'FAIL'}")
        ok = ok and passed
    sys.exit(0 if ok else 1)

if __name__ == '__main__':
    main()

