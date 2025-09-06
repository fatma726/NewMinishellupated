/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_helpers2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatmtahmdabrahym <fatmtahmdabrahym@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by fatmtahmdabrahym #+#    #+#             */
/*   Updated: 2025/01/29 19:31:40 by fatmtahmdabrahym ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*build_env_pair_for_envp(const char *name, const char *value)
{
	char	*str;
	size_t	n;

	if (!value)
		return (ft_strdup(name));
	n = ft_strlen(name) + ft_strlen(value) + 2;
	str = malloc(n);
	if (!str)
		return (NULL);
	ft_strlcpy(str, name, n);
	ft_strlcat(str, "=", n);
	ft_strlcat(str, value, n);
	return (str);
}

static int	find_env_index_local(const char *name, char **envp)
{
	int	i;

	i = 0;
	while (envp[i] && (ft_strncmp(envp[i], name, ft_strlen(name))
			|| (envp[i][ft_strlen(name)] != '=' && envp[i][ft_strlen(name)])))
		i++;
	return (i);
}

static int	update_system_env(const char *name, const char *value)
{
	(void)name;
	(void)value;
	return (0);
}

char	**ft_setenv_envp(const char *name, const char *value, char **envp)
{
	int		i;
	char	*str;

	if (!name || !*name || ft_strchr(name, '='))
		return (envp);
	str = build_env_pair_for_envp(name, value);
	if (!str)
		exit(EXIT_FAILURE);
	i = find_env_index_local(name, envp);
	if (envp[i])
	{
		free(envp[i]);
		envp[i] = str;
	}
	else
		envp = strarradd_take(envp, str);
	if (update_system_env(name, value) == -1)
		return (envp);
	return (envp);
}
