/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatmtahmdabrahym <fatmtahmdabrahym@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by lcouturi          #+#    #+#             */
/*   Updated: 2025/08/28 17:01:48 by fatmtahmdab      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	*expand_loop(char *fmt, char *new_fmt, char *user, char *pwd)
{
	int	j;

	j = 0;
	while (*(++fmt))
	{
		if (*fmt == '\\')
		{
			if (*(++fmt) == '$')
				new_fmt[j++] = '#' + (ft_strncmp(user, "root", 5) || !user);
			else if (*fmt == 'W')
				j += ft_strlcpy(new_fmt + j, pwd, ft_strlen(pwd) + 1);
			else if (*fmt == 's')
				j += ft_strlcpy(new_fmt + j, "minishell", 11);
			else if (*fmt == 'u')
				j += ft_strlcpy(new_fmt + j, user, ft_strlen(user) + 1);
			else if (*fmt == 'v')
				j += ft_strlcpy(new_fmt + j, "1.0", 4);
			else if (*fmt != 'h')
				fmt--;
		}
		else
			new_fmt[j++] = *fmt;
	}
	return (new_fmt);
}

static int	promptlen(char *fmt, char **envp, char *pwd, int i)
{
	int	l;

	l = 0;
	while (fmt[++i])
	{
		if (fmt[i] == '\\')
		{
			if (fmt[++i] == '$')
				l++;
			else if (fmt[i] == 'W')
				l += ft_strlen(pwd);
			else if (fmt[i] == 's')
				l += 9;
			else if (fmt[i] == 'u')
				l += ft_strlen(ft_getenv("USER", envp));
			else if (fmt[i] == 'v')
				l += 3;
			else if (fmt[i] != 'h')
				i--;
		}
		else
			l++;
	}
	return (l);
}

static void	handle_pwd_path(char **pwd, char **envp)
{
	char	root[2];
	char	home[2];

	if (!ft_strncmp(*pwd, "/", 2))
	{
		ft_strlcpy(root, "/", 2);
		*pwd = root;
	}
	else if (!ft_strncmp(ft_getenv("HOME", envp), *pwd, ft_strlen(*pwd) + 1))
	{
		ft_strlcpy(home, "~", 2);
		*pwd = home;
	}
	else if (ft_strchr(*pwd, '/'))
		*pwd = ft_strrchr(*pwd, '/') + 1;
}

char	*expand_prompt(char *fmt, char **envp, t_node *node)
{
	int		l;
	char	*new_fmt;
	char	*pwd;

	if (ft_getenv("PWD", envp))
		pwd = ft_getenv("PWD", envp);
	else
		pwd = node->pwd;
	handle_pwd_path(&pwd, envp);
	l = promptlen(fmt, envp, pwd, -1);
	if (!l)
		return (NULL);
	new_fmt = expand_loop(fmt - 1, malloc((size_t)(l + 1)),
			ft_getenv("USER", envp), pwd);
	new_fmt[l] = '\0';
	return (new_fmt);
}
