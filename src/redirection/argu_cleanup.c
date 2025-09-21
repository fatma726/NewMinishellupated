/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argu_cleanup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatmtahmdabrahym <fatmtahmdabrahym@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by fatmtahmdab       #+#    #+#             */
/*   Updated: 2025/09/20 13:19:54 by fatmtahmdab      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	argu_cleanup(char **args, char **args2, int k, int len)
{
	const int	init_k = k;

	free(args[k]);
	free(args[k + 1]);
	if (k + 2 == len)
	{
		args[k] = NULL;
		args[k + 1] = NULL;
	}
	else
	{
		args[k + 1] = NULL;
		while (k + 2 < len)
		{
			args[k] = ft_strdup(args[k + 2]);
			if (!args[k])
				return ;
			free(args[k + 2]);
			args[k++ + 2] = NULL;
		}
	}
	if (args2)
		argu_cleanup(args2, NULL, init_k, len);
}

void	argu_left_change(char **args, t_node *node)
{
	int	i;
	int	k;
	int	len;

	i = -1;
	len = (int)strarrlen(args);
	while (args[++i])
	{
		if (isdlr(node->ori_args[i]))
		{
			k = i;
			if (k + 1 == len)
			{
				free(args[k]);
				free(node->ori_args[k]);
				args[k] = NULL;
				node->ori_args[k] = NULL;
			}
			else
				argu_cleanup(args, node->ori_args, k, len);
		}
	}
}
