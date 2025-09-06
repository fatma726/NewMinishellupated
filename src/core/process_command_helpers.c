/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_command_helpers.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatmtahmdabrahym <fatmtahmdabrahym@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by fatmtahmdabrahym #+#    #+#             */
/*   Updated: 2025/01/29 19:31:40 by fatmtahmdabrahym ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**check_braces(char *line, char **envp, t_node *n)
{
	int	i;

	i = 0;
	while (line[i] && ft_strchr(" \t", line[i]))
		i++;
	if (line[i] == '{')
	{
		ft_putendl_fd("minishell: unexpected end of file", STDERR_FILENO);
		set_exit_status(2);
		n->syntax_flag = true;
		return (free(line), envp);
	}
	if (line[i] == '}')
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `",
			STDERR_FILENO);
		ft_putendl_fd("}'", STDERR_FILENO);
		set_exit_status(2);
		n->syntax_flag = true;
		return (free(line), envp);
	}
	return (NULL);
}
