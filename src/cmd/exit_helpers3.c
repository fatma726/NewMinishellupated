/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_helpers3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatmtahmdabrahym <fatmtahmdabrahym@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by fatmtahmdabrahym #+#    #+#             */
/*   Updated: 2025/08/30 18:59:00 by fatmtahmdab      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
