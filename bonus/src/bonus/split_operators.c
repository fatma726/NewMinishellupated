/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_operators.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatmtahmdabrahym <fatmtahmdabrahym@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by lcouturi          #+#    #+#             */
/*   Updated: 2025/09/03 18:50:37 by fatmtahmdab      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	advance_to(char *s, size_t *i, t_node *n, char op)
{
	if (op == '|')
		while (s[*i]
			&& (s[*i] != '&' || s[*i + 1] != '&')
			&& !quote_check(s, (int)*i, n))
			(*i)++;
	else
		while (s[*i]
			&& (s[*i] != '|' || s[*i + 1] != '|')
			&& !quote_check(s, (int)*i, n))
			(*i)++;
}

static bool	syntax_err_pair(char *s, size_t i, t_node *n, int pair)
{
	n->syntax_flag = true;
	set_exit_status(2);
	ft_putstr_fd("minishell: syntax error near unexpected token `",
		STDERR_FILENO);
	ft_putchar_fd(s[i], STDERR_FILENO);
	if (pair)
		ft_putchar_fd(s[i + 1], STDERR_FILENO);
	ft_putendl_fd("'", STDERR_FILENO);
	free(s);
	return (true);
}

static size_t	find_split_index(char *s, t_node *n)
{
	size_t	i;

	i = 0;
	while (s[i]
		&& (((s[i] != '&' || s[i + 1] != '&')
			&& (s[i] != '|' || s[i + 1] != '|'))
			|| quote_check(s, (int)i, n)))
	{
		if (!quote_check(s, (int)i, n) && s[i] == '&' && s[i + 1] != '&')
			break ;
		i++;
	}
	return (i);
}

static char	**split_operators_tail(char *s, size_t i, char **envp, t_node *n)
{
	char	*new_str;
	int		skip;

	if (!s[i])
		return (envp);
	while (!get_exit_status() && s[i] && s[i] == '|' && s[i + 1] == '|')
		advance_to(s, &i, n, '|');
	while (get_exit_status() && s[i] && s[i] == '&' && s[i + 1] == '&')
		advance_to(s, &i, n, '&');
	if (s[i] == '&' && s[i + 1] != '&')
		skip = 1;
	else
		skip = 2;
	new_str = ft_substr(s, (unsigned int)(i + (size_t)skip),
			ft_strlen(s) - (i + (size_t)skip));
	free(s);
	return (split_operators(new_str, envp, n));
}

char	**split_operators(char *s, char **envp, t_node *n)
{
	char	*new_str;
	size_t	i;

	if (n->syntax_flag)
		return (envp);
	i = find_split_index(s, n);
	if (i == 0
		&& ((s[i] == '|' && s[i + 1] == '|')
			|| (s[i] == '&' && s[i + 1] == '&')))
		return (syntax_err_pair(s, i, n, 1), envp);
	if ((i == 0 && s[i] == '&' && s[i + 1] != '&')
		|| (s[i] && s[i + 1] && s[i + 2]
			&& ((s[i] == '|' && s[i + 1] == '|' && s[i + 2] == '|')
				|| (s[i] == '&' && s[i + 1] == '&' && s[i + 2] == '&'))))
		return (syntax_err_pair(s, i, n, 0), envp);
	// Check for invalid redirection followed by & or &&
	if (i == ft_strlen(s) && ft_strchr(s, '>'))
	{
		size_t j = 0;
		while (s[j])
		{
			if (s[j] == '>' && !quote_check(s, (int)j, n))
			{
				if (s[j + 1] == '&')
				{
					n->syntax_flag = true;
					set_exit_status(2);
					ft_putstr_fd("minishell: syntax error near unexpected token `", STDERR_FILENO);
					ft_putchar_fd('&', STDERR_FILENO);
					ft_putendl_fd("'", STDERR_FILENO);
					return (envp);
				}
				else if (s[j + 1] == '&' && s[j + 2] == '&')
				{
					n->syntax_flag = true;
					set_exit_status(2);
					ft_putstr_fd("minishell: syntax error near unexpected token `", STDERR_FILENO);
					ft_putstr_fd("&&", STDERR_FILENO);
					ft_putendl_fd("'", STDERR_FILENO);
					return (envp);
				}
			}
			j++;
		}
	}
	new_str = ft_substr(s, 0, i);
	envp = parser(new_str, envp, n);
	return (split_operators_tail(s, i, envp, n));
}
