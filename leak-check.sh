#!/bin/bash

# macOS-native leak checking script using AddressSanitizer and native tools
# Usage: ./leak-check.sh <program> [arguments...]

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
PURPLE='\033[0;35m'
NC='\033[0m' # No Color

# Check if program is provided
if [ $# -eq 0 ]; then
    echo -e "${YELLOW}Usage: $0 <program> [arguments...]${NC}"
    echo "Example: $0 ./minishell"
    echo "Example: $0 ./minishell \"echo hello\""
    echo ""
    echo -e "${BLUE}This script provides several leak checking methods for macOS:${NC}"
    echo "1. AddressSanitizer (recommended)"
    echo "2. macOS native 'leaks' command"
    echo "3. Compilation with sanitizer flags"
    exit 1
fi

echo -e "${BLUE}🔍 macOS Leak Detection Toolkit${NC}"
echo -e "${BLUE}Program: $1${NC}"
if [ $# -gt 1 ]; then
    echo -e "${BLUE}Arguments: ${@:2}${NC}"
fi
echo ""

PROGRAM=$1
shift
ARGS="$@"

# Check if the program exists
if [ ! -f "$PROGRAM" ]; then
    echo -e "${RED}Error: Program '$PROGRAM' not found${NC}"
    exit 1
fi

echo -e "${PURPLE}═══ Method 1: AddressSanitizer Check ═══${NC}"
echo -e "${BLUE}Checking if program was compiled with AddressSanitizer...${NC}"

# Check if program has AddressSanitizer
if otool -L "$PROGRAM" 2>/dev/null | grep -q "libclang_rt.asan"; then
    echo -e "${GREEN}✅ AddressSanitizer detected! Running with ASAN...${NC}"
    export ASAN_OPTIONS="detect_leaks=1:abort_on_error=1:print_stats=1"
    export MSAN_OPTIONS="print_stats=1"
    
    if [ -n "$ARGS" ]; then
        echo "$ARGS" | $PROGRAM
    else
        $PROGRAM
    fi
    ASAN_EXIT_CODE=$?
    
    if [ $ASAN_EXIT_CODE -eq 0 ]; then
        echo -e "${GREEN}✅ No memory errors detected by AddressSanitizer${NC}"
    else
        echo -e "${RED}❌ AddressSanitizer detected issues (exit code: $ASAN_EXIT_CODE)${NC}"
    fi
else
    echo -e "${YELLOW}⚠️  Program not compiled with AddressSanitizer${NC}"
    echo -e "${BLUE}To enable AddressSanitizer, recompile with:${NC}"
    echo -e "  ${YELLOW}CC=\"clang -fsanitize=address -fsanitize=leak -g\" make clean && make${NC}"
fi

echo ""
echo -e "${PURPLE}═══ Method 2: macOS Native Leak Detection ═══${NC}"

# Run the program in background to get its PID
echo -e "${BLUE}Starting program to check for leaks...${NC}"

if [ -n "$ARGS" ]; then
    (echo "$ARGS" | $PROGRAM) &
else
    $PROGRAM &
fi

PROGRAM_PID=$!
sleep 2  # Give the program time to start

# Check if process is still running
if kill -0 $PROGRAM_PID 2>/dev/null; then
    echo -e "${BLUE}Running 'leaks' command on PID: $PROGRAM_PID${NC}"
    leaks $PROGRAM_PID
    LEAKS_EXIT_CODE=$?
    
    # Stop the program
    kill $PROGRAM_PID 2>/dev/null
    wait $PROGRAM_PID 2>/dev/null
    
    if [ $LEAKS_EXIT_CODE -eq 0 ]; then
        echo -e "${GREEN}✅ No leaks detected by macOS leaks command${NC}"
    else
        echo -e "${RED}❌ Leaks detected (exit code: $LEAKS_EXIT_CODE)${NC}"
    fi
else
    echo -e "${YELLOW}⚠️  Program exited too quickly for leak detection${NC}"
fi

echo ""
echo -e "${PURPLE}═══ Method 3: Static Analysis Recommendations ═══${NC}"
echo -e "${BLUE}For comprehensive leak detection, consider:${NC}"
echo ""
echo -e "${YELLOW}1. Recompile with AddressSanitizer:${NC}"
echo -e "   make clean"
echo -e "   CC=\"clang -fsanitize=address -fsanitize=leak -g -O1\" make"
echo ""
echo -e "${YELLOW}2. Use Xcode Instruments:${NC}"
echo -e "   instruments -t Leaks -D trace.trace $PROGRAM"
echo ""
echo -e "${YELLOW}3. Use static analysis:${NC}"
echo -e "   clang --analyze src/**/*.c"
echo ""
echo -e "${BLUE}📝 Note: Valgrind is not available on macOS (Apple Silicon)${NC}"
echo -e "${BLUE}AddressSanitizer is the recommended tool for leak detection${NC}"
