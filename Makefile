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
LIBFT_SRCS := ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c ft_strlen.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c ft_strlcpy.c ft_strlcat.c ft_toupper.c ft_tolower.c ft_strchr.c ft_strrchr.c ft_strncmp.c ft_memchr.c ft_memcmp.c ft_strnstr.c ft_atoi.c ft_calloc.c ft_strdup.c ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c ft_lstlast_bonus.c ft_lstadd_back_bonus.c ft_lstdelone_bonus.c ft_lstclear_bonus.c ft_lstiter_bonus.c ft_lstmap_bonus.c
LIBFT_OBJS := $(addprefix $(LIBFT_DIR)/, $(LIBFT_SRCS:.c=.o))
LIBFT     := $(LIBFT_DIR)/libft.a

# Source files (keeping existing structure)
MAIN = env_utils env_utils2 env_helpers env_helpers2 file_utils global input_utils input_helpers main process_command process_command_helpers numeric_utils strarrutils termios_utils stubs wildcard_stubs wildcard_parser_stubs signals status memory_validation
CMD = cd cd_helpers cd_helpers2 cd_pwd echo env exec exec_error exec_helpers exec_proc exit exit_helpers2 exit_helpers3 export export_helpers export_helpers2 export_helpers3 export2 pwd unset unset_helpers unset_helpers2 exec_check_utils
PARSER =  escape_split expand_envvar get_length hash_handler is is2 is3 is4 parser parser_helpers parser_helpers2 prompt6 prompt_helpers quote_check rm_quotes syntax syntax_helpers syntax_helpers2 syntax_helpers3 syntax_helpers4 wildcard_parser wildcard_parser_helpers
REDIR = argu_cleanup cmd_redir exec_redir heredoc_utils redir_helpers right_redir utils_redir utils_redir2 utils_redir3
PIPE = utils_pipe utils_pipe2 utils_pipe3 utils_pipe4

SRCS =	$(addsuffix .c, $(addprefix src/core/, $(MAIN))) \
		$(addsuffix .c, $(addprefix src/cmd/, $(CMD))) \
		$(addsuffix .c, $(addprefix src/parser/, $(PARSER))) \
		$(addsuffix .c, $(addprefix src/redirection/, $(REDIR))) \
		$(addsuffix .c, $(addprefix src/pipe/, $(PIPE)))

OBJS := $(SRCS:.c=.o)

# Bonus sources
BONUS_SRCS := \
	bonus/src/bonus/split_operators.c \
	bonus/src/bonus/split_operators_helpers.c \
	bonus/src/bonus/split_operators_helpers2.c \
	bonus/src/bonus/subshell.c \
	bonus/src/bonus/subshell_helpers.c \
	bonus/src/bonus/wildcard/expand_wildcard.c \
	bonus/src/bonus/wildcard/expand_wildcard_helpers.c \
	bonus/src/bonus/wildcard/expand_wildcard_loop.c \
	bonus/src/bonus/wildcard/expand_wildcard_redir.c \
	bonus/src/bonus/wildcard/expand_wildcard_utils.c \
	bonus/src/bonus/wildcard/get_arg_num.c \
	bonus/src/bonus/wildcard/get_file_list.c \
	bonus/src/bonus/wildcard/load_lst.c \
	bonus/src/bonus/wildcard/pattern_matching.c \
	bonus/src/bonus/wildcard/wildcard_handler.c

BONUS_OBJS := $(BONUS_SRCS:.c=.o)

# Bonus-specific parser objects (built from non-bonus paths)
BONUS_PARSER_OBJS := src/parser/wildcard_parser_bonus.o src/parser/wildcard_parser_helpers_bonus.o

# Targets
NAME := minishell
BONUS_NAME := minishell_bonus

# Default target
all: $(NAME)

# Mandatory target
mandatory: $(NAME)

# Bonus target
bonus: $(BONUS_NAME)

# Both targets
both: $(NAME) $(BONUS_NAME)

$(LIBFT): $(LIBFT_OBJS)
	ar rcs $@ $^

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(OBJS) -L$(LIBFT_DIR) -lft $(READLINE_LIBS) -o $@

$(BONUS_NAME): $(OBJS) $(BONUS_PARSER_OBJS) $(BONUS_OBJS) $(LIBFT)
		$(CC) $(filter-out src/core/stubs.o src/core/wildcard_stubs.o src/core/wildcard_parser_stubs.o src/parser/wildcard_parser.o src/parser/wildcard_parser_helpers.o, $(OBJS)) $(BONUS_PARSER_OBJS) $(BONUS_OBJS) -L$(LIBFT_DIR) -lft $(READLINE_LIBS) -o $@

src/core/%.o: src/core/%.c
	$(CC) $(CFLAGS) -I./include -c $< -o $@

src/cmd/%.o: src/cmd/%.c
	$(CC) $(CFLAGS) -I./include -c $< -o $@

src/parser/%.o: src/parser/%.c
		$(CC) $(CFLAGS) -I./include -c $< -o $@

# Bonus-compiled variant of wildcard_parser for the bonus binary
src/parser/wildcard_parser_bonus.o: src/parser/wildcard_parser.c
		$(CC) $(CFLAGS) -DBUILD_BONUS -I./include -I./bonus/include -c $< -o $@

src/parser/wildcard_parser_helpers_bonus.o: src/parser/wildcard_parser_helpers.c
		$(CC) $(CFLAGS) -DBUILD_BONUS -I./include -I./bonus/include -c $< -o $@

src/redirection/%.o: src/redirection/%.c
	$(CC) $(CFLAGS) -I./include -c $< -o $@

src/pipe/%.o: src/pipe/%.c
	$(CC) $(CFLAGS) -I./include -c $< -o $@

bonus/%.o: bonus/%.c
	$(CC) $(CFLAGS) -DBUILD_BONUS -I./include -c $< -o $@

$(LIBFT_DIR)/%.o: $(LIBFT_DIR)/%.c
	$(CC) -Wall -Wextra -Werror -I$(LIBFT_DIR) -c $< -o $@

clean:
	rm -f $(OBJS) $(BONUS_OBJS) $(BONUS_PARSER_OBJS) $(LIBFT_OBJS)

fclean: clean
	rm -f $(NAME) $(BONUS_NAME) $(LIBFT)

re: fclean all

debug: clean
	$(CC) $(CFLAGS) -g -fsanitize=address $(SRCS) -L$(LIBFT_DIR) -lft $(READLINE_LIBS) -o $(NAME)

# Build with debug symbols suitable for Valgrind (no ASan)
valgrind: clean
	$(CC) $(CFLAGS) -g $(SRCS) -L$(LIBFT_DIR) -lft $(READLINE_LIBS) -o $(NAME)

.PHONY: all mandatory bonus both clean fclean re debug valgrind
