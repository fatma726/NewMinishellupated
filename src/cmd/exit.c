/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatmtahmdabrahym <fatmtahmdabrahym@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by kyung-ki          #+#    #+#             */
/*   Updated: 2025/09/21 16:39:06 by fatmtahmdab      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/readline.h>
#include <readline/history.h>

bool	ft_isalldigit(char *str)
{
	int	i;

	if (!str || !str[0])
		return (false);
	i = 0;
	if (str[0] == '+' || str[0] == '-')
		i++;
	if (!str[i])
		return (false);
	while (str[i] && ft_isdigit(str[i]))
		i++;
	while (str[i] && ft_strchr(" \t", str[i]))
		i++;
	return (str[i] == '\0');
}

void	handle_exit_message(void)
{
	char	exit_msg[5];

	ft_strlcpy(exit_msg, "exit", 5);
	ft_putendl_fd(exit_msg, STDOUT_FILENO);
}

void	handle_numeric_error(char *arg)
{
	char	exit_error[20];
	char	numeric_error[30];

	set_exit_status(255);
	ft_strlcpy(exit_error, "minishell: exit: ", 20);
	ft_strlcpy(numeric_error, ": numeric argument required\n", 30);
	ft_putstr_fd(exit_error, STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putstr_fd(numeric_error, STDERR_FILENO);
}

void	handle_too_many_args(void)
{
	char	too_many[37];

	set_exit_status(EXIT_FAILURE);
	ft_strlcpy(too_many, "minishell: exit: too many arguments\n", 37);
	ft_putstr_fd(too_many, STDERR_FILENO);
}

void	cmd_exit(char **args, char **envp, t_node *node)
{
	bool	should_exit;

	if (!node->exit_flag)
		return ;
	should_exit = true;
	if (strarrlen(args) > 1)
		should_exit = handle_exit_with_args(args);
	else
		set_exit_status(EXIT_SUCCESS);
	if (should_exit && isatty(STDIN_FILENO) && !node->argmode)
		handle_exit_message();
	if (should_exit)
	{
		if (!isatty(STDIN_FILENO) && !node->argmode)
			return ;
		cleanup_and_exit(args, envp, node);
	}
}
