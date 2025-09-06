/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatmtahmdabrahym <fatmtahmdabrahym@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by fatmtahmdab      #+#    #+#             */
/*   Updated: 2025/08/26 19:45:00 by fatmtahmdab      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	envp = ft_setenv_envp("SHLVL", str, envp);
	free(str);
	return (envp);
}
