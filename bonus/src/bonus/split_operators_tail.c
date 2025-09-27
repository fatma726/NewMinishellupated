/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_operators_tail.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatmtahmdabrahym <fatmtahmdabrahym@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by fatima            #+#    #+#             */
/*   Updated: 2025/09/27 17:20:00 by fatmtahmdab      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"
#include "../../include/bonus.h"

char	**split_operators_tail(char *s, size_t i, char **envp, t_node *n)
{
	char	*new_str;
	int		skip;

	if (!s[i])
	{
		free(s);
		return (envp);
	}
	if (!get_exit_status() && s[i] == '|' && s[i + 1] == '|')
		advance_to(s, &i, n, '|');
	if (get_exit_status() && s[i] == '&' && s[i + 1] == '&')
		advance_to(s, &i, n, '&');
	if (s[i] == '&' && s[i + 1] != '&')
		skip = 1;
	else
		skip = 2;
	new_str = ft_substr(s, (unsigned int)(i + (size_t)skip),
			ft_strlen(s) - (i + (size_t)skip));
	free(s);
	return (split_operators(new_str, envp, n));
}
