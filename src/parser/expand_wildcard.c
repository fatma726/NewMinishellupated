/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_wildcard.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatmtahmdabrahym <fatmtahmdabrahym@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by lcouturi          #+#    #+#             */
/*   Updated: 2025/08/28 00:35:33 by fatmtahmdab      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	failcheck(char **files, int *i, char **newargs, char **args)
{
	if (!newargs[i[5]])
	{
		strarrfree(newargs);
		strarrfree(args);
		strarrfree(files);
		exit(EXIT_FAILURE);
	}
}

static bool	wildcard_loop(char **files, int *i, char **newargs, char **args)
{
	bool	flag;

	flag = 0;
	while (files[++i[1]])
	{
		if (files[i[1]][0])
		{
			newargs[i[5]] = malloc(ft_strlen(files[i[1]]) + 3);
			failcheck(files, i, newargs, args);
			ft_strlcpy(newargs[i[5]], "'", ft_strlen(files[i[1]]) + 3);
			ft_strlcat(newargs[i[5]], files[i[1]], ft_strlen(files[i[1]]) + 3);
			ft_strlcat(newargs[i[5]], "'", ft_strlen(files[i[1]]) + 3);
			i[5] += 1;
			flag = 1;
		}
	}
	if (!flag)
	{
		newargs[i[5]] = ft_strdup(args[i[2]]);
		failcheck(files, i, newargs, args);
		i[5] += 1;
	}
	return (flag);
}

static void	wildcard_handler(char **args, char **newargs, int *i, t_node *node)
{
	char	**files;
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
	if (wildcard_loop(files, i, newargs, args))
		node->escape_skip = false;
	strarrfree(files);
}

static void	expand_wildcard_loop(char **args, char **newargs, char **envp,
		t_node *node)
{
	int	i[6];

	i[2] = -1;
	i[5] = 0;
	while (args[++i[2]])
	{
		if (i[2] > 0 && (isrr(args[i[2] - 1]) || isdrr(args[i[2] - 1])
				|| islr(args[i[2] - 1]) || islrr(args[i[2] - 1])
				|| isdlr(args[i[2] - 1]) || istlr(args[i[2] - 1])))
		{
			newargs[i[5]++] = ft_strdup(args[i[2]]);
			continue ;
		}
		i[0] = -1;
		tilde_handler(args, i, envp);
		while (args[i[2]][++i[0]])
		{
			i[3] = quote_check(args[i[2]], i[0], node);
			if (!i[3] && args[i[2]][i[0]] == '*')
			{
				wildcard_handler(args, newargs, i, node);
				break ;
			}
		}
		if (!args[i[2]][i[0]])
			newargs[i[5]++] = ft_strdup(args[i[2]]);
	}
	newargs[i[5]] = NULL;
}

char	**expand_wildcard(char **args, char **envp, t_node *node)
{
	char	**newargs;
	size_t	size;

	size = strarrlen(args) + (size_t)get_arg_num(args, node) + 1;
	newargs = malloc(size * 8);
	if (!newargs)
	{
		strarrfree(args);
		exit(EXIT_FAILURE);
	}
	expand_wildcard_loop(args, newargs, envp, node);
	strarrfree(args);
	return (newargs);
}

char	*expand_wildcard_redir(char *pattern, t_node *node)
{
	char	**files;
	char	**split;
	char	asterisk[2];
	int		i;
	int		match_count;
	char	*result;

	if (!ft_strchr(pattern, '*'))
		return (ft_strdup(pattern));
	i = -1;
	ft_strlcpy(asterisk, "*", 2);
	split = escape_split(ft_strdup(pattern), asterisk, node);
	split = rm_quotes_wildcards(split, node);
	files = get_file_list(split && split[0] && split[0][0] == '.'
			&& ft_strchr(pattern, '.') < ft_strchr(pattern, '*'));
	while (files[++i])
		match(pattern, split, files, i);
	strarrfree(split);
	match_count = 0;
	result = NULL;
	i = -1;
	while (files[++i])
	{
		if (files[i][0])
		{
			match_count++;
			if (match_count == 1)
				result = ft_strdup(files[i]);
			else if (match_count == 2)
			{
				free(result);
				result = NULL;
				break ;
			}
		}
	}
	strarrfree(files);
	if (match_count == 0)
		return (ft_strdup(pattern));
	return (result);
}
