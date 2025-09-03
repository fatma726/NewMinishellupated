/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_alias.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatmtahmdabrahym <fatmtahmdabrahym@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by lcouturi          #+#    #+#             */
/*   Updated: 2025/08/28 17:56:44 by fatmtahmdab      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*get_command(char *str, int i, int offset, t_node *node)
{
	char	*str2;
	char	*str3;

	if (ft_strchr(" \t", node->aliases[i][ft_strlen(node->aliases[i]) - 1]))
	{
		str3 = expand_alias(ft_strdup(str + offset), node);
		str2 = ft_strjoin(ft_strchr(node->aliases[i], '=') + 1, str3);
		free(str3);
	}
	else
		str2 = ft_strjoin(ft_strchr(node->aliases[i], '=') + 1, str + offset);
	free(str);
	return (str2);
}

char	*expand_alias(char *str, t_node *node)
{
	int		i;
	int		i2;
	long	l;

	i = -1;
	i2 = 0;
	while (str[i2] && ft_strchr(" \t", str[i2]))
		i2++;
	if (!str[i2])
		return (str);
	while (node->aliases[++i])
	{
		l = ft_strchr(node->aliases[i], '=') - node->aliases[i];
		if (!ft_strncmp(node->aliases[i], str + i2, (size_t)l)
			&& (ft_strchr(" \t", str[i2 + l]) || !str[i2 + l]))
			str = get_command(str, i, (int)(i2 + l), node);
	}
	return (str);
}
