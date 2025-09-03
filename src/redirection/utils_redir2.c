/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_redir2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatmtahmdabrahym <fatmtahmdabrahym@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by kyung-ki          #+#    #+#             */
/*   Updated: 2025/08/28 16:23:02 by fatmtahmdab      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	print_err(char **args, int i, t_node *node)
{
	char	bash_line[20];

	ft_strlcpy(bash_line, "minishell: ", 20);
	ft_putstr_fd(bash_line, STDERR_FILENO);
	perror(args[i + 1]);
	set_exit_status(1);
	node->parent_die = 1;
	if (pipe_check(args, node))
	{
		if (isp(node->ori_args[i + 1]))
			node->redir_stop = 1;
		args_left_move(args, 1);
		args_left_move(node->ori_args, 1);
		if (isp(node->ori_args[i + 1]))
			node->redir_stop = 1;
		args_left_move(args, 0);
		args_left_move(node->ori_args, 0);
		if (isp(node->ori_args[i + 1]))
			node->redir_stop = 1;
		node->child_die = 1;
		return (0);
	}
	return (1);
}

void	args_left_move(char **args, int i)
{
	while (args[i] && args[i + 1])
	{
		free(args[i]);
		args[i] = ft_strdup(args[i + 1]);
		i++;
	}
	if (!args[i + 1])
	{
		free(args[i]);
		args[i] = NULL;
	}
}

bool	is_redir(char **args, int i, int j)
{
	return (args && args[i] && (args[i][j] == '<' || args[i][j] == '>'));
}
