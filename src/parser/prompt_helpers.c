/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatmtahmdabrahym <fatmtahmdabrahym@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by fatima            #+#    #+#             */
/*   Updated: 2025/10/06 14:57:45 by fatmtahmdab      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_escape_char(t_prompt_data *data)
{
	if (*(++(*data->fmt)) == '$')
	{
		if (!data->user || ft_strncmp(data->user, "root", 5) != 0)
			data->new_fmt[data->j++] = '$';
		else
			data->new_fmt[data->j++] = '#';
	}
	else if (**data->fmt == 'W')
		data->j += (int)ft_strlcpy(data->new_fmt + data->j, data->pwd,
				ft_strlen(data->pwd) + 1);
	else if (**data->fmt == 's')
		data->j += (int)ft_strlcpy(data->new_fmt + data->j, "minishell", 11);
	else if (**data->fmt == 'u')
		data->j += (int)ft_strlcpy(data->new_fmt + data->j, data->user,
				ft_strlen(data->user) + 1);
	else if (**data->fmt == 'v')
		data->j += (int)ft_strlcpy(data->new_fmt + data->j, "1.0", 4);
	else if (**data->fmt != 'h')
		(*data->fmt)--;
	return (data->j);
}

void	handle_pwd_path(char **pwd, char **envp)
{
	char		*home;

	home = ft_getenv("HOME", envp);
	if (!home)
		return ;
	if (!ft_strncmp(*pwd, home, ft_strlen(home)))
		*pwd = ft_strjoin("~", *pwd + ft_strlen(home));
}

char	*expand_loop(char *fmt, char *new_fmt, char *user, char *pwd)
{
	t_prompt_data	data;

	data.fmt = &fmt;
	data.new_fmt = new_fmt;
	data.j = 0;
	data.user = user;
	data.pwd = pwd;
	while (*(++fmt))
	{
		if (*fmt == '\\')
			data.j = handle_escape_char(&data);
		else
			new_fmt[data.j++] = *fmt;
	}
	return (new_fmt);
}

int	promptlen(char *fmt, char **envp, char *pwd, int i)
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
				l += (int)ft_strlen(pwd);
			else if (fmt[i] == 's')
				l += 9;
			else if (fmt[i] == 'u')
				l += (int)ft_strlen(ft_getenv("USER", envp));
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

char	*get_pwd_for_prompt(char **envp, t_node *node)
{
	char	*pwd;

	if (ft_getenv("PWD", envp))
		pwd = ft_getenv("PWD", envp);
	else
		pwd = node->pwd;
	handle_pwd_path(&pwd, envp);
	return (pwd);
}
