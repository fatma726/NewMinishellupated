/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_stubs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatima <fatima@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by fatima            #+#    #+#             */
/*   Updated: 2025/09/04 10:30:00 by fatima           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#ifndef BUILD_BONUS

char	*expand_wildcard_redir(char *pattern, t_node *node)
{
	(void)node;
	return (ft_strdup(pattern));
}

char	**expand_wildcard(char **args, char **envp, t_node *node)
{
	(void)envp;
	(void)node;
	return (args);
}

char	**get_file_list(bool hidden)
{
	char	**files;

	(void)hidden;
	files = malloc(sizeof(char *));
	if (!files)
		exit(EXIT_FAILURE);
	files[0] = NULL;
	return (files);
}

int	get_arg_num(char **args, t_node *node)
{
	(void)args;
	(void)node;
	return (0);
}

char	**load_lst(struct dirent *dr, DIR *dir, bool hidden)
{
	char	**files;

	(void)dr;
	(void)dir;
	(void)hidden;
	files = malloc(sizeof(char *));
	if (!files)
		exit(EXIT_FAILURE);
	files[0] = NULL;
	return (files);
}

#endif
