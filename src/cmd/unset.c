/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatmtahmdabrahym <fatmtahmdabrahym@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by kyung-ki          #+#    #+#             */
/*   Updated: 2025/08/27 22:47:11 by fatmtahmdab      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	**cmd_unset(char **args, char **envp, t_node *node)
{
	int		flag;

	flag = 1;
	if (args[1] && args[1][0] == '-')
	{
		handle_unset_option_error(args);
		return (envp);
	}
	process_unset_args(args, envp, node, &flag);
	return (envp);
}
