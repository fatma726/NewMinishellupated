#!/bin/bash

# Quick Valgrind test using Docker
cd "/Users/fatmtahmdabrahym/Downloads/minishell-main-35 15"

echo "🔍 Running Valgrind with exact flags in Docker..."
echo ""

# Build Docker image first
echo "Building Docker image..."
docker build -t minishell-valgrind . > /dev/null 2>&1

echo "Running Valgrind with your exact flags:"
echo 'valgrind --tool=memcheck \'
echo '         --leak-check=full \'  
echo '         --show-leak-kinds=all \'
echo '         --track-origins=yes \'
echo '         --track-fds=yes \'
echo '         --suppressions=bin.supp \'
echo '         --suppressions=readline.supp \'
echo '         ./minishell "echo hello"'
echo ""
echo "Output:"

# Run the exact command you wanted
docker run --rm -it \
    -v "$(pwd):/workspace" \
    -w /workspace \
    minishell-valgrind \
    bash -c 'echo "echo hello" | valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all --track-origins=yes --track-fds=yes --suppressions=bin.supp --suppressions=readline.supp ./minishell'
