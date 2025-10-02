#!/bin/bash

# File Descriptor Monitor for Minishell
# This script monitors file descriptors during minishell execution

echo "=== Minishell File Descriptor Monitor ==="
echo

# Function to monitor FDs
monitor_fds() {
    local test_name="$1"
    local command="$2"
    
    echo "Testing: $test_name"
    echo "Command: $command"
    
    # Start minishell in background
    echo "$command" | ./minishell &
    local minishell_pid=$!
    
    # Wait a moment for it to start
    sleep 0.5
    
    # Check file descriptors
    echo "File descriptors for PID $minishell_pid:"
    lsof -p $minishell_pid 2>/dev/null | awk 'NR==1 || /pts|pipe|REG/ {print}' || echo "No file descriptors found"
    
    # Wait for completion
    wait $minishell_pid 2>/dev/null
    
    echo "---"
    echo
}

# Test cases
monitor_fds "Basic Command" "ls"
monitor_fds "Pipe Command" "ls | wc"
monitor_fds "Output Redirection" "ls > test_output.txt"
monitor_fds "Error Command" "invalidcommand123"
monitor_fds "Complex Pipe" "ls | head -5 | wc"

# Cleanup
rm -f test_output.txt

echo "=== Monitoring Complete ==="
