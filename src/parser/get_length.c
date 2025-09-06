/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_length.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatmtahmdabrahym <fatmtahmdabrahym@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by lcouturi          #+#    #+#             */
/*   Updated: 2025/08/28 21:13:07 by fatmtahmdab      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	getsize(long n)
{
	int	s;

	s = 1;
	if (!n)
		s++;
	while (n && s++)
		n /= 10;
	return (s);
}

static int	handle_envvar(char *str, char **envp, int *i)
{
	int	j;

	j = -1;
	if (str[++i[0]] == '?')
	{
		i[5] += getsize(get_exit_status());
		return (1);
	}
	i[1] = i[0];
	while (ft_isalnum(str[i[1]]) || str[i[1]] == '_')
		i[1]++;
	i[2] = 0;
	while (envp[i[2]] && (ft_strncmp(envp[i[2]], str + i[0],
				(size_t)(i[1] - i[0])) || envp[i[2]][i[1] - i[0]] != '='))
		i[2]++;
	if (envp[i[2]])
	{
		while (envp[i[2]][++j])
			i[5] += (ft_strchr("<>|", envp[i[2]][j]) != 0);
		i[5] += (int)(ft_strlen(envp[i[2]]) - (size_t)(i[1] - i[0] + 1));
	}
	i[0] = i[1] - 1;
	return (0);
}

bool	in_heredoc(char *str, int i)
{
	while (i && !ft_strchr(" \t", str[i]))
		i--;
	while (i && ft_strchr(" \t", str[i]))
		i--;
	return (i && str[i] == '<' && str[i - 1] == '<');
}

void	get_length(char *str, char **envp, int *i, t_node *node)
{
	i[3] = quote_check(str, i[0], node);
	if (in_heredoc(str, i[0]))
		i[5]++;
	else if (i[3] < 2 && ((str[i[0]] == '$' && (ft_isalnum(str[i[0] + 1])
					|| str[i[0] + 1] == '_' || (i[3] != 1 && str[i[0]
							+ 1] == '\"') || (i[3] < 2 && str[i[0] + 1] == '\'')
				)) || !ft_strncmp(str + i[0], "$?", 2))
		&& handle_envvar(str, envp, i))
		return ;
	else if (!i[3] && (ft_strchr("<>|", str[i[0]]) || (str[i[0]] == '2'
				&& str[i[0] + 1] == '>')))
	{
		i[5] += 4;
		if (i[0] && str[i[0] - 1] == '2')
			i[0]++;
		else if (i[0] && str[i[0] - 1] == '>')
			i[0] += (str[i[0]] == '>' || str[i[0]] == '|');
		else if (i[0] && str[i[0] - 1] == '<' && (str[i[0]] == '<'
				|| str[i[0]] == '>'))
			i[0] += (str[i[0] + 1] == '<' && str[i[0]] != '>') + 1;
	}
	else
		i[5]++;
}
