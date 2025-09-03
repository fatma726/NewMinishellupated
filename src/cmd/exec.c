/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatmtahmdabrahym <fatmtahmdabrahym@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by lcouturi          #+#    #+#             */
/*   Updated: 2025/08/28 15:52:16 by fatmtahmdab      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	**cmd_exec(char **args, char **envp, t_node *node)
{
	int	pid;
	int	status;
	bool	background = false;
	int	last;

	// Check if this command should run in background
	if (args)
	{
		last = 0;
		while (args[last])
			last++;
		if (last > 0 && is_ampersand(args[last - 1]))
		{
			background = true;
			args[last - 1] = NULL;
		}
		else if (args[0] && is_ampersand(args[0]))
		{
			background = true;
			args = args + 1;
		}
	}

	if (node->argmode)
		envp = shlvl_mod(-1, envp);
	pid = fork();
	if (!pid)
		exec_proc(args, envp, node);
	
	if (background)
	{
		// Don't wait for background processes
		set_exit_status(0);
	}
	else
	{
		waitpid(pid, &status, 0);
		if (status == 2 || status == 3)
			set_exit_status(128 + status);
		else
			set_exit_status(status / 256);
	}
	
	if (node->argmode)
		envp = shlvl_mod(1, envp);
	return (envp);
}

static char	*build_path(char *dir, char *cmd)
{
	size_t	n;
	char	*path;

	n = ft_strlen(dir) + ft_strlen(cmd) + 2;
	path = malloc(n);
	if (!path)
		return (NULL);
	ft_strlcpy(path, dir, n);
	ft_strlcat(path, "/", n);
	ft_strlcat(path, cmd, n);
	return (path);
}

static bool	exec_check_loop(char **paths, char **args)
{
	size_t	i;
	char	*path;

	i = 0;
	while (paths[i])
	{
		path = build_path(paths[i], args[0]);
		if (!path)
		{
			strarrfree(paths);
			exit(EXIT_FAILURE);
		}
		if (!access(path, X_OK))
		{
			free(path);
			return (1);
		}
		free(path);
		i++;
	}
	return (0);
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
