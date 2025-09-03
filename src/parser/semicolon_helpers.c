/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semicolon_helpers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatmtahmdabrahym <fatmtahmdabrahym@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by fatmtahmdabrahym #+#    #+#             */
/*   Updated: 2025/01/29 19:31:40 by fatmtahmdabrahym ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

bool	error_message(char *token, char **envp, t_node *node)
{
	char	*msg1;
	char	*msg2;

	msg1 = ft_strdup(i18n(syntaxerrornearunexpectedtoken1, get_lang(envp)));
	msg2 = ft_strdup(i18n(syntaxerrornearunexpectedtoken2, get_lang(envp)));
	ft_putstr_fd(msg1, STDERR_FILENO);
	ft_putstr_fd(token, STDERR_FILENO);
	ft_putstr_fd(msg2, STDERR_FILENO);
	free(msg1);
	free(msg2);
	set_exit_status(2);
	node->syntax_flag = true;
	return (false);
}

bool	semicolon_syntax_check(char **split, char **envp, t_node *node)
{
	bool	empty;
	int		i;
	int		j;
	char	semicolon[2];

	i = -1;
	while (split[++i])
	{
		empty = true;
		j = -1;
		while (split[i][++j])
			if (!ft_strchr(" \t", split[i][j]))
				empty = false;
		if (empty)
		{
			ft_strlcpy(semicolon, ";", 2);
			return (error_message(semicolon, envp, node));
		}
	}
	return (true);
}
