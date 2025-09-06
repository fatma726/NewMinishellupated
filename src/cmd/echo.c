/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatmtahmdabrahym <fatmtahmdabrahym@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by kyung-ki          #+#    #+#             */
/*   Updated: 2025/08/30 18:44:48 by fatmtahmdab      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_n_option(char *str)
{
	int	i;

	if (ft_strncmp(str, "-n", 2))
		return (0);
	i = 1;
	while (str && str[++i])
		if (str[i] != 'n')
			return (0);
	return (1);
}

void	cmd_echo(char **args, t_node *node)
{
	int	i;
	int	new_line;

	i = 0;
	new_line = 1;
	while (args[++i] && is_n_option(args[i]))
		new_line = 0;
	if (args[i] && !node->echo_skip)
	{
		while (args && args[i])
		{
			if (node->pipe_flag && node->pipe_idx <= i + 1)
				break ;
			ft_putstr_fd(args[i], STDOUT_FILENO);
			if (args[i + 1] && i + 2 != node->pipe_idx)
				ft_putchar_fd(' ', STDOUT_FILENO);
			i++;
		}
	}
	if (new_line && !node->echo_skip)
		ft_putchar_fd('\n', STDOUT_FILENO);
	fflush(stdout);
	set_exit_status(EXIT_SUCCESS);
}
