#!/bin/bash

echo "=== Valgrind File Descriptor Testing ==="
echo

# Test cases that should trigger different code paths
test_cases=(
    "ls"                    # Basic command
    "ls | wc"              # Pipe
    "ls > test.txt"        # Output redirection
    "cat < /dev/null"      # Input redirection
    "invalidcommand123"    # Error command
    "echo hello | grep h"  # Pipe with grep
    "ls | head -5 | wc"    # Multiple pipes
)

for test_case in "${test_cases[@]}"; do
    echo "Testing: $test_case"
    echo "$test_case" | valgrind --track-fds=yes --leak-check=full --show-leak-kinds=all ./minishell 2>&1 | grep -E "(FILE DESCRIPTORS|Open file descriptor|definitely lost|indirectly lost)" || echo "✅ No leaks detected"
    echo "---"
done

# Cleanup
rm -f test.txt
echo "=== Valgrind Testing Complete ==="
