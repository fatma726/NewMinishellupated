/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_operators.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatima <fatima@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by lcouturi          #+#    #+#             */
/*   Updated: 2025/09/03 12:28:25 by fatima           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	process_pipe_loop(char *s, size_t *i, t_node *n)
{
	while (s[*i] && (s[*i] != '&' || s[*i + 1] != '&'
			|| quote_check(s, (int)*i, n)))
		(*i)++;
}

static void	process_ampersand_loop(char *s, size_t *i, t_node *n)
{
	while (s[*i] && (s[*i] != '|' || s[*i + 1] != '|'
			|| quote_check(s, (int)*i, n)))
		(*i)++;
}

char	**split_operators(char *s, char **envp, t_node *n)
{
	char	*new_str;
	size_t	i;

	if (n->syntax_flag)
		return (envp);
	i = 0;
	while (s[i] && (((s[i] != '&' || s[i + 1] != '&') && (s[i] != '|'
					|| s[i + 1] != '|')) || quote_check(s, (int)i, n)))
	{
		if (!quote_check(s, (int)i, n) && s[i] == '&' && s[i + 1] != '&')
			break ;
		i++;
	}
	/* Defer executing the left segment until after leading-operator checks */
	// Check for standalone operators (no command before them)
	if (i == 0 && ((s[i] == '|' && s[i + 1] == '|') || (s[i] == '&' && s[i + 1] == '&')))
	{
		n->syntax_flag = true;
		set_exit_status(2);
		ft_putstr_fd("minishell: syntax error near unexpected token `", STDERR_FILENO);
		ft_putchar_fd(s[i], STDERR_FILENO);
		ft_putchar_fd(s[i + 1], STDERR_FILENO);
		ft_putendl_fd("'", STDERR_FILENO);
		free(s);
		return (envp);
	}
	// Check for standalone single & operator
	if (i == 0 && s[i] == '&' && s[i + 1] != '&')
	{
		n->syntax_flag = true;
		set_exit_status(2);
		ft_putstr_fd("minishell: syntax error near unexpected token `", STDERR_FILENO);
		ft_putchar_fd(s[i], STDERR_FILENO);
		ft_putendl_fd("'", STDERR_FILENO);
		free(s);
		return (envp);
	}
	// Check for invalid operator sequences like ||| or &&&
	if (s[i] && s[i + 1] && s[i + 2])
	{
		if ((s[i] == '|' && s[i + 1] == '|' && s[i + 2] == '|') ||
			(s[i] == '&' && s[i + 1] == '&' && s[i + 2] == '&'))
		{
			// Set syntax error flag and return
			n->syntax_flag = true;
			set_exit_status(2);
			ft_putstr_fd("minishell: syntax error near unexpected token `", STDERR_FILENO);
			ft_putchar_fd(s[i], STDERR_FILENO);
			ft_putendl_fd("'", STDERR_FILENO);
			free(s);
			return (envp);
		}
	}
	/* Execute the left segment first */
	new_str = ft_substr(s, 0, i);
	envp = parser(new_str, envp, n);
	if (!s[i])
		return (envp);
	/* Based on the result, skip chains of the opposite operator */
	while (!get_exit_status() && s[i] && s[i] == '|' && s[i + 1] == '|')
		process_pipe_loop(s, &i, n);
	while (get_exit_status() && s[i] && s[i] == '&' && s[i + 1] == '&')
		process_ampersand_loop(s, &i, n);
	{
		int		 skip;
		size_t	start;
		size_t	len;

		skip = (s[i] == '&' && s[i + 1] != '&') ? 1 : 2;
		start = i + (size_t)skip;
		len = ft_strlen(s) - start;
		new_str = ft_substr(s, (unsigned int)start, len);
	}
	free(s);
	envp = split_operators(new_str, envp, n);
	return (envp);
}
