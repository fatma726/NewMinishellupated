/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatmtahmdabrahym <fatmtahmdabrahym@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by kyung-ki          #+#    #+#             */
/*   Updated: 2025/09/03 18:41:42 by fatmtahmdab      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define MSTEST_MODE 0

/* includes */
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <termios.h>
# include <unistd.h>
# include "../libs/Libft/libft.h"

typedef struct s_global_state
{
	int	signal_number;
	int	exit_status;
}	t_global_state;

/* enums */
typedef enum e_message
{
	commandnotfound,
	filenameargumentrequired,
	invalidaliasname1,
	invalidaliasname2,
	notavalididentifier1,
	notavalididentifier2,
	notfound,
	numericargumentrequired,
	oldpwdnotset,
	syntaxerrornearunexpectedtoken1,
	syntaxerrornearunexpectedtoken2,
	toomanyarguments
}	t_message;

typedef enum e_language
{
	english,
	french
}	t_language;

/* structs */
typedef struct s_node
{
	char	**aliases;
	bool	argmode;
	int		backup_stdin;
	int		backup_stdout;
	int		child_die;
	char	*cmd;
	int		echo_skip;
	bool	escape_skip;
	int		exit_flag;
	int		fds[2];
	int		i;
	bool	last;
	int		line_nbr;
	char	**ori_args;
	int		parent_die;
	char	*path;
	char	*path_fallback;
	int		pipe_flag;
	int		pipe_idx;
	char	*pwd;
	int		quota_idx_j;
	int		quota_pipe_cnt;
	int		quota_pipe_idx_arr[10];
	int		redir_fd;
	int		redir_fds[2];
	int		redir_flag;
	int		redir_idx;
	int		redir_stop;
	int		right_flag;
	bool	syntax_flag;
}	t_node;

/* global state access */
int				get_signal_number(void);
void			clear_signal_number(void);
int				get_exit_status(void);
void			set_exit_status(int status);

/* bonus */
char			**split_operators(char *s, char **envp, t_node *n);
char			**subshell(char *str, char **envp, t_node *node);

/* cmds */
void			checkdot(char **args, char **envp);
void			chkdir(char **args, char **envp, bool end);
void			cmd_alias(char **args, char **envp, t_node *node);
void			printalias(char *str);
void			set_alias(char *arg, char **envp, t_node *node);
char			*find_lowest_alias(char **aliases, char *lowest_old,
					unsigned int i2);
char			**cmd_cd(char **args, char **envp, t_node *node);
bool			check_arg_count_with_slash(char **args, char **envp,
					bool offset);
bool			check_arg_count_without_slash(char **args, char **envp,
					bool offset);
bool			check_argument_count(char **args, char **envp, bool offset);
bool			handle_home_cd(char **args, char **envp, bool offset);
bool			handle_oldpwd_cd(char **args, char **envp, t_node *node,
					bool offset);
bool			handle_chdir_error(char **args, bool offset);
bool			checks2(char **args, char **envp, t_node *node,
					bool offset);
bool			checks(char **args, char **envp, t_node *node,
					bool offset);
void			cmd_echo(char **args, t_node *node);
char			**cmd_env(char **args, char **envs, t_node *node);
char			**cmd_exec(char **args, char **envp, t_node *node);
void			cmd_exit(char **args, char **envp, t_node *node);
void			handle_exit_message(void);
void			handle_numeric_error(char *arg);
void			handle_too_many_args(void);
void			handle_exit_with_args(char **args);
void			cleanup_and_exit(char **args, char **envp, t_node *node);
char			**cmd_export(char **args, char **envp, t_node *node);
char			**export_print(char **envp);
void			print_escaped_value(char *value);
bool			is_valid_identifier_start(char c);
bool			is_valid_identifier_char(char c);
void			print_invalid_identifier_error(char *arg);
bool			process_export_arg(char *arg, char ***envp, t_node *node);
void			handle_export_option_error(char **args);
void			process_export_args(char **args, char ***envp, t_node *node);
void			handle_path_update(char *arg, t_node *node);
char			**handle_env_update(char *arg, char **envp, char *name, int j);
bool			validate_export_identifier(char *arg);
void			cmd_pwd(t_node *node);
void			cmd_history(char **args, t_node *node);
char			**cmd_unset(char **args, char **envp, t_node *node);
bool			is_valid_identifier(char *str);
int				find_envkey(char *str, char *envp);
char			**delete_env(char *str, char **envp, t_node *node, int *flag);
void			handle_unset_option_error(char **args);
void			process_unset_args(char **args, char **envp, t_node *node,
					int *flag);
