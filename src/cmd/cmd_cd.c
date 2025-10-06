/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_cd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatmtahmdabrahym <fatmtahmdabrahym@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by fatima            #+#    #+#             */
/*   Updated: 2025/10/06 21:32:02 by fatmtahmdab      ###   ########.fr       */
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

char	**cmd_cd(char **args, char **envp, t_node *node)
{
	int		offset;

	set_exit_status(EXIT_SUCCESS);
	if (node->pipe_flag || node->pipe_idx)
		return (envp);
	offset = 0;
	if (args[1] && !ft_strncmp(args[1], "--", 3))
		offset++;
	if (!validate_cd_args(args, offset))
		return (envp);
	if (args[1 + offset] && !args[1 + offset][0] && !args[2 + offset])
		return (ft_setenv_envp("OLDPWD", ft_getenv("PWD", envp), envp));
	return (execute_cd(args, envp, node, offset));
}
