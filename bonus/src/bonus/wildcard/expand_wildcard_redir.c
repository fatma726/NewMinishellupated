/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_wildcard_redir.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatima <fatima@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by fatima            #+#    #+#             */
/*   Updated: 2025/09/04 10:06:27 by fatima           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	process_file_matches(char **files, int *match_count, char **result)
{
	int	i;

	i = -1;
	while (files[++i])
	{
		if (files[i][0])
		{
			(*match_count)++;
			if (*match_count == 1)
				*result = ft_strdup(files[i]);
			else if (*match_count == 2)
			{
				free(*result);
				*result = NULL;
				break ;
			}
		}
	}
}

static char	**prepare_files_for_pattern(char *pattern, t_node *node)
{
	char		charset[2];
	char		**split;
	char		**files;
	int			i;

	charset[0] = '*';
	charset[1] = '\0';
	split = escape_split(ft_strdup(pattern), charset, node);
	split = rm_quotes_wildcards(split, node);
	files = get_file_list(split && split[0] && split[0][0] == '.'
			&& ft_strchr(pattern, '.') < ft_strchr(pattern, '*'));
	i = -1;
	while (files[++i])
		match(pattern, split, files, i);
	strarrfree(split);
	return (files);
}

char	*expand_wildcard_redir(char *pattern, t_node *node)
{
	char		**files;
	int			match_count;
	char		*result;

	if (!ft_strchr(pattern, '*'))
		return (ft_strdup(pattern));
	files = prepare_files_for_pattern(pattern, node);
	match_count = 0;
	result = NULL;
	process_file_matches(files, &match_count, &result);
	strarrfree(files);
	if (match_count == 0)
		return (ft_strdup(pattern));
	return (result);
}
