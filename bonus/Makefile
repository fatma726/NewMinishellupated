# Bonus-only Makefile

NAME		:= minishell_bonus
CC			:= gcc
CFLAGS		:= -Werror -Wall -Wextra -Wpedantic -Wshadow \
			   -Wunused-parameter -Wunused-variable -Wunused-function \
			   -Wformat=2 -Wconversion -Wcast-align -Wcast-qual -Wwrite-strings \
			   -Wstrict-prototypes -Wmissing-prototypes -Wmissing-declarations \
			   -Wredundant-decls -Wnested-externs

LDFLAGS	:= -L$(HOME)/.brew/opt/readline/lib -L/opt/homebrew/opt/readline/lib -lreadline -L../libs/Libft -lft
CPPFLAGS	:= -I../include -I$(HOME)/.brew/opt/readline/include -I/opt/homebrew/opt/readline/include

CORE_OBJS	:= \
	../src/core/env_utils.o \
	../src/core/env_helpers.o \
	../src/core/file_utils.o \
	../src/core/global.o \
	../src/core/global_accessors.o \
	../src/core/input_utils.o \
	../src/core/input_helpers.o \
	../src/core/main.o \
	../src/core/process_command.o \
	../src/core/numeric_utils.o \
	../src/core/run_commands.o \
	../src/core/strarrutils.o \
	../src/core/termios_utils.o \
	../src/cmd/alias.o \
	../src/cmd/alias_helpers.o \
	../src/cmd/cd.o \
	../src/cmd/cd_helpers.o \
	../src/cmd/cd_helpers2.o \
	../src/cmd/cd_pwd.o \
	../src/cmd/echo.o \
	../src/cmd/env.o \
	../src/cmd/exec.o \
	../src/cmd/exec_error.o \
	../src/cmd/exec_helpers.o \
	../src/cmd/exec_proc.o \
	../src/cmd/exit.o \
	../src/cmd/exit_helpers2.o \
	../src/cmd/exit_helpers3.o \
	../src/cmd/export.o \
	../src/cmd/export_helpers.o \
	../src/cmd/export_helpers2.o \
	../src/cmd/export_helpers3.o \
	../src/cmd/export2.o \
	../src/cmd/history.o \
	../src/cmd/pwd.o \
	../src/cmd/unset.o \
	../src/cmd/unset_helpers.o \
	../src/cmd/unset_helpers2.o \
	../src/parser/escape_split.o \
	../src/parser/expand_alias.o \
	../src/parser/expand_envvar.o \
	../src/parser/expand_wildcard.o \
	../src/parser/get_arg_num.o \
	../src/parser/get_file_list.o \
	../src/parser/get_length.o \
	../src/parser/hash_handler.o \
	../src/parser/is.o \
	../src/parser/is2.o \
	../src/parser/load_lst.o \
	../src/parser/parser.o \
	../src/parser/prompt.o \
	../src/parser/quote_check.o \
	../src/parser/rm_quotes.o \
	../src/parser/semicolon_handler.o \
	../src/parser/semicolon_helpers.o \
	../src/parser/syntax.o \
	../src/parser/syntax_helpers.o \
	../src/parser/syntax_helpers2.o \
	../src/parser/syntax_helpers3.o \
	../src/redirection/argu_cleanup.o \
	../src/redirection/cmd_redir.o \
	../src/redirection/exec_redir.o \
	../src/redirection/redir_helpers.o \
	../src/redirection/utils_redir.o \
	../src/redirection/utils_redir2.o \
	../src/redirection/utils_redir3.o \
	../src/pipe/utils_pipe.o \
	../src/pipe/utils_pipe2.o \
	../src/pipe/utils_pipe3.o

BONUS_DIR	:= src/bonus
OBJ_DIR		:= obj
BONUS_SRCS	:= \
	$(BONUS_DIR)/split_operators.c \
	$(BONUS_DIR)/subshell.c
BONUS_OBJS	:= $(BONUS_SRCS:$(BONUS_DIR)/%.c=$(OBJ_DIR)/%.o)

# Build stubs without bonus functions for bonus link
STUB_BONUS	:= $(OBJ_DIR)/stubs.o

all: $(NAME)

$(CORE_OBJS):
	@$(MAKE) -s -C ..

$(NAME): $(CORE_OBJS) $(BONUS_OBJS) $(STUB_BONUS)
	$(CC) $(CFLAGS) $(CORE_OBJS) $(BONUS_OBJS) $(STUB_BONUS) $(LDFLAGS) -o $@

$(OBJ_DIR)/%.o: $(BONUS_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

$(STUB_BONUS): ../src/core/stubs.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(CPPFLAGS) -DBUILD_BONUS -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re


