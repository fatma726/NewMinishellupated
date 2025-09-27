/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_helpers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatmtahmdabrahym <fatmtahmdabrahym@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by fatmtahmdabrahym #+#    #+#             */
/*   Updated: 2025/01/29 19:31:40 by fatmtahmdabrahym ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_setenv_var(const char *name, const char *value, int overwrite)
{
	(void)name;
	(void)value;
	(void)overwrite;
	return (0);
}

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
	return (envp);
}

/* moved to env_helpers2.c to satisfy function-count norm */