bool			is_valid_identifier_start_unset(char c);
bool			is_valid_identifier_char_unset(char c);

/* exec helpers (norm-friendly) */
void			post_wait_set_status(int pid, int background);
bool			exec_check_loop(char **paths, char **args);
bool			exec_check(char **args, char **envp, t_node *node);
void			exec_error(char **args, char **envp, char **paths);
void			exec_proc(char **args, char **envp, t_node *node);
char			**exec_pipe(char *path, char **args, char **envp,
					t_node *node);
void			exec_nopath(t_node *node, char **args, char **envp,
					char **paths);
void			exec_proc_loop(char **paths, char **args, char **envp,
					t_node *node);
void			exec_proc_loop2(char **paths, char **args, char **envp,
					t_node *node);
char			**get_paths(char **envp);
bool			is_executable(char *path);
bool			is_directory(char *path);
long			ft_atol(const char *str);
long long		ft_atoll(const char *str);
bool			ft_isalldigit(char *str);
char			*ft_getenv(const char *name, char **envp);
char			**ft_setenv(const char *name, const char *value,
					char **envp);
char			*newpwd(t_node *node, char **envp);
void			printenv(char *str);
char			*curdir(char **envp);
char			*get_curdir(void);

/* main */
t_language		get_lang(char **envp);
char			*get_line(char *str);
char			**get_file(int fd);
char			*read_line_simple(void);
const char		*i18n(t_message arg, t_language language);
void			argmode(char *line, char *arg, char **envp, t_node *node);
char			**run_commands(char **envp, t_node *node);
void			set_signal(void);
void			set_termios(void);
void			restore_termios(void);
char			**setpwd(t_node *node, char **envp);
char			**shlvl_mod(int mod, char **envp);
char			**shlvl_plus_plus(char **envp);
char			**strarradd(char **strs, char *str);
char			**strarrdup(char **strs);
void			strarrfree(char **strs);
size_t			strarrlen(char **strs);
char			**process_command(char *line, char **envp, t_node *n);
char			**get_prompt(char **envp, t_node *n);

/* parser */
bool			error_message(const char *token, char **envp, t_node *node);
char			*escape_handler(char *str, t_node *node);
char			**escape_split(char *s, char *charset, t_node *node);
char			*expand_alias(char *str, t_node *node);
char			*get_command(char *str, int i, int offset, t_node *node);
char			*expand_envvar(char *str, char **envp, t_node *node);
char			*expand_prompt(char *fmt, char **envp, t_node *node);
char			**expand_wildcard(char **args, char **envp, t_node *node);
char			*expand_wildcard_redir(char *pattern, t_node *node);
char			**find_command(char **args, char **envp, t_node *node);
int				get_arg_num(char **args, t_node *node);
char			**get_file_list(bool hidden);
int				match_loop(char **split, char **files, int i);
void			match(char *str, char **split, char **files, int i);
char			**load_lst(struct dirent *dr, DIR *dir, bool hidden);
void			get_length(char *str, char **envp, int *i, t_node *node);
char			*hash_handler(char *str, t_node *node);
bool			in_heredoc(char *str, int i);
bool			isdlr(char *str);
bool			isdrr(char *str);
bool			islr(char *str);
bool			islrr(char *str);
bool			isp(char *str);
bool			istr(char *str);
bool			isrr(char *str);
bool			istlr(char *str);
bool			isdp(char *str);
bool			isda(char *str);
char			**parser(char *str, char **envp, t_node *node);
int				quote_check(char const *s, int i, t_node *node);
char			**rm_quotes(char **args, t_node *node);
char			**rm_quotes_wildcards(char **args, t_node *node);
char			**semicolon_handler(char *str, char **envp, t_node *node);
bool			syntax_check(char **args, char **envp, t_node *node);
void			tilde_handler(char **args, int *i, char **envp);

