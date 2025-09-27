/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_redir4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatmtahmdabrahym <fatmtahmdabrahym@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by kyung-ki          #+#    #+#             */
/*   Updated: 2025/09/24 11:16:00 by fatmtahmdab      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Intentionally simple holder file to satisfy norm function count limits */

int	left_redir_error_public(const char *s, int type, char *tmp)
{
	if (type == 0)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(s, STDERR_FILENO);
		ft_putendl_fd(": ambiguous redirect", STDERR_FILENO);
	}
	else
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(s, STDERR_FILENO);
		ft_putendl_fd(": No such file or directory", STDERR_FILENO);
	}
	set_exit_status(1);
	if (tmp)
		free(tmp);
	return (1);
}

void	double_lmove_idx_change(char **args, int *i)
{
	args_left_move(args, *i);
	args_left_move(args, *i);
	*i -= 1;
}
