/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatmtahmdabrahym <fatmtahmdabrahym@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by kyung-ki          #+#    #+#             */
/*   Updated: 2025/08/28 15:47:02 by fatmtahmdab      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

bool	ft_isalldigit(char *str)
{
	int	i;

	i = 0;
	if (str[0] == '+' || str[0] == '-')
		i++;
	while (str && str[i])
	{
		if (!ft_isdigit(str[i]))
			break ;
		i++;
	}
	while (str && str[i])
	{
		if (!ft_strchr(" \t", str[i]))
			return (false);
		i++;
	}
	return (true);
}

void	cmd_exit(char **args, char **envp, t_node *node)
{
	if (!node->exit_flag)
		return ;
	if (isatty(STDIN_FILENO) && !node->argmode)
		handle_exit_message();
	if (strarrlen(args) > 1)
		handle_exit_with_args(args);
	else
		set_exit_status(EXIT_SUCCESS);
	cleanup_and_exit(args, envp, node);
}
