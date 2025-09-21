/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatmtahmdabrahym <fatmtahmdabrahym@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by kyung-ki          #+#    #+#             */
/*   Updated: 2025/09/20 14:32:02 by fatmtahmdab      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/readline.h>
#include <readline/history.h>

static bool	check_overflow_limits(char *arg)
{
	if (ft_strlen(arg) > 20)
		return (true);
	if (ft_strncmp(arg, "9223372036854775808", 20) == 0)
		return (true);
	if (ft_strncmp(arg, "-9223372036854775809", 21) == 0)
		return (true);
	return (false);
}

bool	handle_exit_with_args(char **args)
{
	long long	exit_num;

	if (!ft_isalldigit(args[1]))
	{
		handle_numeric_error(args[1]);
		return (true);
	}
	if (strarrlen(args) > 2)
	{
		handle_too_many_args();
		return (false);
	}
	exit_num = ft_atoll(args[1]);
	if (check_overflow_limits(args[1]))
	{
		handle_numeric_error(args[1]);
		return (true);
	}
	set_exit_status((int)(exit_num & 0xFF));
	return (true);
}

void	cleanup_and_exit(char **args, char **envp, t_node *node)
{
	free(node->pwd);
	if (node->path_fallback)
		free(node->path_fallback);
	if (node->ori_args)
	{
		strarrfree(node->ori_args);
		node->ori_args = NULL;
	}
	strarrfree(args);
	strarrfree(envp);
	clear_history();
	restore_termios();
	exit(get_exit_status());
}
