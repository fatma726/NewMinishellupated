NAME = minishell
CC = gcc
CFLAGS = -Werror -Wall -Wextra -Wpedantic -Wshadow -Wunused-parameter -Wunused-variable -Wunused-function -Wformat=2 -Wconversion -Wcast-align -Wcast-qual -Wwrite-strings -Wstrict-prototypes -Wmissing-prototypes -Wmissing-declarations -Wredundant-decls -Wnested-externs

# Readline include/lib paths (42 Homebrew and macOS Homebrew)
READLINE_INC = -I$(HOME)/.brew/opt/readline/include -I/opt/homebrew/opt/readline/include
READLINE_LIB = -L$(HOME)/.brew/opt/readline/lib -L/opt/homebrew/opt/readline/lib

LDFLAGS = $(READLINE_LIB) -lreadline -Llibs/Libft -lft
CPPFLAGS = -I./include $(READLINE_INC)

# Explicit Homebrew macOS flags (requested)
CFLAGS += -I/opt/homebrew/opt/readline/include
# Avoid linking readline twice; only extend the search path here
LDFLAGS += -L/opt/homebrew/opt/readline/lib

INCLUDE_DIR = ./include

MAIN = env_utils env_helpers file_utils global global_accessors input_utils input_helpers main process_command numeric_utils run_commands strarrutils termios_utils stubs
CMD = alias alias_helpers cd cd_helpers cd_helpers2 cd_pwd echo env exec exec_error exec_helpers exec_proc exit exit_helpers2 exit_helpers3 export export_helpers export_helpers2 export_helpers3 export2 history pwd unset unset_helpers unset_helpers2 exec_check_utils
PARSER =  escape_split expand_alias expand_envvar expand_wildcard get_arg_num get_file_list get_length hash_handler is is2 load_lst parser prompt quote_check rm_quotes semicolon_handler semicolon_helpers syntax syntax_helpers syntax_helpers2 syntax_helpers3
REDIR = argu_cleanup cmd_redir exec_redir redir_helpers utils_redir utils_redir2 utils_redir3
PIPE = utils_pipe utils_pipe2 utils_pipe3 utils_pipe4


SRCS =	$(addsuffix .c, $(addprefix src/core/, $(MAIN))) \
		$(addsuffix .c, $(addprefix src/cmd/, $(CMD))) \
		$(addsuffix .c, $(addprefix src/parser/, $(PARSER))) \
		$(addsuffix .c, $(addprefix src/redirection/, $(REDIR))) \
		$(addsuffix .c, $(addprefix src/pipe/, $(PIPE)))

OBJS = $(SRCS:.c=.o)

all : $(NAME)

$(NAME) : $(OBJS)
	@make bonus -s -C libs/Libft
	$(CC) $(CFLAGS) $(LDFLAGS) $(OBJS) -o $(NAME)


%.o: %.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

clean :
	@make clean -s -C libs/Libft
	@rm -rf $(OBJS) "|" "<" ">" ">>" .temp asd echo grep la lol minishell.dSYM o out0 out1 tmp_*

debug : clean
	@make debug -s -C libs/Libft
	$(CC) $(CFLAGS) $(CPPFLAGS) -g -fsanitize=address $(LDFLAGS) $(SRCS) -o $(NAME)

fclean : clean
	@make fclean -s -C libs/Libft
	@rm -rf $(NAME)

re : fclean all

.PHONY : all, clean, debug, fclean, re,
