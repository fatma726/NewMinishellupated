/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_quotes_core.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatmtahmdabrahym <fatmtahmdabrahym@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by fatima            #+#    #+#             */
/*   Updated: 2025/10/06 21:32:09 by fatmtahmdab      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static char	*alloc_str(char *str, int *i, t_node *node)
{
	int		l;
	char	*newstr;

	i[0] = -1;
	l = 0;
	while (str[++i[0]])
	{
		i[3] = quote_check(str, i[0], node);
		if (str[i[0]] == '"' && i[3] != 1)
			continue ;
		else if (str[i[0]] == '\'' && i[3] != 2)
			continue ;
		else if (str[i[0]] == '\\' && i[3] == 0)
			continue ;
		else
			l++;
	}
	newstr = malloc(((size_t)l + 1) * sizeof(char));
	if (!newstr)
	{
		free(str);
		exit(EXIT_FAILURE);
	}
	return (newstr);
}

static char	*rm_quotes_loop(char *str, t_node *node)
{
	int		i[5];
	int		j;
	char	*newstr;

	if (str && str[0] == (char)WILDMARK)
		return (return_marked_unchanged(str));
	j = 0;
	newstr = alloc_str(str, i, node);
	i[0] = -1;
	while (str[++i[0]])
	{
		i[3] = quote_check(str, i[0], node);
		if (str[i[0]] == '"' && i[3] != 1)
			continue ;
		else if (str[i[0]] == '\'' && i[3] != 2)
			continue ;
		else if (str[i[0]] == '\\' && i[3] == 0)
			continue ;
		else
			newstr[j++] = str[i[0]];
	}
	newstr[j] = '\0';
	free(str);
	return (newstr);
}

static void	quote_pipe_check(char **args, t_node *node)
{
	int	i;
	int	j;

	i = 0;
	node->quota_idx_j = 0;
	j = 0;
	while (args[i])
	{
		j = 0;
		while (args[i][j] && args[i][j + 1])
		{
			if (args[i][j] == '\'' && args[i][j + 1] == '|' &&
				args[i][j + 2] == '\'')
				node->quota_pipe_idx_arr[node->quota_pipe_cnt++] = i;
			else if (args[i][j] == '"' && args[i][j + 1] == '|' &&
				args[i][j + 2] == '"')
				node->quota_pipe_idx_arr[node->quota_pipe_cnt++] = i;
			else if (args[i][j] == '\\' && args[i][j + 1] == '|')
				node->quota_pipe_idx_arr[node->quota_pipe_cnt++] = i;
			j++;
		}
		i++;
	}
}

char	**rm_quotes(char **args, t_node *node)
{
	int	i;

	i = -1;
	quote_pipe_check(args, node);
	if (node->escape_skip)
	{
		strip_wildmarks_inplace(args);
		return (args);
	}
	while (args[++i])
		args[i] = rm_quotes_loop(args[i], node);
	return (args);
}

char	**rm_quotes_wildcards(char **args, t_node *node)
{
	int	i;

	if (node->escape_skip)
	{
		strip_wildmarks_inplace(args);
		return (args);
	}
	i = -1;
	while (args[++i])
		args[i] = rm_quotes_loop(args[i], node);
	return (args);
}
