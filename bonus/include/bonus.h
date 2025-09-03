/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatima <fatima@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 12:00:00 by fatima            #+#    #+#             */
/*   Updated: 2025/09/03 09:12:00 by fatima           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BONUS_H
# define BONUS_H

# include "minishell.h"

/* Bonus features */

/* Logical operators and parentheses */
char	**split_operators(char *s, char **envp, t_node *n);
char	**subshell(char *str, char **envp, t_node *node);

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

#endif