/* syntax helpers */
const char		*check_leading_operators(char **args);
const char		*check_consecutive_ops(char **args, int i);
const char		*check_triple_redir_split(char **args, int i);
bool			check_leading_operators_syntax(char **a);
bool			check_consecutive_operators_syntax(char **a);
bool			check_pipe_redir_combination(char **a, int i);
bool			check_trailing_operators_syntax(char **a);
const char		*get_error_token(char **args);
bool			c(char **args, int i, bool (*f1)(char *), bool (*f2)(char *));
void			handle_syntax_error(char **envp, t_node *node);
bool			semicolon_syntax_check(char **split, char **envp, t_node *node);
bool			check_invalid_operator_sequences_in_string(char *s, t_node *n);
char			**process_semicolon_commands(char **split, char **envp,
				t_node *node);

/* pipe */
int				prepare_redirections(char **args, char **envp, t_node *node);
int				maybe_setup_pipe(t_node *node);
void			backup_restor(t_node *node);
char			**cloturn(int backup_stdout, int backup_stdin, char **envp);
void			exec_child(char **args, char **envp, t_node *node);
void			exec_parents(char **args, char **envp, t_node *node);
char			**execute(char **args, char **envp, t_node *node);
void			init_node(t_node *node);
char			**one_commnad(char **args, char **envp, t_node *node);
int				pipe_check(char **args, t_node *node);
int				redir_syntax_check(char **args);
char			**repeat(char **args, char **envp, t_node *node);
char			**split_before_pipe_args(char **args, t_node *node);
void			double_lmove_idx_change(char **args, int *i);
bool			is_pipe(char *str);
bool			is_ampersand(char *str);

/* redirection */
void			args_left_move(char **args, int i);
void			args_left_move_i(char **args, t_node *node);
void			argu_left_change(char **args, t_node *node);
int				exec_redir(char **args, char **envp, t_node *node);
void			exec_redir_child(char **args, char **envp, t_node *node,
					int *flag);
void			exec_redir_parents(char **args, char **envp, t_node *node,
					int *flag);
bool			is_redir(char **args, int i, int j);
bool			is_redir_check(char *str);
int				left_redir(char **args, char **envp, int *i, t_node *node);
int				left_double_redir(char **args, char **envp, int *i,
					t_node *node);
int				print_err(char **args, int i, t_node *node);
int				print_err2(char **args, int i);
int				print_err3(char **args, t_node *node, int *i);
int				redir_chk(char **args);
int				redir_excute(char **args, char **envp, t_node *node, int flag);
int				right_redir(char **args, int *i, t_node *node);
int				right_double_redir(char **args, int *i, t_node *node);
int				heredoc_loop(char **args, char **envp, int *i, t_node *node);
int				setup_heredoc_file(t_node *node);
void			cleanup_heredoc_file(t_node *node);
void			move_redir_args(char **args, char **ori_args, int *i);
bool			is_left_redir(char *str);
bool			is_right_redir(char *str);
bool			is_double_left_redir(char *str);
bool			is_double_right_redir(char *str);
void			argu_left_change(char **args, t_node *node);
int				left_redir_expand(char **args, int i, t_node *node,
					char **expanded);
void			handle_echo_skip(char **args, t_node *node);
int				open_redir_out(char **args, int i, t_node *node, int flags);

#endif
