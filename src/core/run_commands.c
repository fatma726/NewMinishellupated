/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_commands.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatmtahmdabrahym <fatmtahmdabrahym@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by kyung-ki          #+#    #+#             */
/*   Updated: 2025/08/30 02:17:52 by fatmtahmdab      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	**run(char **file, char **envp, t_node *node)
{
	int	i;

	i = -1;
	while (file[++i])
	{
		node->escape_skip = !ft_strchr(file[i], '\'') && !ft_strchr(file[i],
				'\"') && !ft_strchr(file[i], '\\');
		envp = subshell(hash_handler(file[i], node), envp, node);
	}
	return (envp);
}

char	**run_commands(char **envp, t_node *node)
{
	char	**file;
	int		fd;
	char	*path;

	if (!ft_getenv("HOME", envp))
		return (envp);
	path = ft_strjoin(ft_getenv("HOME", envp), "/.minishellrc");
	fd = open(path, O_RDONLY | O_SYMLINK);
	free(path);
	if (fd == -1)
		return (envp);
	file = get_file(fd);
	close(fd);
	envp = run(file, envp, node);
	free(file);
	return (envp);
}
