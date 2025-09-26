# minishell

Programs created for the 42 project minishell. The project has been evaluated with a final score of 95/100.

## Description

An attempt at a minimal UNIX shell. This is specifically attempting to immitate the latest version of Bash as of 2024 (Bash 5.2) and as such replicates a number of bashisms. It implements the following shell features as required by the project's PDF:

* Double quote (`"`) escaping.
* Single quote (`'`) escaping.
* Environment variable expansion.
* Pipes (`|`).
* Redirections (`<`, `<<`, `>`, `>>`).
* `cd` as built-in command.
* `echo` as built-in command.
* `env` as built-in command.
* `export` as built-in command.
* `pwd` as built-in command.
* `unset` as built-in command.

Bonus features are documented separately and are not part of the mandatory build.

For fun (non-mandatory), the following features were also implemented:

* Backslash (`\`) escaping.
* Comments (`#`).
* More redirections (`<<<`, `<>`).
* Tilde `~` expansion.
* Semi-colon (`;`) command splitting (non-mandatory).
* Running commands externally with the `-c` argument (removed for evaluation build).
* Translations (non-mandatory).
* A bunch of really niche features and edge cases (symlink support for `pwd`, `$SHLVL` incrementation, `$_` and a whole lot more).
* Custom prompt support via the PS1 environment variable (see next section).
* Command completion prompt for unclosed quotes or backslashes at the end of commands.

This was initially a team project created by [Kay](https://github.com/kay30kim) and myself. He wrote most of the code for pipes, redirections and signal handling. I wrote most of the rest of the code. The project as was submitted for evaluation had a ton of issues and we ended up with a frankly quite generous score of 95/100. Unsatisfied with this result, I moved the project to my GitLab and continued improving it on my own. As such, the project as seen in this repository is much improved compared to the project we submitted for evaluation in March 2024. The repository for that version of the project can still be found on my GitHub: https://github.com/lcouturi/minishell.

## Custom Prompts

This was added purely for fun, no tester I could find actually tests for this. It's also very incomplete. I only implemented the codes I personally use, which are as follows:

* `\$`, which expands into `#` if the user is root and `$` otherwise.
* `\W`, which expands into the name of the current working directory.
* `\h`, which is supposed to expand into the hostname, but instead expands into nothing because I have no means of getting the hostname using the permitted functions.
* `\s`, which expands into the shell name (always `minishell`).
* `\u`, which expands into your username.
* `\v`, which expands into the shell version (always `1.0`, because I don't have a proper versioning system for this).

The implementation for a lot of this is less than ideal because I lack a lot of the functions needed to get the info I need. For instance, I can't use `geteuid()` or `getlogin()`, so my only means of getting the username is through the `$USER` environment variable, which is vulnerable to user alteration and may thus have an incorrect value. Not much I can do about it, though.

## Tests

This project was mainly tested against Bash 5.2 using a number of tester programs available online. When using these testers, it is thus recommended to have Bash 5.2 installed. Bash 3.2, which is the version included in macOS by default, has some differences which will cause some tests to fail. Here are the results (last updated on July 28th, 2024):

### [mstest](https://github.com/zstenger93/42_minishell_tester) (mandatory)

For this tester to work, the MSTEST_MODE macro must be set to true.

#### mstest ne (no environment tests)

* 39/44 tests passed.
* 126 cases passed.
* 6 cases failed, including 4 STD_OUT cases and 2 EXIT_CODE cases.

Dunno what problem the tester has with most of these, except for tests 30 and 31. The problem there is that Bash is capable of expanding `~` to the user's home even if `$HOME` isn't set at launch, which I'm not sure how to replicate short of `execve`ing `whoami` (or `logname`, or `id`) and concatenating the output to `/Users/`, which feels like cheating.

#### mstest a (mandatory + bonus tests)

* 979/1001 tests passed.
* 2963 cases passed.
* 40 cases failed, including 14 STD_OUT cases, 11 STD_ERR cases and 15 EXIT_CODE cases.

#### mstest d (syntax tests)

* 57/61 tests passed.
* 179 cases passed.
* 4 cases failed, including 4 EXIT_CODE cases.

### [minishell_tester](https://github.com/LucasKuhn/minishell_tester) (mandatory)

For this tester to work, the MSTEST_MODE macro must be set to false.

#### ./tester

146/146 tests passed.

Five tests have warnings, all of them caused by minishell_tester expecting a `Permission denied` with my minishell instead printing nothing. I'm not sure how to reproduce these warnings, so they have not been fixed.

#### ./tester os_specific (extra)

10/11 tests passed.

#### ./tester syntax

17/17 tests passed.

Bonus-specific tests (wildcards, logical operators, subshells) live in `README_BONUS.md`.

### [minishell_test](https://github.com/cacharle/minishell_test)

* 1034 tests passed.
* 81 tests failed.

For this tester to work, you must change the path in line 25 of minishell_test.cfg to point to your installation of Bash 5.2.

## Project Structure

```
minishell/
├── src/                    # Source code
│   ├── core/              # Core functionality
│   ├── cmd/               # Command implementations
│   ├── parser/            # Command parsing
│   ├── pipe/              # Pipe handling
│   ├── redirection/       # Redirection handling
│   └── bonus/             # Bonus features
├── include/               # Header files
├── libs/                  # External libraries
├── Makefile               # Build configuration
└── .gitignore            # Git ignore rules
```

## Building

Depends on readline. If not installed, will automatically try to install it with `homebrew`. If that is also not installed, compilation will fail. Otherwise, compilation can simply be done like so:

	make
