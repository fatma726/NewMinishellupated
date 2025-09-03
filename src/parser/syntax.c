/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatmtahmdabrahym <fatmtahmdabrahym@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by lcouturi          #+#    #+#             */
/*   Updated: 2025/08/30 10:06:54 by fatmtahmdab      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	*handle_escape_continuation(char *str, char **str2, int esc)
{
	if (str2[0][0] && str2[0][0] != '#' && esc == 3)
		str[ft_strlen(str) - 1] = '\0';
	else if ((!str2[0][0] || str2[0][0] == '#') && esc == 3)
		return (free(str2[0]), str);
	else
	{
		str2[1] = ft_strjoin(str, "\n");
		free(str);
		str = str2[1];
	}
	return (str);
}

char	*escape_handler(char *str, t_node *node)
{
	char	*str2[2];
	char	prompt[3];
	int		esc;

	while (1)
	{
		esc = quote_check(str, (int)ft_strlen(str), node);
		if (!esc)
			return (str);
		ft_strlcpy(prompt, "> ", 3);
		str2[0] = get_line(prompt);
		if (!str2[0])
			return (str);
		str = handle_escape_continuation(str, str2, esc);
		str2[1] = ft_strjoin(str, str2[0]);
		free(str2[0]);
		free(str);
		str = str2[1];
	}
}

static bool	syntax_check_loop(int i, char **a, char **envp, t_node *node)
{
	(void)envp;
	(void)node;
	if (a[i] && a[i + 1] && ft_strchr(a[i], '\\') && !a[i + 1][0])
		return (false);
	return (true);
}

static bool	check_consecutive_operators_syntax(char **a)
{
	int	i;
	int	c_op;
	int	n_op;
	int	c_q;
	int	n_q;

	i = 0;
	while (a[i] && a[i + 1])
	{
		c_op = (isp(a[i]) || islr(a[i]) || isrr(a[i])
				|| isdlr(a[i]) || isdrr(a[i]) || isdp(a[i]) || isda(a[i]) || is_ampersand(a[i]));
		n_op = (isp(a[i + 1]) || islr(a[i + 1]) || isrr(a[i + 1])
				|| isdlr(a[i + 1]) || isdrr(a[i + 1]) || isdp(a[i + 1]) || isda(a[i + 1]) || is_ampersand(a[i + 1]));
		c_q = (ft_strchr(a[i], '\'') || ft_strchr(a[i], '\"'));
		n_q = (ft_strchr(a[i + 1], '\'') || ft_strchr(a[i + 1], '\"'));
		if (c_op && n_op && !c_q && !n_q)
		{
			if (check_pipe_redir_combination(a, i))
				i++;
			else
				return (false);
		}
		i++;
	}
	return (true);
}

bool	syntax_check(char **a, char **envp, t_node *node)
{
	int	i;

	if (!check_leading_operators_syntax(a))
		return (false);
	if (!check_consecutive_operators_syntax(a))
		return (false);
	if (!check_trailing_operators_syntax(a))
		return (false);
	i = -1;
	while (a[++i])
		if (!syntax_check_loop(i, a, envp, node))
			return (false);
	if (!redir_syntax_check(a))
		return (false);
	return (true);
}
