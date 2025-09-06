/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt6.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatmtahmdabrahym <fatmtahmdabrahym@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by lcouturi          #+#    #+#             */
/*   Updated: 2025/09/06 18:47:00 by fatmtahmdab      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_prompt(char *fmt, char **envp, t_node *node)
{
	int		l;
	char	*new_fmt;
	char	*pwd;

	pwd = get_pwd_for_prompt(envp, node);
	l = promptlen(fmt, envp, pwd, -1);
	if (!l)
	{
		free(fmt);
		return (NULL);
	}
	new_fmt = expand_loop(fmt - 1, malloc((size_t)(l + 1)),
			ft_getenv("USER", envp), pwd);
	new_fmt[l] = '\0';
	free(fmt);
	return (new_fmt);
}
