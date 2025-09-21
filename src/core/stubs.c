/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stubs.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatmtahmdabrahym <fatmtahmdabrahym@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by fatmtahmdab       #+#    #+#             */
/*   Updated: 2025/09/20 14:02:58 by fatmtahmdab      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Removed internationalization system - not required for evaluation

#ifndef BUILD_BONUS

/* Bonus operator stubs */
char	**split_operators(char *s, char **envp, t_node *n)
{
	(void)s;
	(void)n;
	return (envp);
}

char	**subshell(char *str, char **envp, t_node *node)
{
	return (parser(str, envp, node));
}

/* Wildcard stubs */
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

#endif
