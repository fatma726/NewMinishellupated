#!/bin/bash

echo "=== File Descriptor Fix Verification ==="
echo

# Check if our fixes are in place
echo "1. Checking for file descriptor leak fixes in cmd_exit.c:"
if grep -q "close(node->backup_stdout)" src/cmd/cmd_exit.c; then
    echo "✅ backup_stdout close found"
else
    echo "❌ backup_stdout close missing"
fi

if grep -q "close(node->backup_stdin)" src/cmd/cmd_exit.c; then
    echo "✅ backup_stdin close found"
else
    echo "❌ backup_stdin close missing"
fi

echo

# Check for proper include
echo "2. Checking for proper includes:"
if grep -q '#include "minishell.h"' src/cmd/cmd_exit.c; then
    echo "✅ minishell.h include found"
else
    echo "❌ minishell.h include missing"
fi

echo

# Check for redundant readline includes
echo "3. Checking for redundant readline includes:"
redundant_files=()
for file in src/cmd/cmd_exit.c src/core/signals.c src/core/input_helpers.c src/core/input.c; do
    if [ -f "$file" ]; then
        if grep -q '#include.*readline' "$file" && grep -q '#include "minishell.h"' "$file"; then
            redundant_files+=("$file")
        fi
    fi
done

if [ ${#redundant_files[@]} -eq 0 ]; then
    echo "✅ No redundant readline includes found"
else
    echo "❌ Redundant readline includes found in:"
    for file in "${redundant_files[@]}"; do
        echo "   - $file"
    done
fi

echo

# Check compilation
echo "4. Testing compilation:"
if make >/dev/null 2>&1; then
    echo "✅ Compilation successful"
else
    echo "❌ Compilation failed"
fi

echo
echo "=== Verification Complete ==="
