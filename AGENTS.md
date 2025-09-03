# Repository Guidelines

## Project Structure & Modules
- `src/`: C sources
  - `core/`, `cmd/`, `parser/`, `redirection/`, `pipe/`
- `include/`: public headers (`minishell.h`)
- `libs/Libft`: bundled Libft (built by the main Makefile)
- `bonus/`: bonus binary symlink target (`minishell_bonus`)
- `minishell_tester/`: upstream tester helper files
- Update file lists in `Makefile` (`MAIN`, `CMD`, `PARSER`, `REDIR`, `PIPE`) when adding new `.c` files.

## Build, Run, Test
- `make`: builds `minishell` with Libft and Readline.
- `make debug`: AddressSanitizer + `-g` build.
- `make clean|fclean|re`: objects/binary cleanup and full rebuild.
- Run locally: `./minishell` (prompt uses `$PS1`, defaults to `\\s-\\v\\$ `).
- Readline: Makefile auto-detects 42 Homebrew; if missing, it tries to install. Ensure `readline` exists in `~/.brew` or `/opt/homebrew` on macOS.
- Tests: see `README/README.md` for tester details. Common examples:
  - `cd minishell_tester && ./tester`
  - For wildcards: `cd minishell_tester && ./tester wildcards`
  - Some testers require toggling `#define MSTEST_MODE` in `include/minishell.h` (0/1).

## Coding Style & Naming
- Language: C with GCC warnings enabled (see `CFLAGS` in `Makefile`).
- Indentation: tabs; max 80–100 cols preferred; one function per concern.
- Files: `snake_case.c` in `src/<module>/`; headers in `include/`.
- APIs: prefer Libft helpers (`ft_*`) over standard reimplementations.
- Headers: declare prototypes; keep minimal includes; use include guards.

## Testing Guidelines
- No unit harness in-tree; use external testers provided in `README/`.
- When adding features, include minimal repros in `minishell_tester` style (inputs, expected behavior).
- Validate interactive behavior and exit codes. For tester parity, set `MSTEST_MODE` appropriately.

## Commits & Pull Requests
- Commits: concise, imperative, scope-prefixed when possible, e.g. `parser: handle nested quotes`, `cmd/cd: fix OLDPWD`.
- PRs: include summary, scope of change, manual test notes (commands run), and any `MSTEST_MODE` setting used. Add before/after snippets when fixing parsing or exec edge cases.

## Security & Configuration
- Avoid unsafe `exec` paths; resolve via `$PATH` or fallback (`/usr/bin:/bin`).
- Be careful with environment mutation (`PWD`, `OLDPWD`, `SHLVL`, `_`).
- Quote and escape user input consistently; see `parser/` helpers for patterns.
