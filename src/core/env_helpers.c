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

int	ft_setenv_var(const char *name, const char *value, int overwrite)
{
	(void)name;
	(void)value;
	(void)overwrite;
	return (0);
}
