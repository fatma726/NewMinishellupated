/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatmtahmdabrahym <fatmtahmdabrahym@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by fatmtahmdabrahym #+#    #+#             */
/*   Updated: 2025/09/03 19:00:52 by fatmtahmdab      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_env_i_option(char **args, char **envs, t_node *node)
{
	char	**args_new;
	char	**envp;

	envp = malloc(sizeof(char *));
	if (!envp)
		return ;
	envp[0] = NULL;
	envp = ft_setenv_envp("PATH", ft_getenv("PATH", envs), envp);
	args_new = strarrdup(args + 2);
	if (!args_new)
	{
		strarrfree(envp);
		return ;
	}
	envp = find_command(args_new, envp, node);
	strarrfree(args_new);
	strarrfree(envp);
}

void	handle_path_update(char *arg, t_node *node)
{
	if (!ft_strncmp(arg, "PATH=", 5) && node->path_fallback)
		free(node->path_fallback);
}

char	**handle_env_update(char *arg, char **envp, char *name, int j)
{
	char	*tmp;

	if (!ft_getenv(name, envp))
		return (ft_setenv_envp(name, arg + j + 1, envp));
	else if (j > 0 && arg[j - 1] == '+')
	{
		tmp = ft_strjoin(ft_getenv(name, envp), arg + j + 1);
		envp = ft_setenv_envp(name, tmp, envp);
		free(tmp);
		return (envp);
	}
	else
		return (ft_setenv_envp(name, arg + j + 1, envp));
}

bool	validate_export_identifier(char *arg)
{
	int	j;

	j = 0;
	if (!is_valid_identifier_start(arg[0]))
	{
		print_invalid_identifier_error(arg);
		return (false);
	}
	while (arg[j] && arg[j] != '=')
	{
		if (!is_valid_identifier_char(arg[j]))
		{
			print_invalid_identifier_error(arg);
			return (false);
		}
		j++;
	}
	return (true);
}

bool	process_export_arg(char *arg, char ***envp, t_node *node)
{
	int		j;
	char	*name;
	char	*tmp;

	if (!validate_export_identifier(arg))
		return (false);
	j = 0;
	while (arg[j] && arg[j] != '=')
		j++;
	tmp = ft_substr(arg, 0, (size_t)j);
	name = ft_strtrim(tmp, "+");
	free(tmp);
	handle_path_update(arg, node);
	if (arg[j] == '=')
		*envp = handle_env_update(arg, *envp, name, j);
	else
		*envp = ft_setenv_envp(name, "", *envp);
	free(name);
	return (true);
}
