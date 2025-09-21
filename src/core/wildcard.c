/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatmtahmdabrahym <fatmtahmdabrahym@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by fatima            #+#    #+#             */
/*   Updated: 2025/09/20 17:00:50 by fatmtahmdab      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#ifndef BUILD_BONUS

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

bool	check_wildcard_redirections(char **args)
{
	(void)args;
	return (true);
}

char	**expand_wildcard_if_bonus(char **args, char **envp, t_node *node)
{
	(void)envp;
	(void)node;
	return (args);
}

#endif
