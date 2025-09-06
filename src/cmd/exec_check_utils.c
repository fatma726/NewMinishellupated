/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_check_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatmtahmdabrahym <fatmtahmdabrahym@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 17:00:00 by fatmtahmdab       #+#    #+#             */
/*   Updated: 2025/09/03 17:00:00 by fatmtahmdab      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*build_candidate(char *dir, char *cmd)
{
	char	*path;
	size_t	n;

	n = ft_strlen(dir) + ft_strlen(cmd) + 2;
	path = malloc(n);
	if (!path)
		return (NULL);
	ft_strlcpy(path, dir, n);
	ft_strlcat(path, "/", n);
	ft_strlcat(path, cmd, n);
	return (path);
}

bool	exec_check_loop(char **paths, char **args)
{
	size_t	i;
	char	*path;

	i = 0;
	while (paths[i])
	{
		path = build_candidate(paths[i], args[0]);
		if (!path)
		{
			strarrfree(paths);
			exit(EXIT_FAILURE);
		}
		if (!access(path, X_OK))
		{
			free(path);
			return (true);
		}
		free(path);
		i++;
	}
	return (false);
}
