/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatmtahmdabrahym <fatmtahmdabrahym@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by lcouturi          #+#    #+#             */
/*   Updated: 2025/09/06 19:17:00 by fatmtahmdab      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/bonus.h"

void	wildcard_handler(char **args, char **newargs, int *i, t_node *node)
{
	char	*pattern;
	int		j;

	pattern = args[i[2]];
	j = i[5];
	if (expand_pattern(newargs, &j, pattern))
		i[5] = j;
	else
	{
		newargs[i[5]++] = ft_strdup(pattern);
		if (!newargs[i[5] - 1])
		{
			strarrfree(newargs);
			strarrfree(args);
			exit(1);
		}
	}
	(void)node;
}
