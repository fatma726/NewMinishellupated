/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatmtahmdabrahym <fatmtahmdabrahym@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by kyung-ki          #+#    #+#             */
/*   Updated: 2025/08/28 16:21:29 by fatmtahmdab      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	args_left_move_i(char **args, t_node *node)
{
	int	i;

	i = 0;
	while (++i < node->redir_idx)
	{
		args_left_move(args, 1);
		args_left_move(node->ori_args, 1);
	}
}

void	double_lmove_idx_change(char **args, int *i)
{
	args_left_move(args, *i);
	args_left_move(args, *i);
	*i -= 1;
}

int	exec_redir(char **args, char **envp, t_node *node)
{
	int	i;
	int	ret;

	ret = 0;
	if (exec_check(args, envp, node))
		node->cmd = ft_strdup(args[0]);
	i = -1;
	while (args[++i] && !isp(node->ori_args[i]) && !node->redir_stop && !ret)
		if (isdlr(node->ori_args[i]))
			ret = left_double_redir(args, envp, &i, node);
	i = -1;
	while (args[++i] && !isp(node->ori_args[i]) && !node->redir_stop && !ret)
	{
		if (islr(node->ori_args[i]) || islrr(node->ori_args[i]))
			ret = left_redir(args, envp, &i, node);
		else if (isrr(node->ori_args[i]))
			ret = right_redir(args, &i, node);
		else if (isdrr(node->ori_args[i]))
			ret = right_double_redir(args, &i, node);
		else if (istlr(node->ori_args[i]))
			ret = left_double_redir(args, envp, &i, node);
	}
	if (node->cmd)
		free(node->cmd);
	return (node->cmd = NULL, ret);
}

int	print_err2(char **args, int i)
{
	char	bash_line[20];

	ft_strlcpy(bash_line, "bash: line 1: ", 20);
	ft_putstr_fd(bash_line, STDERR_FILENO);
	errno = ENOENT;
	perror(args[i + 2]);
	return (1);
}

int	print_err3(char **args, t_node *node, int *i)
{
	char	bash_line[30];
	char	here_doc[25];
	char	delimited[40];
	char	close_quote[5];

	ft_strlcpy(bash_line, "bash: line 1: warning: h", 30);
	ft_strlcpy(here_doc, "ere-document at line ", 25);
	ft_strlcpy(delimited, " delimited by end-of-file (wanted `", 40);
	ft_strlcpy(close_quote, "')", 5);
	ft_putstr_fd(bash_line, STDERR_FILENO);
	ft_putstr_fd(here_doc, STDERR_FILENO);
	ft_putnbr_fd(node->line_nbr, STDERR_FILENO);
	ft_putstr_fd(delimited, STDERR_FILENO);
	ft_putstr_fd(args[*i + 1], STDERR_FILENO);
	ft_putendl_fd(close_quote, STDERR_FILENO);
	return (1);
}
