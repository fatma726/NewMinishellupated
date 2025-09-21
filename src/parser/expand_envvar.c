/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_envvar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatmtahmdabrahym <fatmtahmdabrahym@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by lcouturi          #+#    #+#             */
/*   Updated: 2025/09/20 16:44:56 by fatmtahmdab      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	insert_int(char *str, int *i)
{
	int	j;

	j = 1000000000;
	while (j)
	{
		if (get_exit_status() / j)
			str[i[1]++] = (char)(get_exit_status() / j % 10 + '0');
		j /= 10;
	}
	if (!get_exit_status())
		str[i[1]++] = '0';
	i[0] += 2;
}

static void	expand_envvar_loop(char **str, char **envp, t_node *node)
{
	int	i[7];

	i[0] = 0;
	i[1] = 0;
	while (str[0][i[0]])
	{
		process_envvar(str, envp, node, i);
	}
	str[1][i[1]] = '\0';
}

char	*expand_envvar(char *str, char **envp, t_node *node)
{
	int		i[6];
	char	*strs[2];

	i[0] = -1;
	i[5] = 0;
	while (str[++i[0]])
	{
		get_length(str, envp, i, node);
		if (!str[i[0]])
			break ;
	}
	if (i[5] < 4096)
		i[5] = 4096;
	strs[1] = malloc(((size_t)i[5] + 1) * sizeof(char));
	if (!strs[1])
	{
		free(str);
		strarrfree(envp);
		exit(EXIT_FAILURE);
	}
	strs[0] = str;
	expand_envvar_loop(strs, envp, node);
	free(str);
	return (strs[1]);
}
