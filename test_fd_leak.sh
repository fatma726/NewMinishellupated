#!/bin/bash

# Test script to verify file descriptor leak fix
echo "Testing file descriptor leaks..."

# Compile the minishell
echo "Compiling minishell..."
make clean
make

if [ $? -ne 0 ]; then
    echo "Compilation failed!"
    exit 1
fi

# Test with a simple command that should trigger error paths
echo "Testing with invalid command..."
echo "invalidcommand123" | valgrind --track-fds=yes --leak-check=full --show-leak-kinds=all ./minishell 2>&1 | grep "FILE DESCRIPTORS"

echo "Testing with pipe command..."
echo "ls | invalidcommand123" | valgrind --track-fds=yes --leak-check=full --show-leak-kinds=all ./minishell 2>&1 | grep "FILE DESCRIPTORS"

echo "Testing with redirection error..."
echo "ls > /invalid/path/file" | valgrind --track-fds=yes --leak-check=full --show-leak-kinds=all ./minishell 2>&1 | grep "FILE DESCRIPTORS"

echo "Test completed. Check output above for file descriptor leaks."
