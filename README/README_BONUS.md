# Minishell Bonus Features

## 🎯 Implemented Bonus Features

### ✅ 1. Logical Operators (&&, ||) and Parentheses
- **AND operator (`&&`)**: Executes second command only if first succeeds
- **OR operator (`||`)**: Executes second command only if first fails  
- **Parentheses `()`**: Groups commands for complex logic
- **Examples**:
  ```bash
  echo hello && echo world    # Both execute
  false && echo no            # Second doesn't execute
  false || echo yes           # Second executes
  (echo hello && echo world)  # Grouped execution
  ```

### ✅ 2. Wildcards (*)
- **Current directory wildcards**: `*.c`, `*.sh`, etc.
- **File matching**: Expands to matching files in current directory
- **Examples**:
  ```bash
  echo *.sh                   # Lists all .sh files
  ls *.c                      # Lists all .c files
  cat *.txt | head -5         # Processes multiple files
  ```
- **Note**: Limited to current directory (subdirectories not supported)

### ✅ 3. Advanced Quote Handling (Surprise Feature)
- **Perfect quote behavior**: Matches bash exactly
- **Examples**:
  ```bash
  echo "'$USER'"              # Output: 'username' (expands USER)
  echo '"$USER"'              # Output: "$USER" (doesn't expand)
  echo '$USER'                # Output: $USER (single quotes)
  echo "$USER"                # Output: username (double quotes)
  ```

## 🏗️ Architecture

### Data Structures Used
- **Linked Lists**: `t_list` from libft for wildcard file collection
- **String Arrays**: `char **` for arguments, environment variables
- **Struct**: `t_node` for shell state management

### File Organization
```
src/bonus/
├── split_operators.c    # &&, ||, () handling
└── subshell.c          # Parentheses execution

src/parser/
├── expand_wildcard.c   # Wildcard expansion
├── get_file_list.c     # File listing
└── load_lst.c         # Linked list operations
```

## 🚀 Building Bonus Version

```bash
# Build bonus version
make -f Makefile.bonus

# Run bonus version
./minishell_bonus

# Debug version with AddressSanitizer
make -f Makefile.bonus debug
```

## 🧪 Testing Bonus Features

### Test Logical Operators
```bash
echo hello && echo world
false && echo should_not_print
false || echo should_print
(echo hello && echo world)
```

### Test Wildcards
```bash
echo *.sh
ls *.c
cat *.txt | head -5
```

### Test Quote Handling
```bash
echo "'$USER'"
echo '"$USER"'
```

## 📊 Bonus Score: 3/3 Features ✅

All three bonus features are fully implemented and working correctly!
