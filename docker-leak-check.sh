#!/bin/bash

# Docker-based leak checking script using Valgrind with suppression files
# Usage: ./docker-leak-check.sh [minishell_command...]

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
PURPLE='\033[0;35m'
NC='\033[0m' # No Color

echo -e "${BLUE}🐳 Docker + Valgrind Leak Detection${NC}"
echo -e "${BLUE}═══════════════════════════════════${NC}"

# Get the current directory (project root)
PROJECT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

echo -e "${YELLOW}Building Docker image with Valgrind...${NC}"

# Build Docker image
docker build -t minishell-valgrind . || {
    echo -e "${RED}❌ Failed to build Docker image${NC}"
    exit 1
}

echo -e "${GREEN}✅ Docker image built successfully${NC}"
echo ""

# Prepare the Valgrind command
VALGRIND_FLAGS="--tool=memcheck \
    --leak-check=full \
    --show-leak-kinds=all \
    --track-origins=yes \
    --track-fds=yes \
    --suppressions=bin.supp \
    --suppressions=readline.supp"

# If arguments provided, use them; otherwise run interactively
if [ $# -gt 0 ]; then
    MINISHELL_COMMAND="$@"
    echo -e "${BLUE}Running command: ${YELLOW}$MINISHELL_COMMAND${NC}"
    echo -e "${BLUE}Valgrind flags: ${YELLOW}$VALGRIND_FLAGS${NC}"
    echo ""
    
    # Run with specific command
    docker run --rm -it \
        -v "$PROJECT_DIR:/workspace" \
        -w /workspace \
        minishell-valgrind \
        bash -c "make clean && make && echo '$MINISHELL_COMMAND' | valgrind $VALGRIND_FLAGS ./minishell"
else
    echo -e "${BLUE}Running interactive mode...${NC}"
    echo -e "${YELLOW}You can run commands like:${NC}"
    echo -e "  valgrind $VALGRIND_FLAGS ./minishell"
    echo -e "${YELLOW}Or test specific commands:${NC}"
    echo -e "  echo 'ls | grep minishell' | valgrind $VALGRIND_FLAGS ./minishell"
    echo ""
    
    # Run interactive Docker container
    docker run --rm -it \
        -v "$PROJECT_DIR:/workspace" \
        -w /workspace \
        minishell-valgrind \
        bash
fi

echo ""
echo -e "${BLUE}📝 Note: This uses the suppression files:${NC}"
echo -e "  - ${YELLOW}bin.supp${NC} (Linux system libraries)"
echo -e "  - ${YELLOW}readline.supp${NC} (readline library)"
echo -e "${BLUE}Only real leaks from your minishell should be shown.${NC}"
