#!/bin/bash

echo "Testing heredoc with * delimiter..."
echo -e "<< *\n*\n" | ./minishell_bonus
echo "Exit code: $?"
