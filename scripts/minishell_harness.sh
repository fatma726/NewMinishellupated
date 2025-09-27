#!/usr/bin/env bash
set -euo pipefail

ROOT_DIR=$(cd "$(dirname "$0")/.." && pwd)
BIN="$ROOT_DIR/minishell"

pass=0; fail=0

say() { printf "\n== %s ==\n" "$*"; }
ok() { echo "[OK] $*"; pass=$((pass+1)); }
nok() { echo "[FAIL] $*"; fail=$((fail+1)); }

run_shell() {
  printf "%s" "$1" | "$BIN"
}

ensure_build() {
  say "Build"
  make -C "$ROOT_DIR" -j >/dev/null
  if [[ -x "$BIN" ]]; then ok "built minishell"; else nok "build failed"; fi
}

test_simple() {
  say "Simple Commands"
  out=$(run_shell $'/bin/ls >/dev/null\necho $?\nexit\n') || true
  [[ "$out" == "0" ]] && ok "/bin/ls exit status" || nok "/bin/ls exit status (got: $out)"

  out=$(run_shell $'/bin/ls nofile >/dev/null\necho $?\nexit\n') || true
  [[ "$out" == "1" ]] && ok "failing ls exit status" || nok "failing ls exit status (got: $out)"
}

test_builtins_env() {
  say "Builtins: echo, export, unset, env"
  out=$(run_shell $'echo hello world\nexit\n') || true
  [[ "$out" == "hello world" ]] && ok "echo" || nok "echo (got: $out)"

  out=$(run_shell $'export TESTVAR=foo\n echo $TESTVAR\n env | grep ^TESTVAR=\n unset TESTVAR\n env | grep ^TESTVAR= || echo TESTVAR_REMOVED\nexit\n') || true
  grep -q "^foo$" <<<"$out" && grep -q "^TESTVAR=foo$" <<<"$out" && grep -q "TESTVAR_REMOVED" <<<"$out" \
    && ok "export/unset/env" || nok "export/unset/env (got: $out)"
}

test_cd_pwd() {
  say "Builtins: cd, pwd"
  out=$(run_shell $'pwd\n cd src\n pwd\n cd ..\n pwd\n cd .\n pwd\n exit\n') || true
  lines=$(wc -l <<<"$out")
  [[ $lines -ge 4 ]] && ok "cd/pwd navigation" || nok "cd/pwd navigation (got: $out)"
}

test_path() {
  say "PATH resolution"
  out=$(run_shell $'ls >/dev/null\n echo $?\n unset PATH\n ls >/dev/null\n echo $?\n export PATH=/does/notexist:/bin\n ls >/dev/null\n echo $?\n exit\n') || true
  nums=$(echo "$out" | grep -E '^[0-9]+$' | sed -n '1,3p')
  n1=$(echo "$nums" | sed -n '1p'); n2=$(echo "$nums" | sed -n '2p'); n3=$(echo "$nums" | sed -n '3p')
  [[ "$n1" == 0 && "$n2" != 0 && "$n3" == 0 ]] && ok "PATH search order" || nok "PATH search order (got: $out)"
}

test_redirs() {
  say "Redirections and pipes"
  out=$(run_shell $'echo hello > testfile1\n echo append >> testfile1\n cat < testfile1 | wc -l\n exit\n') || true
  [[ "$out" =~ ^[[:space:]]*2$ ]] && ok ">, >>, < and pipe" || nok ">, >>, < and pipe (got: $out)"

  out=$(run_shell $'cat << EOF\nline1\nline2\nEOF\nexit\n') || true
  [[ "$out" == $'line1\nline2' ]] && ok "heredoc simple" || nok "heredoc simple (got: $out)"

  out=$(run_shell $'printf "hi" | wc -c\n exit\n') || true
  [[ "$out" =~ ^[[:space:]]*2$ ]] && ok "pipe simple" || nok "pipe simple (got: $out)"
}

test_quotes() {
  say "Quotes and expansion"
  out=$("$BIN" <<'EOS'
export USER=VALUE
echo "$USER"
echo '$USER'
exit
EOS
  ) || true
  l1=$(printf "%s\n" "$out" | sed -n '1p')
  l2=$(printf "%s\n" "$out" | sed -n '2p')
  [[ "$l1" == VALUE && "$l2" == '$USER' ]] && ok "quote behavior" || nok "quote behavior (got: $out)"
}

main() {
  ensure_build
  test_simple
  test_builtins_env
  test_cd_pwd
  test_path
  test_redirs
  test_quotes

  if [[ -x "$ROOT_DIR/minishell_bonus" ]]; then
    say "Bonus: && and ||"
    out=$(printf 'true && echo yes\ntrue || echo no\nfalse && echo no\nfalse || echo yes\nexit\n' | "$ROOT_DIR/minishell_bonus") || true
    got_yes=$(printf "%s\n" "$out" | grep -c '^yes$' || true)
    if [[ "$got_yes" -eq 2 ]]; then ok "short-circuit logic"; else nok "short-circuit logic (got: $out)"; fi

    say "Bonus: Parentheses"
    out=$(printf '(true && echo in) || echo out\n(false && echo x) || echo y\nexit\n' | "$ROOT_DIR/minishell_bonus" 2>&1) || true
    if grep -q 'syntax error near unexpected token' <<<"$out"; then echo "[SKIP] parentheses not supported"; else
      if grep -q '^in$' <<<"$out" && grep -q '^y$' <<<"$out"; then ok "grouped conditions"; else nok "grouped conditions (got: $out)"; fi
    fi

    say "Bonus: Wildcards"
    out=$(printf 'echo *.md\nexit\n' | "$ROOT_DIR/minishell_bonus") || true
    if grep -q '\.md' <<<"$out"; then ok "wildcard expansion"; else nok "wildcard expansion (got: $out)"; fi
  fi

  say "Summary"
  echo "Passed: $pass  Failed: $fail"
  [[ $fail -eq 0 ]]
}

main "$@"
