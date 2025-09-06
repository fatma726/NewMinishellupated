/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   right_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatmtahmdabrahym <fatmtahmdabrahym@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by kyung-ki          #+#    #+#             */
/*   Updated: 2025/09/06 18:31:20 by fatmtahmdab      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	right_redir(char **args, int *i, t_node *node)
{
	int	fd;

	fd = open_redir_out(args, *i, node, O_WRONLY | O_CREAT | O_TRUNC);
	if (fd < 0)
		return (1);
	node->right_flag = 1;
	if (args[*i][0] == '2')
		dup2(fd, STDERR_FILENO);
	else
		dup2(fd, STDOUT_FILENO);
	close(fd);
	move_redir_args(args, node->ori_args, i);
	return (*i -= 1, 0);
}

int	right_double_redir(char **args, int *i, t_node *node)
{
	int	fd;

	fd = open_redir_out(args, *i, node, O_WRONLY | O_CREAT | O_APPEND);
	if (fd < 0)
		return (1);
	node->right_flag = 1;
	dup2(fd, STDOUT_FILENO);
	close(fd);
	move_redir_args(args, node->ori_args, i);
	return (*i -= 1, 0);
}
