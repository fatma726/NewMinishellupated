#!/bin/bash

# Comprehensive leak-check script with all required valgrind flags
# Based on the systematic testing methodology provided

valgrind --leak-check=full --leak-resolution=high -s --track-origins=yes \
         --num-callers=500 --show-mismatched-frees=yes --show-leak-kinds=all \
         --track-fds=yes --trace-children=yes --gen-suppressions=no \
         --error-limit=no --undef-value-errors=yes --expensive-definedness-checks=yes \
         --malloc-fill=0x41 --free-fill=0x42 --read-var-info=yes --keep-debuginfo=yes \
         --suppressions="$PWD/bin.supp" --suppressions="$PWD/readline.supp" \
         "$@"
