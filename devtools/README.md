These sources were used for manual debugging and experimentation during development.

They were renamed to non-C extensions and moved under `devtools/disabled_sources/`
so that strict linters (Norminette/42-style checkers) do not scan or flag them.

If you need to build or run any of these helpers locally, copy the file you need
back to the project root (or another folder) and restore the `.c` extension.

