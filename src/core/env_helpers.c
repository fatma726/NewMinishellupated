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

char	**ft_setenv(const char *name, const char *value, char **envp)
{
	int		i;
	size_t	n;
	char	*str;
	char	*putenv_str;

	if (!value)
		str = ft_strdup(name);
	else
	{
		n = ft_strlen(name) + ft_strlen(value) + 2;
		str = malloc(n);
		ft_strlcpy(str, name, n);
		ft_strlcat(str, "=", n);
		ft_strlcat(str, value, n);
	}
	i = 0;
	if (!str)
		exit(EXIT_FAILURE);
	while (envp[i] && (ft_strncmp(envp[i], name, ft_strlen(name))
			|| (envp[i][ft_strlen(name)] != '=' && envp[i][ft_strlen(name)])))
		i++;
	if (envp[i])
	{
		free(envp[i]);
		envp[i] = str;
		putenv_str = str;
	}
	else
	{
		envp = strarradd(envp, str);
		// For putenv, we need a separate string that won't be freed
		if (value)
		{
			putenv_str = malloc(ft_strlen(name) + ft_strlen(value) + 2);
			ft_strlcpy(putenv_str, name, ft_strlen(name) + 1);
			ft_strlcat(putenv_str, "=", ft_strlen(name) + 2);
			ft_strlcat(putenv_str, value, ft_strlen(name) + ft_strlen(value) + 2);
		}
		else
			putenv_str = ft_strdup(name);
		free(str);
	}
	// Also update the actual environment variables
	if (value)
		putenv(putenv_str);
	else
		unsetenv(name);
	return (envp);
}
