/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_wildcard_utils2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatmtahmdabrahym <fatmtahmdabrahym@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 18:06:00 by fatmtahmdab       #+#    #+#             */
/*   Updated: 2025/09/20 19:08:14 by fatmtahmdab      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/bonus.h"

static int	process_directory_entries(DIR *dir, char **matches, char *pattern)
{
	struct dirent	*dr;
	int				i;

	i = 0;
	dr = readdir(dir);
	while (dr != NULL)
	{
		if (process_directory_entry(dr, pattern))
		{
			matches[i] = ft_strdup(dr->d_name);
			if (!matches[i])
			{
				cleanup_matches(matches, i, dir);
				return (0);
			}
			i++;
		}
		dr = readdir(dir);
	}
	matches[i] = NULL;
	return (1);
}

void	sort_matches(char **matches)
{
	int		i;
	char	*temp;

	i = 0;
	while (matches[i + 1])
	{
		if (ft_strncmp(matches[i], matches[i + 1], 1000) > 0)
		{
			temp = matches[i];
			matches[i] = matches[i + 1];
			matches[i + 1] = temp;
			i = 0;
		}
		else
			i++;
	}
}

int	add_sorted_matches(char **newargs, int *j, char **matches)
{
	int	i;

	i = 0;
	while (matches[i])
	{
		if (!add_matching_file(newargs, j, matches[i]))
		{
			while (matches[i])
				free(matches[i++]);
			free(matches);
			return (0);
		}
		free(matches[i]);
		i++;
	}
	return (1);
}

int	collect_matches(char **matches, char *pattern)
{
	DIR	*dir;

	dir = opendir(".");
	if (!dir)
		return (0);
	if (!process_directory_entries(dir, matches, pattern))
		return (0);
	closedir(dir);
	return (1);
}
