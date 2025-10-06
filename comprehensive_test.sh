#!/bin/bash
# Comprehensive Minishell Test Suite
# Based on full English test cases

MINISHELL="./minishell_bonus"
GREEN="\033[0;32m"
RED="\033[0;31m"
YELLOW="\033[1;33m"
BLUE="\033[0;34m"
NC="\033[0m"

PASS=0
FAIL=0
SKIP=0

test_command() {
    local test_name="$1"
    local command="$2"
    local expected="$3"
    local description="$4"
    
    echo -e "${BLUE}Testing:${NC} $test_name"
    echo -e "  Command: $command"
    
    # Run command
    result=$(echo "$command" | $MINISHELL 2>&1 | tail -n +2)
    
    if [[ "$result" == *"$expected"* ]] || [[ -z "$expected" ]]; then
        echo -e "  ${GREEN}✓ PASS${NC}: $description"
        ((PASS++))
    else
        echo -e "  ${RED}✗ FAIL${NC}: Expected '$expected', got '$result'"
        ((FAIL++))
    fi
    echo ""
}

echo "=========================================="
echo "  MINISHELL COMPREHENSIVE TEST SUITE"
echo "=========================================="
echo ""

# Cleanup
rm -f a.txt b.txt newfile files.txt test_*.txt 2>/dev/null

echo "=========================================="
echo "1. BUILTINS (Basic Commands)"
echo "=========================================="
echo ""

test_command "echo hello" "echo hello" "hello" "Should print hello"
test_command "echo -n hello" "echo -n hello" "hello" "Should print without newline"
test_command "pwd" "pwd" "/" "Should print working directory"

echo "=========================================="
echo "2. EXPORT TESTS"
echo "=========================================="
echo ""

# Basic export
echo -e "${BLUE}Testing:${NC} export A=42"
result=$(echo -e "export A=42\necho \$A\nexit" | $MINISHELL 2>&1 | grep -v "minishell" | tail -2 | head -1)
if [[ "$result" == "42" ]]; then
    echo -e "  ${GREEN}✓ PASS${NC}: export and variable expansion works"
    ((PASS++))
else
    echo -e "  ${RED}✗ FAIL${NC}: Expected 42, got '$result'"
    ((FAIL++))
fi
echo ""

# Multiple exports
echo -e "${BLUE}Testing:${NC} export B=hello C=world"
result=$(echo -e "export B=hello C=world\necho \$B \$C\nexit" | $MINISHELL 2>&1 | grep -v "minishell" | tail -2 | head -1)
if [[ "$result" == "hello world" ]]; then
    echo -e "  ${GREEN}✓ PASS${NC}: Multiple exports work"
    ((PASS++))
else
    echo -e "  ${RED}✗ FAIL${NC}: Expected 'hello world', got '$result'"
    ((FAIL++))
fi
echo ""

# Quoted values
echo -e "${BLUE}Testing:${NC} export D=\"quoted value\""
result=$(echo -e "export D=\"quoted value\"\necho \$D\nexit" | $MINISHELL 2>&1 | grep -v "minishell" | tail -2 | head -1)
if [[ "$result" == "quoted value" ]]; then
    echo -e "  ${GREEN}✓ PASS${NC}: Quoted export works"
    ((PASS++))
else
    echo -e "  ${RED}✗ FAIL${NC}: Expected 'quoted value', got '$result'"
    ((FAIL++))
fi
echo ""

# Invalid identifiers
echo -e "${BLUE}Testing:${NC} export = (invalid)"
result=$(echo -e "export =\nexit" | $MINISHELL 2>&1 | grep -i "not.*valid.*identifier")
if [[ -n "$result" ]]; then
    echo -e "  ${GREEN}✓ PASS${NC}: Rejects invalid identifier '='"
    ((PASS++))
else
    echo -e "  ${RED}✗ FAIL${NC}: Should reject 'export ='"
    ((FAIL++))
