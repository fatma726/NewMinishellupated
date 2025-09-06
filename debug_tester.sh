#!/bin/bash

MINISHELL_PATH="../minishell"
REMOVE_COLORS="sed s/\x1B\[[0-9;]\{1,\}[A-Za-z]//g"
REMOVE_EXIT="grep -v ^exit$"

teste="echo hello world"

echo "Testing command: $teste"
echo "Raw output:"
echo -e "$teste" | $MINISHELL_PATH 2> /dev/null
echo "---"
echo "After REMOVE_COLORS:"
echo -e "$teste" | $MINISHELL_PATH 2> /dev/null | $REMOVE_COLORS
echo "---"
echo "After REMOVE_EXIT:"
echo -e "$teste" | $MINISHELL_PATH 2> /dev/null | $REMOVE_COLORS | $REMOVE_EXIT
echo "---"
echo "Final result:"
MINI_OUTPUT=$(echo -e "$teste" | $MINISHELL_PATH 2> /dev/null | $REMOVE_COLORS | $REMOVE_EXIT)
echo "MINI_OUTPUT: '$MINI_OUTPUT'"
