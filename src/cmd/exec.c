/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatmtahmdabrahym <fatmtahmdabrahym@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by lcouturi          #+#    #+#             */
/*   Updated: 2025/09/03 18:43:48 by fatmtahmdab      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	parse_background(char ***pargs)
{
	char	**args;
	int		last;

	args = *pargs;
	if (!args)
		return (0);
	last = 0;
	while (args[last])
		last++;
	if (last > 0 && is_ampersand(args[last - 1]))
	{
		args[last - 1] = NULL;
		return (1);
	}
	if (args[0] && is_ampersand(args[0]))
	{
		*pargs = args + 1;
		return (1);
	}
	return (0);
}

static char	**maybe_adjust_shlvl(char **envp, int argmode, int delta)
{
	if (argmode)
		return (shlvl_mod(delta, envp));
	return (envp);
}

static bool	is_builtin_command(char **args)
{
	if (!access(args[0], X_OK) || !ft_strncmp(args[0], "cd", 3)
		|| !ft_strncmp(args[0], "echo", 5) || !ft_strncmp(args[0], "env", 4)
		|| !ft_strncmp(args[0], "exit", 5) || !ft_strncmp(args[0], "export", 7)
		|| !ft_strncmp(args[0], "pwd", 4) || !ft_strncmp(args[0], "unset", 6))
		return (true);
	return (false);
}

bool	exec_check(char **args, char **envp, t_node *node)
{
	char	**paths;
	bool	ret;

	if (is_builtin_command(args))
		return (true);
	if (node->path_fallback)
		paths = ft_split(node->path_fallback, ':');
	else
		paths = ft_split(ft_getenv("PATH", envp), ':');
	if (!paths)
		exit(EXIT_FAILURE);
	ret = exec_check_loop(paths, args);
	strarrfree(paths);
	return (ret);
}

char	**cmd_exec(char **args, char **envp, t_node *node)
{
	int	pid;
	int	background;

	background = parse_background(&args);
	envp = maybe_adjust_shlvl(envp, node->argmode, -1);
	pid = fork();
	if (!pid)
		exec_proc(args, envp, node);
	post_wait_set_status(pid, background);
	envp = maybe_adjust_shlvl(envp, node->argmode, 1);
	return (envp);
}
