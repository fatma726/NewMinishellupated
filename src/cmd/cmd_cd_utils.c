/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_cd_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatmtahmdabrahym <fatmtahmdabrahym@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by fatima            #+#    #+#             */
/*   Updated: 2025/10/06 21:44:00 by fatmtahmdab      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

bool	validate_cd_args(char **args, int offset)
{
	if (args[1 + offset] && args[2 + offset])
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", STDERR_FILENO);
		set_exit_status(EXIT_FAILURE);
		return (false);
	}
	return (true);
}

void	handle_cd_arguments(char **args, char **envp, t_node *node, int offset)
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

char	**execute_cd(char **args, char **envp, t_node *node, int offset)
{
	char	*old_pwd;

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
