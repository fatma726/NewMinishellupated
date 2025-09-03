/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pipe2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatima <fatima@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 09:20:31 by kyung-ki          #+#    #+#             */
/*   Updated: 2025/09/03 10:08:02 by fatima           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	backup_restor(t_node *node)
{
	dup2(node->backup_stdout, STDOUT_FILENO);
	dup2(node->backup_stdin, STDIN_FILENO);
}

char	**split_before_pipe_args(char **args, t_node *node)
{
	char	**temp;
	int		i;
	int		j;

	i = -1;
	temp = malloc(((size_t)node->pipe_idx + 1) * sizeof(char *));
	if (!temp)
		exit(EXIT_FAILURE);
	while (++i < node->pipe_idx - 1)
	{
		temp[i] = malloc(ft_strlen(args[i]) + 1);
		if (!temp[i])
			exit(EXIT_FAILURE);
		j = -1;
		while (args[i][++j])
			temp[i][j] = args[i][j];
		temp[i][j] = '\0';
	}
	temp[i] = NULL;
	return (temp);
}

static void	repeat_exec(char **args, char **envp, t_node *node, int pid)
{
	char	**new_ori_args;

	if (!pid)
		exec_child(args, envp, node);
	else
	{
		backup_restor(node);
		new_ori_args = strarrdup(node->ori_args + node->pipe_idx);
		strarrfree(node->ori_args);
		node->ori_args = new_ori_args;
		exec_parents(strarrdup(args + node->pipe_idx), strarrdup(envp), node);
	}
	backup_restor(node);
	waitpid(pid, 0, 0);
}

char	**repeat(char **args, char **envp, t_node *node)
{
    int	pid;
    int	redir_err;

    pid = 0;
    node->redir_flag = redir_chk(node->ori_args);
    redir_err = 0;
    /* detect pipeline first to decide behavior on redir errors */
    (void)pipe_check(args, node);
    if (node->redir_flag)
        redir_err = redir_excute(args, envp, node, 0);
    /* redirections may remove tokens and shift indices; refresh pipe index */
    (void)pipe_check(args, node);
    if (redir_err)
    {
        if (node->pipe_flag)
            node->child_die = 1;
        else
            return (envp);
    }
	if (node->pipe_flag)
	{
		pipe(node->fds);
		pid = fork();
		if (pid < 0)
			return (envp);
	}
	else
		return (one_commnad(args, envp, node));
	repeat_exec(args, envp, node, pid);
	return (envp);
}

char	**execute(char **args, char **envp, t_node *node)
{
	node->backup_stdout = dup(STDOUT_FILENO);
	node->backup_stdin = dup(STDIN_FILENO);
	envp = repeat(args, envp, node);
	backup_restor(node);
	return (cloturn(node->backup_stdout, node->backup_stdin, envp));
}
