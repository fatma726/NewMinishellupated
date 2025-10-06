#!/bin/bash
# Comprehensive Memory Leak Test Suite for Minishell
# Based on the systematic testing methodology

echo "=========================================="
echo "Minishell Memory Leak Test Suite"
echo "=========================================="
echo ""

ulimit -n 1024
echo "Set FD limit to 1024"
echo ""

EXECUTABLE="./minishell_bonus"
LEAK_CHECK="./leak-check.sh"

# Test Case 0: File Descriptor Leak Test
echo "=== Test Case 0: FD Leak Test (cd | echo rfrfrf && exit) ==="
echo 'cd | echo rfrfrf && exit' | $LEAK_CHECK $EXECUTABLE 2>&1 | grep -E "(definitely lost|still reachable|FILE DESCRIPTORS|All heap)"
echo ""

# Test Case 1: Empty Parentheses (Still Reachable Memory)
echo "=== Test Case 1: Empty Subshell () ==="
echo '()' | $LEAK_CHECK $EXECUTABLE 2>&1 | grep -E "(definitely lost|still reachable|All heap)"
echo ""

# Test Case 3: Baseline (No Leak Expected)
echo "=== Test Case 3: Baseline (exit) ==="
echo 'exit' | $LEAK_CHECK $EXECUTABLE 2>&1 | grep -E "(definitely lost|still reachable|All heap)"
echo ""

# Test Case 4: Binary Input (Definite Memory Leaks)
echo "=== Test Case 4: Binary Input ==="
cat $EXECUTABLE | $LEAK_CHECK $EXECUTABLE 2>&1 | tail -20 | grep -E "(definitely lost|still reachable|All heap)"
echo ""

# Test Case 5: Syntax Error Handling
echo "=== Test Case 5: Syntax Error ==="
echo '> ienfcoino oinf o4n >$poincpin && ()' | $LEAK_CHECK $EXECUTABLE 2>&1 | grep -E "(definitely lost|still reachable|All heap|syntax error)"
echo ""

echo "=========================================="
echo "Test Suite Completed"
echo "=========================================="