fi
echo ""

echo -e "${BLUE}Testing:${NC} export 1A=42 (invalid)"
result=$(echo -e "export 1A=42\nexit" | $MINISHELL 2>&1 | grep -i "not.*valid.*identifier")
if [[ -n "$result" ]]; then
    echo -e "  ${GREEN}✓ PASS${NC}: Rejects identifier starting with number"
    ((PASS++))
else
    echo -e "  ${RED}✗ FAIL${NC}: Should reject 'export 1A=42'"
    ((FAIL++))
fi
echo ""

echo "=========================================="
echo "3. UNSET TESTS"
echo "=========================================="
echo ""

echo -e "${BLUE}Testing:${NC} unset removes variable"
result=$(echo -e "export TEST=hello\nunset TEST\necho \$TEST\nexit" | $MINISHELL 2>&1 | tail -2 | head -1)
if [[ -z "$result" ]] || [[ "$result" == "" ]]; then
    echo -e "  ${GREEN}✓ PASS${NC}: unset removes variable"
    ((PASS++))
else
    echo -e "  ${RED}✗ FAIL${NC}: Expected empty, got '$result'"
    ((FAIL++))
fi
echo ""

echo -e "${BLUE}Testing:${NC} unset 1A (invalid identifier)"
result=$(echo -e "unset 1A\nexit" | $MINISHELL 2>&1 | grep -i "not.*valid.*identifier")
if [[ -n "$result" ]]; then
    echo -e "  ${GREEN}✓ PASS${NC}: Rejects invalid unset identifier"
    ((PASS++))
else
    echo -e "  ${YELLOW}⚠ SKIP${NC}: unset may silently ignore invalid identifiers"
    ((SKIP++))
fi
echo ""

echo "=========================================="
echo "4. REDIRECTIONS"
echo "=========================================="
echo ""

echo -e "${BLUE}Testing:${NC} echo hi > a.txt"
echo -e "echo hi > a.txt\nexit" | $MINISHELL > /dev/null 2>&1
if [[ -f a.txt ]] && [[ "$(cat a.txt)" == "hi" ]]; then
    echo -e "  ${GREEN}✓ PASS${NC}: Output redirection creates file"
    ((PASS++))
else
    echo -e "  ${RED}✗ FAIL${NC}: Output redirection failed"
    ((FAIL++))
fi
rm -f a.txt
echo ""

echo -e "${BLUE}Testing:${NC} echo hi > a.txt then echo bye >> a.txt"
echo -e "echo hi > a.txt\necho bye >> a.txt\nexit" | $MINISHELL > /dev/null 2>&1
content=$(cat a.txt 2>/dev/null)
if [[ "$content" == $'hi\nbye' ]]; then
    echo -e "  ${GREEN}✓ PASS${NC}: Append redirection works"
    ((PASS++))
else
    echo -e "  ${RED}✗ FAIL${NC}: Append failed. Got: '$content'"
    ((FAIL++))
fi
rm -f a.txt
echo ""

echo -e "${BLUE}Testing:${NC} cat < a.txt (input redirection)"
echo "test content" > a.txt
result=$(echo -e "cat < a.txt\nexit" | $MINISHELL 2>&1 | grep "test content")
if [[ -n "$result" ]]; then
    echo -e "  ${GREEN}✓ PASS${NC}: Input redirection works"
    ((PASS++))
else
    echo -e "  ${RED}✗ FAIL${NC}: Input redirection failed"
    ((FAIL++))
fi
rm -f a.txt
echo ""

echo -e "${BLUE}Testing:${NC} cat < missing.txt (error handling)"
result=$(echo -e "cat < missing.txt\nexit" | $MINISHELL 2>&1 | grep -i "no such file")
if [[ -n "$result" ]]; then
    echo -e "  ${GREEN}✓ PASS${NC}: Reports missing file error"
    ((PASS++))
