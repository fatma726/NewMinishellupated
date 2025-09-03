/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatmtahmdabrahym <fatmtahmdabrahym@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by lcouturi          #+#    #+#             */
/*   Updated: 2025/08/30 10:12:15 by fatmtahmdab      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	handle_cd_arguments(char **args, char **envp, t_node *node,
		bool offset)
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
	{
		// For cd -, node->pwd is already updated in handle_oldpwd_cd
		// No additional action needed here
	}
	else
	{
		// For regular paths, update node->pwd with current working directory
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
	bool	offset;
	char	*old_pwd;

	set_exit_status(EXIT_SUCCESS);
	if (node->pipe_flag || node->pipe_idx)
		return (envp);
	offset = 0;
	if (args[1] && !ft_strncmp(args[1], "--", 3))
		offset++;
	if (args[1 + offset] && !args[1 + offset][0] && !args[2 + offset])
	{
		envp = ft_setenv("OLDPWD", ft_getenv("PWD", envp), envp);
		return (envp);
	}
	// Save the current PWD before changing directory
	old_pwd = ft_strdup(ft_getenv("PWD", envp));
	if (checks(args, envp, node, offset))
	{
		free(old_pwd);
		return (envp);
	}
	handle_cd_arguments(args, envp, node, offset);
	envp = ft_setenv("OLDPWD", old_pwd, envp);
	envp = ft_setenv("PWD", node->pwd, envp);
	free(old_pwd);
	return (envp);
}
