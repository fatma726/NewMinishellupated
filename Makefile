# 🌈 Beautiful Colors and Icons for Hologram Effect 🌈
RESET   := \033[0m
BOLD    := \033[1m
DIM     := \033[2m
ITALIC  := \033[3m
UNDERLINE := \033[4m

# 🌟 Mandatory Build Colors
MANDATORY_COLOR := \033[38;5;51m  # Cyan
MANDATORY_ICON  := ✨
MANDATORY_TEXT  := MANDATORY

# 🚀 Bonus Build Colors  
BONUS_COLOR     := \033[38;5;208m  # Orange
BONUS_ICON      := 🚀
BONUS_TEXT      := BONUS

# 🎨 General Colors
SUCCESS_COLOR   := \033[38;5;46m   # Green
WARNING_COLOR   := \033[38;5;226m  # Yellow
ERROR_COLOR     := \033[38;5;196m  # Red
INFO_COLOR      := \033[38;5;75m   # Blue
HIGHLIGHT_COLOR := \033[38;5;201m  # Magenta

CC      := gcc
CFLAGS  := -Werror -Wall -Wextra -Wpedantic -Wshadow -Wunused-parameter -Wunused-variable -Wunused-function -Wformat=2 -Wconversion -Wcast-align -Wcast-qual -Wwrite-strings -Wstrict-prototypes -Wmissing-prototypes -Wmissing-declarations -Wredundant-decls -Wnested-externs
CFLAGS  += -I./include

# Readline (portable)
# Allow pkg-config discovery, but let local config override it.
READLINE_CFLAGS ?= $(shell pkg-config --cflags readline 2>/dev/null)
READLINE_LIBS   ?= $(shell pkg-config --libs   readline 2>/dev/null)

# Optional local overrides (create a config.mk to pin flags)
-include config.mk

UNAME_S := $(shell uname -s)
ifeq ($(strip $(READLINE_CFLAGS)),)
  ifeq ($(UNAME_S),Darwin)
    READLINE_CFLAGS += -I/opt/homebrew/opt/readline/include
    READLINE_LIBS   += -L/opt/homebrew/opt/readline/lib -lreadline -lncurses
  else
    # Linux fallback if pkg-config missing (Debian/Ubuntu)
    READLINE_LIBS   += -lreadline -lncurses
  endif
endif

CFLAGS  += $(READLINE_CFLAGS)

# Libft
LIBFT_DIR := libs/Libft
LIBFT_SRCS := ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c ft_strlen.c ft_memset.c ft_bzero.c ft_memcpy.c ft_strlcpy.c ft_strlcat.c ft_toupper.c ft_tolower.c ft_strchr.c ft_strrchr.c ft_strncmp.c ft_strnstr.c ft_atoi.c ft_calloc.c ft_strdup.c ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_lstnew.c ft_lstadd_back.c ft_lstsize.c ft_lstlast.c
LIBFT_OBJS := $(addprefix $(LIBFT_DIR)/, $(LIBFT_SRCS:.c=.o))
LIBFT     := $(LIBFT_DIR)/libft.a

# Source files (consolidated structure)
MAIN = env_utils env_utils2 env_helpers global status input_utils input_helpers main process_command process_command_helpers core_utils strarrutils stubs wildcard signals memory_validation
CMD = cd cd_utils basic_commands cmd_utils env exec exec_error exec_utils exit exit_utils export export_utils export_helpers unset unset_utils
PARSER =  escape_split expand_envvar expand_envvar_helpers parser_utils operator_utils operator_helpers operator_checks parser parser_helpers prompt_helpers rm_quotes rm_quotes_utils syntax_utils syntax_helpers syntax_helpers_utils syntax syntax_helpers3 syntax_helpers4
REDIR = argu_cleanup cmd_redir exec_redir heredoc_utils redir_utils utils_redir utils_redir2 utils_redir3
PIPE = pipe_core pipe_utils pipe_helpers

SRCS =	$(addsuffix .c, $(addprefix src/core/, $(MAIN))) \
		$(addsuffix .c, $(addprefix src/cmd/, $(CMD))) \
		$(addsuffix .c, $(addprefix src/parser/, $(PARSER))) \
		$(addsuffix .c, $(addprefix src/redirection/, $(REDIR))) \
		$(addsuffix .c, $(addprefix src/pipe/, $(PIPE)))

# Out-of-tree objects to reduce clutter in src/
OBJ_DIR := .dist/obj
OBJS    := $(SRCS:%.c=$(OBJ_DIR)/%.o)

# Bonus sources
BONUS_SRCS := \
	bonus/src/bonus/split_operators_main.c \
	bonus/src/bonus/split_operators_consolidated.c \
	bonus/src/bonus/split_operators_helpers2.c \
	bonus/src/bonus/subshell_consolidated.c \
	bonus/src/bonus/subshell_main.c \
	bonus/src/bonus/wildcard/wildcard_core.c \
	bonus/src/bonus/wildcard/expand_wildcard_helpers.c \
	bonus/src/bonus/wildcard/expand_wildcard_loop.c \
	bonus/src/bonus/wildcard/expand_wildcard_redir.c \
	bonus/src/bonus/wildcard/expand_wildcard_utils.c \
	bonus/src/bonus/wildcard/expand_wildcard_utils2.c \
	bonus/src/bonus/wildcard/get_file_list.c \
	bonus/src/bonus/wildcard/load_lst.c \
	bonus/src/bonus/wildcard/pattern_matching.c

BONUS_OBJS := $(BONUS_SRCS:%.c=$(OBJ_DIR)/%.o)

# Bonus-specific parser objects (built from non-bonus paths)
BONUS_PARSER_OBJS := \
	$(OBJ_DIR)/src/parser/wildcard_parser_bonus.o \
	$(OBJ_DIR)/src/parser/wildcard_parser_helpers_bonus.o \
	$(OBJ_DIR)/src/parser/wildcard_parser_helpers2_bonus.o

# Targets
NAME := minishell
BONUS_NAME := minishell_bonus

# Default target
all: $(NAME)
	@echo "$(BOLD)$(HIGHLIGHT_COLOR)╔══════════════════════════════════════════════════════════════╗$(RESET)"
	@echo "$(BOLD)$(HIGHLIGHT_COLOR)║              🌟 MINISHELL BUILD SYSTEM 🌟              ║$(RESET)"
	@echo "$(BOLD)$(HIGHLIGHT_COLOR)║              Hologram Edition v2.0                      ║$(RESET)"
	@echo "$(BOLD)$(HIGHLIGHT_COLOR)╚══════════════════════════════════════════════════════════════╝$(RESET)"

# Mandatory target
mandatory: $(NAME)

# Bonus target
bonus: $(BONUS_NAME)
	@echo "$(BOLD)$(BONUS_COLOR)╔══════════════════════════════════════════════════════════════╗$(RESET)"
	@echo "$(BOLD)$(BONUS_COLOR)║            🚀 MINISHELL BONUS BUILD SYSTEM 🚀            ║$(RESET)"
	@echo "$(BOLD)$(BONUS_COLOR)║            Advanced Features Edition v2.0                ║$(RESET)"
	@echo "$(BOLD)$(BONUS_COLOR)╚══════════════════════════════════════════════════════════════╝$(RESET)"

# Both targets
both: $(NAME) $(BONUS_NAME)

$(LIBFT): $(LIBFT_OBJS)
	@ar rcs $@ $^


$(NAME): $(OBJS) $(LIBFT)
	@echo "$(BOLD)$(MANDATORY_COLOR)╔══════════════════════════════════════════════════════════════╗$(RESET)"
	@echo "$(BOLD)$(MANDATORY_COLOR)║                    $(MANDATORY_ICON)  $(MANDATORY_TEXT) BUILD  $(MANDATORY_ICON)                    ║$(RESET)"
	@echo "$(BOLD)$(MANDATORY_COLOR)╚══════════════════════════════════════════════════════════════╝$(RESET)"
	@echo "$(DIM)$(INFO_COLOR)🔧 Compiling mandatory minishell...$(RESET)"
	@$(CC) $(OBJS) -L$(LIBFT_DIR) -lft $(READLINE_LIBS) -o $@
	@echo "$(BOLD)$(SUCCESS_COLOR)✅ $(MANDATORY_ICON) Mandatory build completed successfully! $(MANDATORY_ICON)$(RESET)"
	@echo "$(DIM)$(HIGHLIGHT_COLOR)💫 Ready to explore the shell universe! 💫$(RESET)"

$(BONUS_NAME): $(OBJS) $(BONUS_PARSER_OBJS) $(BONUS_OBJS) $(LIBFT)
	@echo "$(BOLD)$(BONUS_COLOR)╔══════════════════════════════════════════════════════════════╗$(RESET)"
	@echo "$(BOLD)$(BONUS_COLOR)║                     $(BONUS_ICON)  $(BONUS_TEXT) BUILD  $(BONUS_ICON)                     ║$(RESET)"
	@echo "$(BOLD)$(BONUS_COLOR)╚══════════════════════════════════════════════════════════════╝$(RESET)"
	@echo "$(DIM)$(INFO_COLOR)🚀 Compiling bonus minishell with advanced features...$(RESET)"
	@echo "$(DIM)$(HIGHLIGHT_COLOR)🌟 Including: Wildcards, Subshells, Advanced Operators 🌟$(RESET)"
	@$(CC) $(filter-out $(OBJ_DIR)/src/core/stubs.o $(OBJ_DIR)/src/core/wildcard.o $(OBJ_DIR)/src/parser/wildcard_parser.o $(OBJ_DIR)/src/parser/wildcard_parser_helpers.o, $(OBJS)) $(BONUS_PARSER_OBJS) $(BONUS_OBJS) -L$(LIBFT_DIR) -lft $(READLINE_LIBS) -o $@
	@echo "$(BOLD)$(SUCCESS_COLOR)✅ $(BONUS_ICON) Bonus build completed successfully! $(BONUS_ICON)$(RESET)"
	@echo "$(BOLD)$(HIGHLIGHT_COLOR)🎆 Welcome to the future of shell programming! 🎆$(RESET)"
	@echo "$(DIM)$(BONUS_COLOR)🚀 Ready to launch into advanced shell features! 🚀$(RESET)"

# Generic rule for all normal objects into OBJ_DIR
$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -I./include -c $< -o $@

# Bonus-compiled variant of wildcard_parser for the bonus binary (into OBJ_DIR)
$(OBJ_DIR)/src/parser/wildcard_parser_bonus.o: bonus/src/bonus/wildcard_parser_main.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -DBUILD_BONUS -I./include -I./bonus/include -c $< -o $@

$(OBJ_DIR)/src/parser/wildcard_parser_helpers_bonus.o: bonus/src/bonus/wildcard_parser_helpers.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -DBUILD_BONUS -I./include -I./bonus/include -c $< -o $@

$(OBJ_DIR)/src/parser/wildcard_parser_helpers2_bonus.o: bonus/src/bonus/wildcard_parser_helpers2.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -DBUILD_BONUS -I./include -I./bonus/include -c $< -o $@

# Bonus sources under bonus/ with BUILD_BONUS flag
$(OBJ_DIR)/bonus/%.o: bonus/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -DBUILD_BONUS -I./include -I./bonus/include -c $< -o $@

$(LIBFT_DIR)/%.o: $(LIBFT_DIR)/%.c
	@$(CC) -Wall -Wextra -Werror -I$(LIBFT_DIR) -c $< -o $@

clean:
	@echo "$(BOLD)$(WARNING_COLOR)🧹 Cleaning up object files...$(RESET)"
	@rm -f $(LIBFT_OBJS)
	@rm -rf $(OBJ_DIR)
	# Also clean any legacy in-tree objects left in src/ and bonus/
	@-find src -name '*.o' -type f -delete 2>/dev/null || true
	@-find bonus -name '*.o' -type f -delete 2>/dev/null || true
	@echo "$(SUCCESS_COLOR)✨ Clean completed! All object files removed. ✨$(RESET)"

fclean: clean
	@echo "$(BOLD)$(ERROR_COLOR)🗑️  Removing all binaries and libraries...$(RESET)"
	@rm -f $(NAME) $(BONUS_NAME) $(LIBFT)
	@echo "$(SUCCESS_COLOR)🧽 Full clean completed! Everything removed. 🧽$(RESET)"

re: fclean all
	@echo "$(BOLD)$(HIGHLIGHT_COLOR)🔄 Rebuild completed! Fresh start achieved! 🔄$(RESET)"

debug: clean
	$(CC) $(CFLAGS) -g -fsanitize=address $(SRCS) -L$(LIBFT_DIR) -lft $(READLINE_LIBS) -o $(NAME)

# Build with debug symbols suitable for Valgrind (no ASan)
valgrind: clean
	$(CC) $(CFLAGS) -g $(SRCS) -L$(LIBFT_DIR) -lft $(READLINE_LIBS) -o $(NAME)

.PHONY: all mandatory bonus both clean fclean re debug valgrind
