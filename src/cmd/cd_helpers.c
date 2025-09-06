/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_helpers.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatmtahmdabrahym <fatmtahmdabrahym@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by fatmtahmdabrahym #+#    #+#             */
/*   Updated: 2025/01/29 19:31:40 by fatmtahmdabrahym ###   ########.fr       */
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
