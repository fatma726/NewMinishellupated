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

static bool	env_has_key_any(char **envp, const char *name)
{
	int			i;
	size_t		len;

	len = ft_strlen(name);
	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], name, len)
			&& (envp[i][len] == '=' || envp[i][len] == '\0'))
			return (true);
		i++;
	}
	return (false);
}

char	**ensure_oldpwd_export(char **envp)
{
	if (!env_has_key_any(envp, "OLDPWD"))
		envp = ft_setenv_envp("OLDPWD", NULL, envp);
	return (envp);
}
