/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_wildcard_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatmtahmdabrahym <fatmtahmdabrahym@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by lcouturi          #+#    #+#             */
/*   Updated: 2025/09/06 19:17:00 by fatmtahmdab      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/bonus.h"

void	cleanup_and_return(char **newargs, int j, char **args)
{
	while (j > 0)
		free(newargs[--j]);
	free(newargs);
	strarrfree(args);
}

static int	process_wildcard_pattern(char **newargs, int *j, char *pattern)
{
	int	matches;

	matches = expand_pattern(newargs, j, pattern);
	if (matches == -1)
		return (-1);
	if (matches == 0)
	{
		newargs[*j] = ft_strdup(pattern);
		if (!newargs[*j])
			return (-1);
		(*j)++;
	}
	return (0);
}

static int	process_regular_arg(char **newargs, int *j, char *arg)
{
	newargs[*j] = ft_strdup(arg);
	if (!newargs[*j])
		return (-1);
	(*j)++;
	return (0);
}

int	count_wildcard_matches(char **args)
{
	int	i;
	int	count;

	i = -1;
	count = 0;
	while (args[++i])
	{
		if (ft_strchr(args[i], '*'))
			count += count_matching_files(args[i]);
	}
	return (count);
}

int	process_all_args(char **args, char **newargs)
{
	int	i;
	int	j;

	j = 0;
	i = -1;
	while (args[++i])
	{
		if (ft_strchr(args[i], '*'))
		{
			if (process_wildcard_pattern(newargs, &j, args[i]) == -1)
				return (-1);
		}
		else
		{
			if (process_regular_arg(newargs, &j, args[i]) == -1)
				return (-1);
		}
	}
	newargs[j] = NULL;
	return (0);
}
