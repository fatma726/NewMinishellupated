#!/bin/bash

echo "=== Minishell File Descriptor Testing ==="
echo

# Compile the minishell
echo "1. Compiling minishell..."
make clean
make

if [ $? -ne 0 ]; then
    echo "❌ Compilation failed!"
    exit 1
fi
echo "✅ Compilation successful"
echo

# Test 1: Basic command
echo "2. Testing basic command (ls)..."
echo "ls" | timeout 5s ./minishell &
MINISHELL_PID=$!
sleep 1
echo "Minishell PID: $MINISHELL_PID"
echo "Open file descriptors:"
lsof -p $MINISHELL_PID 2>/dev/null | grep -E "(FD|pts|pipe)" || echo "No file descriptors found"
wait $MINISHELL_PID
echo

# Test 2: Pipe command
echo "3. Testing pipe command (ls | wc)..."
echo "ls | wc" | timeout 5s ./minishell &
MINISHELL_PID=$!
sleep 1
echo "Minishell PID: $MINISHELL_PID"
echo "Open file descriptors:"
lsof -p $MINISHELL_PID 2>/dev/null | grep -E "(FD|pts|pipe)" || echo "No file descriptors found"
wait $MINISHELL_PID
echo

# Test 3: Redirection
echo "4. Testing redirection (ls > test_output.txt)..."
echo "ls > test_output.txt" | timeout 5s ./minishell &
MINISHELL_PID=$!
sleep 1
echo "Minishell PID: $MINISHELL_PID"
echo "Open file descriptors:"
lsof -p $MINISHELL_PID 2>/dev/null | grep -E "(FD|pts|pipe)" || echo "No file descriptors found"
wait $MINISHELL_PID
echo

# Test 4: Error command
echo "5. Testing error command (invalidcommand123)..."
echo "invalidcommand123" | timeout 5s ./minishell &
MINISHELL_PID=$!
sleep 1
echo "Minishell PID: $MINISHELL_PID"
echo "Open file descriptors:"
lsof -p $MINISHELL_PID 2>/dev/null | grep -E "(FD|pts|pipe)" || echo "No file descriptors found"
wait $MINISHELL_PID
echo

# Test 5: Valgrind check
echo "6. Running Valgrind file descriptor check..."
echo "ls" | valgrind --track-fds=yes --leak-check=full --show-leak-kinds=all ./minishell 2>&1 | grep -E "(FILE DESCRIPTORS|Open file descriptor)" || echo "No file descriptor leaks detected"
echo

# Cleanup
rm -f test_output.txt
echo "=== Testing Complete ==="