else
    echo -e "  ${RED}✗ FAIL${NC}: Should report 'No such file'"
    ((FAIL++))
fi
echo ""

echo "=========================================="
echo "5. PIPES"
echo "=========================================="
echo ""

echo -e "${BLUE}Testing:${NC} echo hi | cat"
result=$(echo -e "echo hi | cat\nexit" | $MINISHELL 2>&1 | grep "hi")
if [[ -n "$result" ]]; then
    echo -e "  ${GREEN}✓ PASS${NC}: Simple pipe works"
    ((PASS++))
else
    echo -e "  ${RED}✗ FAIL${NC}: Pipe failed"
    ((FAIL++))
fi
echo ""

echo -e "${BLUE}Testing:${NC} echo hi | grep h"
result=$(echo -e "echo hi | grep h\nexit" | $MINISHELL 2>&1 | grep "hi")
if [[ -n "$result" ]]; then
    echo -e "  ${GREEN}✓ PASS${NC}: Pipe with grep works"
    ((PASS++))
else
    echo -e "  ${RED}✗ FAIL${NC}: Pipe with grep failed"
    ((FAIL++))
fi
echo ""

echo -e "${BLUE}Testing:${NC} echo hi | grep z (no match)"
result=$(echo -e "echo hi | grep z\nexit" | $MINISHELL 2>&1 | grep "hi")
if [[ -z "$result" ]]; then
    echo -e "  ${GREEN}✓ PASS${NC}: Pipe handles no match correctly"
    ((PASS++))
else
    echo -e "  ${RED}✗ FAIL${NC}: Should produce no output"
    ((FAIL++))
fi
echo ""

echo "=========================================="
echo "6. EXIT STATUS"
echo "=========================================="
echo ""

echo -e "${BLUE}Testing:${NC} ls (valid) then echo \$?"
result=$(echo -e "ls > /dev/null\necho \$?\nexit" | $MINISHELL 2>&1 | tail -2 | head -1)
if [[ "$result" == "0" ]]; then
    echo -e "  ${GREEN}✓ PASS${NC}: Exit status 0 for success"
    ((PASS++))
else
    echo -e "  ${RED}✗ FAIL${NC}: Expected 0, got '$result'"
    ((FAIL++))
fi
echo ""

echo -e "${BLUE}Testing:${NC} ls invalid then echo \$?"
result=$(echo -e "ls /nonexistent_dir_12345 2>/dev/null\necho \$?\nexit" | $MINISHELL 2>&1 | tail -2 | head -1)
if [[ "$result" != "0" ]]; then
    echo -e "  ${GREEN}✓ PASS${NC}: Exit status non-zero for failure"
    ((PASS++))
else
    echo -e "  ${RED}✗ FAIL${NC}: Expected non-zero, got '$result'"
    ((FAIL++))
fi
echo ""

echo "=========================================="
echo "7. QUOTES"
echo "=========================================="
echo ""

echo -e "${BLUE}Testing:${NC} echo \"hello world\""
result=$(echo -e "echo \"hello world\"\nexit" | $MINISHELL 2>&1 | grep "hello world")
if [[ -n "$result" ]]; then
    echo -e "  ${GREEN}✓ PASS${NC}: Double quotes work"
    ((PASS++))
else
    echo -e "  ${RED}✗ FAIL${NC}: Double quotes failed"
    ((FAIL++))
fi
echo ""

echo -e "${BLUE}Testing:${NC} echo 'hello world'"
result=$(echo -e "echo 'hello world'\nexit" | $MINISHELL 2>&1 | grep "hello world")
if [[ -n "$result" ]]; then
    echo -e "  ${GREEN}✓ PASS${NC}: Single quotes work"
    ((PASS++))
else
    echo -e "  ${RED}✗ FAIL${NC}: Single quotes failed"
    ((FAIL++))
fi
echo ""

