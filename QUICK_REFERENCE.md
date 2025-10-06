# Memory Leak Fixes - Quick Reference

## What Was Fixed

### 1. File Descriptor Leak (src/pipe/pipe_utils.c)
**Problem:** Unclosed dup'd FDs on error paths  
**Fix:** Added `backup_restor()` + `close()` calls in `repeat()` error paths  
**Lines:** 73-77, 81-87

### 2. Memory Leak in Operator Parsing (bonus/src/bonus/split_operators_main.c)
**Problem:** String `s` not freed on 5 error paths  
**Fix:** Added `free(s)` before all early returns  
**Functions:** `split_operators_after_index()` and `split_operators()`  
**Lines:** 104, 110, 117, 124, 145

## How to Verify

```bash
# Build
make fclean && make bonus

# Run verification script
chmod +x verify_leak_fixes.sh
./verify_leak_fixes.sh

# Or test manually (Linux with valgrind only)
echo 'cd | echo test && exit' | ./leak-check.sh ./minishell_bonus 2>&1
echo '()' | ./leak-check.sh ./minishell_bonus 2>&1
cat minishell_bonus | ./leak-check.sh ./minishell_bonus 2>&1
```

## Expected Results

✅ `definitely lost: 0 bytes in 0 blocks`  
✅ `still reachable: 0 bytes in 0 blocks`  
✅ `FILE DESCRIPTORS: 8 open (3 std) at exit`

## Files Changed

1. `src/pipe/pipe_utils.c` - FD leak fixes
2. `bonus/src/bonus/split_operators_main.c` - Memory leak fixes

## Key Pattern Applied

**Before:**
```c
if (error)
    return (envp);  // LEAK!
```

**After:**
```c
if (error)
{
    free(allocated_memory);
    close(opened_fd);
    return (envp);
}
```

## Documentation

- Full details: `MEMORY_LEAK_FIXES.md`
- Verification script: `verify_leak_fixes.sh`
- Original guide: See user-provided methodology

