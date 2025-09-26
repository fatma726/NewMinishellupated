/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatmtahmdabrahym <fatmtahmdabrahym@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by fatmtahmdabrahym #+#    #+#             */
/*   Updated: 2025/01/29 19:31:40 by fatmtahmdabrahym ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_valid_identifier(char *str)
{
	int	i;

	if (!str || !str[0] || ft_isdigit(str[0]))
		return (false);
	i = 0;
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (false);
		i++;
	}
	return (true);
}

int	find_envkey(char *str, char *envp)
{
	int	i;

	i = 0;
	while (str[i] && envp[i] && str[i] == envp[i] && envp[i] != '=')
		i++;
	return (str[i] == '\0' && envp[i] == '=');
}

static void	clear_path_fallback_if(char *str, t_node *node)
{
	if (!ft_strncmp(str, "PATH", 5) && node->path_fallback)
	{
		free(node->path_fallback);
		node->path_fallback = NULL;
	}
}

char	**delete_env(char *str, char **envp, t_node *node, int *flag)
{
	int	i;
	int	last;

	last = (int)strarrlen(envp);
	if (last < 1)
		return (envp);
	clear_path_fallback_if(str, node);
	i = -1;
	while (envp[++i])
	{
		if (find_envkey(str, envp[i]))
		{
			free(envp[i]);
			envp[i] = envp[last - 1];
			envp[last - 1] = NULL;
			*flag = 1;
			return (envp);
		}
	}
	*flag = 1;
	return (envp);
}

void	handle_unset_option_error(char **args)
{
	char	unset_error[25];
	char	invalid1[35];
	char	invalid2[30];
	char	usage[15];

	ft_strlcpy(unset_error, "minishell: unset: ", 25);
	ft_putstr_fd(unset_error, STDERR_FILENO);
	ft_putstr_fd(args[1], STDERR_FILENO);
	ft_strlcpy(invalid1, ": invalid option\nunset: usage: unset ", 35);
	ft_putstr_fd(invalid1, STDERR_FILENO);
	ft_strlcpy(invalid2, "[-f] [-v] [-n] ", 30);
	ft_putstr_fd(invalid2, STDERR_FILENO);
	ft_strlcpy(usage, "[name ...]\n", 15);
	ft_putstr_fd(usage, STDERR_FILENO);
	set_exit_status(2);
}
