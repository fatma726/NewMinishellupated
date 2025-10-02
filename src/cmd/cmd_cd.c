/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatmtahmdabrahym <fatmtahmdabrahym@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by fatima            #+#    #+#             */
/*   Updated: 2025/09/30 23:00:00 by fatmtahmdab      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

bool	check_arg_count_with_slash(char **args, char **envp, int offset)
{
	char	*msg;

	(void)envp;
	if (strarrlen(args) > 4 + (size_t)offset)
	{
		set_exit_status(EXIT_FAILURE);
		msg = ft_strdup(": too many arguments\n");
		ft_putstr_fd(msg, STDERR_FILENO);
		free(msg);
		return (true);
	}
	return (false);
}

bool	check_arg_count_without_slash(char **args, char **envp, int offset)
{
	char	*msg;

	(void)envp;
	if (strarrlen(args) > 3 + (size_t)offset)
	{
		set_exit_status(EXIT_FAILURE);
		msg = ft_strdup(": too many arguments\n");
		ft_putstr_fd(msg, STDERR_FILENO);
		free(msg);
		return (true);
	}
	return (false);
}

bool	check_argument_count(char **args, char **envp, int offset)
{
	if (args[1 + offset] && !ft_strncmp(args[1 + offset], "/", 1))
		return (check_arg_count_with_slash(args, envp, offset));
	else
		return (check_arg_count_without_slash(args, envp, offset));
}

static void	handle_cd_arguments(char **args, char **envp, t_node *node,
			int offset)
{
	char	*home_path;
	char	*cwd;

	if (!args[1 + offset])
	{
		free(node->pwd);
		home_path = ft_getenv("HOME", envp);
		node->pwd = ft_strdup(home_path);
	}
	else if (!ft_strncmp(args[1 + offset], "-", 2))
		;
	else
	{
		cwd = getcwd(NULL, 0);
		if (cwd)
		{
			free(node->pwd);
			node->pwd = ft_strdup(cwd);
			free(cwd);
		}
	}
}

char	**cmd_cd(char **args, char **envp, t_node *node)
{
	int		offset;
	char	*old_pwd;

	set_exit_status(EXIT_SUCCESS);
	if (node->pipe_flag || node->pipe_idx)
		return (envp);
	offset = 0;
	if (args[1] && !ft_strncmp(args[1], "--", 3))
		offset++;
	if (args[1 + offset] && !args[1 + offset][0] && !args[2 + offset])
		return (ft_setenv_envp("OLDPWD", ft_getenv("PWD", envp), envp));
	old_pwd = ft_strdup(ft_getenv("PWD", envp));
	if (checks(args, envp, node, offset))
	{
		free(old_pwd);
		return (envp);
	}
	handle_cd_arguments(args, envp, node, offset);
	envp = ft_setenv_envp("OLDPWD", old_pwd, envp);
	envp = ft_setenv_envp("PWD", node->pwd, envp);
	free(old_pwd);
	return (envp);
}