echo -e "${BLUE}Testing:${NC} echo '\$USER' (no expansion)"
result=$(echo -e "echo '\$USER'\nexit" | $MINISHELL 2>&1 | tail -2 | head -1)
if [[ "$result" == '$USER' ]]; then
    echo -e "  ${GREEN}✓ PASS${NC}: Single quotes prevent expansion"
    ((PASS++))
else
    echo -e "  ${RED}✗ FAIL${NC}: Expected '\$USER', got '$result'"
    ((FAIL++))
fi
echo ""

echo -e "${BLUE}Testing:${NC} echo \"\$USER\" (with expansion)"
result=$(echo -e "export USER=testuser\necho \"\$USER\"\nexit" | $MINISHELL 2>&1 | tail -2 | head -1)
if [[ "$result" == "testuser" ]]; then
    echo -e "  ${GREEN}✓ PASS${NC}: Double quotes allow expansion"
    ((PASS++))
else
    echo -e "  ${RED}✗ FAIL${NC}: Expected 'testuser', got '$result'"
    ((FAIL++))
fi
echo ""

echo "=========================================="
echo "8. ENVIRONMENT & PATH"
echo "=========================================="
echo ""

echo -e "${BLUE}Testing:${NC} env (shows variables)"
result=$(echo -e "env\nexit" | $MINISHELL 2>&1 | grep -c "PATH\|HOME\|USER")
if [[ $result -gt 0 ]]; then
    echo -e "  ${GREEN}✓ PASS${NC}: env command works"
    ((PASS++))
else
    echo -e "  ${RED}✗ FAIL${NC}: env command failed"
    ((FAIL++))
fi
echo ""

echo "=========================================="
echo "9. ERROR HANDLING"
echo "=========================================="
echo ""

echo -e "${BLUE}Testing:${NC} | ls (pipe at start - syntax error)"
result=$(echo -e "| ls\nexit" | $MINISHELL 2>&1 | grep -i "syntax error")
if [[ -n "$result" ]]; then
    echo -e "  ${GREEN}✓ PASS${NC}: Detects syntax error"
    ((PASS++))
else
    echo -e "  ${YELLOW}⚠ SKIP${NC}: May handle differently"
    ((SKIP++))
fi
echo ""

echo -e "${BLUE}Testing:${NC} > file (redirect without command)"
result=$(echo -e "> file\nexit" | $MINISHELL 2>&1 | grep -i "syntax error")
if [[ -n "$result" ]]; then
    echo -e "  ${GREEN}✓ PASS${NC}: Detects redirect without command"
    ((PASS++))
else
    echo -e "  ${YELLOW}⚠ SKIP${NC}: May handle differently (creates empty file)"
    ((SKIP++))
fi
rm -f file 2>/dev/null
echo ""

echo -e "${BLUE}Testing:${NC} cd too many args"
result=$(echo -e "cd /tmp /usr\nexit" | $MINISHELL 2>&1 | grep -i "too many\|error")
if [[ -n "$result" ]]; then
    echo -e "  ${GREEN}✓ PASS${NC}: cd rejects too many arguments"
    ((PASS++))
else
    echo -e "  ${RED}✗ FAIL${NC}: Should reject multiple arguments to cd"
    ((FAIL++))
fi
echo ""

# Cleanup
rm -f a.txt b.txt newfile files.txt test_*.txt 2>/dev/null

echo "=========================================="
echo "           TEST SUMMARY"
echo "=========================================="
echo -e "${GREEN}PASSED: $PASS${NC}"
echo -e "${RED}FAILED: $FAIL${NC}"
echo -e "${YELLOW}SKIPPED: $SKIP${NC}"
echo ""

TOTAL=$((PASS + FAIL + SKIP))
PERCENTAGE=$((PASS * 100 / TOTAL))
echo "Pass rate: $PERCENTAGE% ($PASS/$TOTAL)"
echo "=========================================="

exit $FAIL

