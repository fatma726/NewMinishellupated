/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatmtahmdabrahym <fatmtahmdabrahym@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by fatmtahmdab      #+#    #+#             */
/*   Updated: 2025/08/26 19:45:00 by fatmtahmdab      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	**setpwd(t_node *node, char **envp)
{
	char	*curdir[2];
	size_t	n;

	curdir[0] = getcwd(0, 0);
	node->pwd = ft_strdup(ft_getenv("PWD", envp));
	if (chdir(node->pwd) == -1)
		return (free(node->pwd), node->pwd = curdir[0], envp = ft_setenv("PWD",
				node->pwd, envp), envp);
	curdir[1] = getcwd(0, 0);
	if (ft_strlen(curdir[0]) < ft_strlen(curdir[1]))
		n = ft_strlen(curdir[0]) + 1;
	else
		n = ft_strlen(curdir[1]) + 1;
	if (ft_strncmp(curdir[0], curdir[1], n))
	{
		free(node->pwd);
		node->pwd = curdir[0];
		envp = ft_setenv("PWD", node->pwd, envp);
		chdir(node->pwd);
	}
	else
		free(curdir[0]);
	free(curdir[1]);
	return (envp);
}

char	**shlvl_mod(int mod, char **envp)
{
	int		newval;
	char	*tmp;

	newval = ft_atoi(ft_getenv("SHLVL", envp)) + mod;
	if (newval > 1000)
		newval = 1;
	if (newval < 0)
		newval = 0;
	tmp = ft_itoa(newval);
	envp = ft_setenv("SHLVL", tmp, envp);
	free(tmp);
	return (envp);
}

static void	handle_shell_level_warning(int level)
{
	char	warning_msg[40];
	char	reset_msg[30];

	ft_strlcpy(warning_msg, "minishell: warning: shell level (", 40);
	ft_strlcpy(reset_msg, ") too high, resetting to 1", 30);
	ft_putstr_fd(warning_msg, STDERR_FILENO);
	ft_putnbr_fd(level, STDERR_FILENO);
	ft_putendl_fd(reset_msg, STDERR_FILENO);
}

char	**shlvl_plus_plus(char **envp)
{
	char	*str;

	str = ft_getenv("SHLVL", envp);
	if (!str || ft_atol(str) != ft_atoll(str))
		str = ft_itoa(1);
	else if (ft_atoi(str) + 1 <= 0)
		str = ft_itoa(0);
	else if (ft_atoi(str) + 1 >= 1000)
	{
		handle_shell_level_warning(ft_atoi(str) + 1);
		str = ft_itoa(1);
	}
	else
		str = ft_itoa(ft_atoi(str) + 1);
	if (!str)
	{
		strarrfree(envp);
		exit(EXIT_FAILURE);
	}
	envp = ft_setenv("SHLVL", str, envp);
	free(str);
	return (envp);
}
