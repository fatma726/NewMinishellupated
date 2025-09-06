/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_wildcard_helpers.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatmtahmdabrahym <fatmtahmdabrahym@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 23:25:54 by fatmtahmdab       #+#    #+#             */
/*   Updated: 2025/09/06 19:40:00 by fatmtahmdab      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/bonus.h"

static int	process_directory_entry(struct dirent *dr, char *pattern)
{
	if (dr->d_name[0] == '.')
		return (0);
	return (matches_pattern(dr->d_name, pattern));
}

int	count_matching_files(char *pattern)
{
	DIR				*dir;
	struct dirent	*dr;
	int				count;

	dir = opendir(".");
	if (!dir)
		return (0);
	count = 0;
	dr = readdir(dir);
	while (dr != NULL)
	{
		if (process_directory_entry(dr, pattern))
			count++;
		dr = readdir(dir);
	}
	closedir(dir);
	return (count);
}

static int	add_matching_file(char **newargs, int *j, char *filename)
{
	newargs[*j] = ft_strdup(filename);
	if (!newargs[*j])
		return (0);
	(*j)++;
	return (1);
}

int	expand_pattern(char **newargs, int *j, char *pattern)
{
	DIR				*dir;
	struct dirent	*dr;
	int				count;

	dir = opendir(".");
	if (!dir)
		return (0);
	count = 0;
	dr = readdir(dir);
	while (dr != NULL)
	{
		if (process_directory_entry(dr, pattern))
		{
			if (!add_matching_file(newargs, j, dr->d_name))
			{
				closedir(dir);
				return (0);
			}
			count++;
		}
		dr = readdir(dir);
	}
	closedir(dir);
	return (count);
}
