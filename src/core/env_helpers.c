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

#include "../../include/minishell.h"

char	*ft_getenv(const char *name, char **envp)
{
	int	i;

	i = 0;
	while (envp[i] && (ft_strncmp(envp[i], name, ft_strlen(name))
			|| (envp[i][ft_strlen(name)] != '=' && envp[i][ft_strlen(name)])))
		i++;
	if (!envp[i] || !ft_strchr(envp[i], '='))
		return (NULL);
	return (envp[i] + ft_strlen(name) + 1);
}

static char	*build_env_pair(const char *name, const char *value)
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

static char	*dup_for_putenv(const char *name, const char *value)
{
	char	*dst;
	size_t	n;

	if (!value)
		return (ft_strdup(name));
	n = ft_strlen(name) + ft_strlen(value) + 2;
	dst = malloc(n);
	if (!dst)
		return (NULL);
	ft_strlcpy(dst, name, n);
	ft_strlcat(dst, "=", n);
	ft_strlcat(dst, value, n);
	return (dst);
}

char	**ft_setenv(const char *name, const char *value, char **envp)
{
	int		i;
	char	*str;
	char	*putenv_str;

	str = build_env_pair(name, value);
	if (!str)
		exit(EXIT_FAILURE);
	i = find_env_index_local(name, envp);
	if (envp[i])
	{
		free(envp[i]);
		envp[i] = str;
		putenv_str = str;
	}
	else
	{
		envp = strarradd(envp, str);
		putenv_str = dup_for_putenv(name, value);
		free(str);
	}
	if (value)
		putenv(putenv_str);
	else
		unsetenv(name);
	return (envp);
}
