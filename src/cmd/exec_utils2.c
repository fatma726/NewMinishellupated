/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatmtahmdabrahym <fatmtahmdabrahym@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by lcouturi          #+#    #+#             */
/*   Updated: 2025/09/26 19:20:00 by fatmtahmdab      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_builtin_command(char **args)
{
	if (!access(args[0], X_OK) || !ft_strncmp(args[0], "cd", 3)
		|| !ft_strncmp(args[0], "echo", 5) || !ft_strncmp(args[0], "env", 4)
		|| !ft_strncmp(args[0], "exit", 5) || !ft_strncmp(args[0], "export", 7)
		|| !ft_strncmp(args[0], "pwd", 4) || !ft_strncmp(args[0], "unset", 6))
		return (true);
	return (false);
}
