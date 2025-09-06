/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatima <fatima@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 12:00:00 by fatima            #+#    #+#             */
/*   Updated: 2025/09/04 11:04:44 by fatima           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BONUS_H
# define BONUS_H

# include "minishell.h"

/* Bonus features */

/* Logical operators and parentheses */
char	**split_operators(char *s, char **envp, t_node *n);
char	**subshell(char *str, char **envp, t_node *node);
bool	check_redirection_syntax(char *s, t_node *n);
bool	is_operator_pair(char *s, size_t i, t_node *n);
bool	starts_invalid(char *s, size_t i);
bool	has_triple_ops(char *s, size_t i);
bool	has_mixed_op_error(char *s, t_node *n);
bool	handle_invalid_start_and_report(char *s, size_t i, t_node *n);
bool	syntax_err_pair(char *s, size_t i, t_node *n, int pair);
char	*handle_triple_redir_error(char *str, t_node *node);
char	*handle_paren_error(char *str, int count);

/* Wildcards */
char	**expand_wildcard(char **args, char **envp, t_node *node);
char	**get_file_list(bool hidden);
int		match_loop(char **split, char **files, int i);
void	match(char *str, char **split, char **files, int i);
char	**load_lst(struct dirent *dr, DIR *dir, bool hidden);

/* Quote handling */
char	*expand_envvar(char *str, char **envp, t_node *node);
char	**rm_quotes(char **args, t_node *node);
char	**rm_quotes_wildcards(char **args, t_node *node);

/* Syntax helpers for bonus */
bool	isdp(char *str);
bool	isda(char *str);

/* Wildcard helpers */
int		count_matching_files(char *pattern);
int		expand_pattern(char **newargs, int *j, char *pattern);
void	wildcard_handler(char **args, char **newargs, int *i, t_node *node);
int		count_wildcard_matches(char **args);
int		process_all_args(char **args, char **newargs);
void	cleanup_and_return(char **newargs, int j, char **args);
int		matches_pattern(char *filename, char *pattern);

#endif
