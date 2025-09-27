/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatmtahmdabrahym <fatmtahmdabrahym@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by lcouturi          #+#    #+#             */
/*   Updated: 2025/09/27 13:11:10 by fatmtahmdab      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	handle_home_cd(char **args, char **envp, int offset)
{
	char	home_error[30];

	(void)args;
	(void)offset;
	if (!ft_getenv("HOME", envp))
	{
		set_exit_status(EXIT_FAILURE);
		ft_strlcpy(home_error, "minishell: cd: HOME not set", 30);
		ft_putendl_fd(home_error, STDERR_FILENO);
		return (true);
	}
	chdir(ft_getenv("HOME", envp));
	return (false);
}

bool	handle_oldpwd_cd(char **args, char **envp, t_node *node, int offset)
{
	char	*oldpwd;
	char	*cwd;

	(void)args;
	(void)envp;
	(void)offset;
	oldpwd = getenv("OLDPWD");
	if (!oldpwd)
	{
		set_exit_status(EXIT_FAILURE);
		ft_putstr_fd("minishell: cd: OLDPWD not set\n", STDERR_FILENO);
		return (true);
	}
	chdir(oldpwd);
	cwd = getcwd(NULL, 0);
	if (cwd)
	{
		free(node->pwd);
		node->pwd = ft_strdup(cwd);
		free(cwd);
	}
	return (false);
}

bool	handle_chdir_error(char **args, int offset)
{
	char	chdir_error[60];

	set_exit_status(EXIT_FAILURE);
	ft_strlcpy(chdir_error, "minishell: cd: ", 50);
	ft_putstr_fd(chdir_error, STDERR_FILENO);
	ft_putstr_fd(args[1 + offset], STDERR_FILENO);
	ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
	return (true);
}

static bool	update_pwd(char *path, t_node *node)
{
	char	*cwd;

	if (path[0] == '/')
	{
		free(node->pwd);
		node->pwd = ft_strdup(path);
	}
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
	return (false);
}

bool	checks(char **args, char **envp, t_node *node, int offset)
{
	char	*path;
	int		chdir_result;

	if (!args[1 + offset])
		return (handle_home_cd(args, envp, offset));
	if (!ft_strncmp(args[1 + offset], "-", 2))
		return (handle_oldpwd_cd(args, envp, node, offset));
	path = args[1 + offset];
	chdir_result = chdir(path);
	if (chdir_result == -1)
		return (handle_chdir_error(args, offset));
	return (update_pwd(path, node));
}
