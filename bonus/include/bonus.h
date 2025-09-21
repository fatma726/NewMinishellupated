/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatmtahmdabrahym <fatmtahmdabrahym@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 12:00:00 by fatima            #+#    #+#             */
/*   Updated: 2025/09/20 20:13:56 by fatmtahmdab      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BONUS_H
# define BONUS_H

# include "minishell.h"

/* Logical operators and parentheses */
bool	check_redirection_syntax(char *s, t_node *n);
bool	is_operator_pair(char *s, size_t i, t_node *n);
bool	starts_invalid(char *s, size_t i);
bool	has_triple_ops(char *s, size_t i);
bool	has_mixed_op_error(char *s, t_node *n);
bool	handle_invalid_start_and_report(char *s, size_t i, t_node *n);
bool	syntax_err_pair(char *s, size_t i, t_node *n, int pair);
char	*handle_triple_redir_error(char *str, t_node *node);
char	*handle_paren_error(char *str, int count);

/* Wildcard helpers */
int		count_matching_files(char *pattern);
int		expand_pattern(char **newargs, int *j, char *pattern);
int		count_wildcard_matches(char **args);
int		process_all_args(char **args, char **newargs);
void	cleanup_and_return(char **newargs, int j, char **args);
int		matches_pattern(char *filename, char *pattern);
int		collect_matches(char **matches, char *pattern);
int		process_directory_entry(struct dirent *dr, char *pattern);
void	sort_matches(char **matches);
int		add_sorted_matches(char **newargs, int *j, char **matches);
int		add_matching_file(char **newargs, int *j, char *filename);
void	cleanup_matches(char **matches, int i, DIR *dir);

#endif
