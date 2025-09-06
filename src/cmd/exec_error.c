/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatima <fatima@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by lcouturi          #+#    #+#             */
/*   Updated: 2025/08/28 20:48:30 by fatima           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	chkdir_check(DIR *check, int err, bool end)
{
	if (check)
	{
		closedir(check);
		errno = EISDIR;
	}
	else if (err == EACCES || errno == ENOTDIR)
		errno = EACCES;
	else if (!end)
		return (1);
	return (0);
}

static void	handle_directory_error(char **args, int err, int *status, bool end)
{
	char	bash_line[20];
	char	is_dir[20];

	errno = err;
	ft_strlcpy(bash_line, "minishell: ", 20);
	ft_putstr_fd(bash_line, STDERR_FILENO);
	if (err == EISDIR)
	{
		ft_putstr_fd(args[0], STDERR_FILENO);
		ft_strlcpy(is_dir, ": is a directory", 20);
		ft_putstr_fd(is_dir, STDERR_FILENO);
	}
	else
	{
		ft_putstr_fd(args[0], STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putstr_fd(strerror(errno), STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
	}
	*status = 126 + (end && errno != EISDIR && errno != EACCES);
}

void	chkdir(char **args, char **envp, bool end)
{
	DIR			*check;
	int			err;
	struct stat	stats;
	int			status;

	err = errno;
	check = opendir(args[0]);
	status = 0;
	stat(args[0], &stats);
	if (chkdir_check(check, err, end))
		return ;
	if (S_ISDIR(stats.st_mode))
		errno = EISDIR;
	err = errno;
	if (access(args[0], R_OK | X_OK) != 0 || err == EISDIR)
		handle_directory_error(args, err, &status, end);
	strarrfree(envp);
	strarrfree(args);
	exit(status);
}

void	exec_error(char **args, char **envp, char **paths)
{
	char	bash_line[20];
	char	*msg;

	ft_strlcpy(bash_line, "minishell: ", 20);
	ft_putstr_fd(bash_line, STDERR_FILENO);
	if (ft_strchr(args[0], '/') || !paths || !paths[0])
	{
		errno = ENOENT;
		ft_putstr_fd(args[0], STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putstr_fd(strerror(errno), STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
	}
	else
	{
		ft_putstr_fd(args[0], STDERR_FILENO);
		msg = ft_strdup(": command not found\n");
		ft_putstr_fd(msg, STDERR_FILENO);
		free(msg);
	}
	strarrfree(envp);
	if (paths)
		strarrfree(paths);
	strarrfree(args);
	exit(127);
}

void	checkdot(char **args, char **envp)
{
	char	*msg;
	char	bash_line[20];

	if (!ft_strncmp(args[0], ".", 2))
	{
		ft_strlcpy(bash_line, "minishell: ", 20);
		ft_putstr_fd(bash_line, STDERR_FILENO);
		ft_putstr_fd(args[0], STDERR_FILENO);
		msg = ft_strdup(": filename argument required\n");
		ft_putstr_fd(msg, STDERR_FILENO);
		free(msg);
		strarrfree(envp);
		strarrfree(args);
		exit(2);
	}
	else if (!ft_strncmp(args[0], "..", 3) || !ft_strncmp(args[0], ".", 2))
	{
		ft_strlcpy(bash_line, "minishell: ", 20);
		ft_putstr_fd(bash_line, STDERR_FILENO);
		ft_putstr_fd(args[0], STDERR_FILENO);
		msg = ft_strdup(": command not found\n");
		ft_putstr_fd(msg, STDERR_FILENO);
		free(msg);
		exit(127);
	}
}

/* removed unused local error_message_cmd */
