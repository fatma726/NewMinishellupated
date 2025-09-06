/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_arg_num.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatmtahmdabrahym <fatmtahmdabrahym@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by lcouturi          #+#    #+#             */
/*   Updated: 2025/08/28 00:37:58 by fatmtahmdab      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	get_arg_num_loop(char **args, int *i, int *n, t_node *node)
{
	char	**files;
	int		n2;
	char	**split;
	char	asterisk[2];

	i[1] = -1;
	ft_strlcpy(asterisk, "*", 2);
	split = escape_split(ft_strdup(args[i[2]]), asterisk, node);
	split = rm_quotes_wildcards(split, node);
	files = get_file_list(split && split[0] && split[0][0] == '.'
			&& ft_strchr(args[i[2]], '.') < ft_strchr(args[i[2]], '*'));
	while (files[++i[1]])
		match(args[i[2]], split, files, i[1]);
	strarrfree(split);
	i[1] = -1;
	n2 = 0;
	while (files[++i[1]])
		if (files[i[1]][0])
			n2++;
	if (!n2)
		*n += 1;
	else
		*n += n2;
	strarrfree(files);
}

int	get_arg_num(char **args, t_node *node)
{
	int	i[5];
	int	n;

	i[2] = -1;
	n = 0;
	while (args[++i[2]])
	{
		i[0] = -1;
		while (args[i[2]][++i[0]])
		{
			i[3] = quote_check(args[i[2]], i[0], node);
			if (!i[3] && args[i[2]][i[0]] == '*')
			{
				get_arg_num_loop(args, i, &n, node);
				break ;
			}
		}
	}
	return (n);
}
