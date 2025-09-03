/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semicolon_handler.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatmtahmdabrahym <fatmtahmdabrahym@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by lcouturi          #+#    #+#             */
/*   Updated: 2025/09/03 19:10:08 by fatmtahmdab      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	handle_leading_semicolon(char **envp, t_node *node)
{
	char	semicolon[2];

	ft_strlcpy(semicolon, ";", 2);
	error_message(semicolon, envp, node);
}

static char	**process_semicolon_split(char *str, t_node *node)
{
	char	semicolon[2];
	char	**split;

	ft_strlcpy(semicolon, ";", 2);
	split = escape_split(str, semicolon, node);
	return (split);
}

/* moved to semicolon_helpers.c to satisfy norm */

/* moved to semicolon_helpers.c to satisfy norm */

char	**semicolon_handler(char *str, char **envp, t_node *node)
{
	int		i;
	char	**split;

	if (node->syntax_flag)
	{
		free(str);
		return (envp);
	}
	if (!check_invalid_operator_sequences_in_string(str, node))
	{
		free(str);
		return (envp);
	}
	i = 0;
	while (str[i] && ft_strchr(" \t", str[i]))
		i++;
	if (str[i] == ';')
	{
		handle_leading_semicolon(envp, node);
		return (envp);
	}
	i = -1;
	split = process_semicolon_split(str, node);
	if (ft_strchr(str, ';') && !semicolon_syntax_check(split, envp, node))
		return (strarrfree(split), envp);
	envp = process_semicolon_commands(split, envp, node);
	return (free(str), free(split), envp);
}
