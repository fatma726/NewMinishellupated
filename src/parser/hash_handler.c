/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatmtahmdabrahym <fatmtahmdabrahym@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by lcouturi          #+#    #+#             */
/*   Updated: 2025/08/28 00:43:05 by fatmtahmdab      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*hash_handler(char *str, t_node *node)
{
	unsigned int	i;
	char			*new_str;

	if (ft_strlen(str))
		add_history(str);
	node->syntax_flag = false;
	i = 0;
	while (str[i] && (str[i] != '#' || quote_check(str, (int)i, node)
			|| (i && !ft_strchr(" \t", str[i - 1]))))
		i++;
	if (i == ft_strlen(str))
		return (str);
	new_str = ft_substr(str, 0, i);
	free(str);
	return (new_str);
}
