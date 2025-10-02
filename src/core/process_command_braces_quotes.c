/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_command_braces_quotes.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatmtahmdabrahym <fatmtahmdabrahym@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by fatima            #+#    #+#             */
/*   Updated: 2025/09/30 23:00:00 by fatmtahmdab      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static char	**report_syntax_token(const char *tok, char **envp,
									t_node *n, char *line)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `",
		STDERR_FILENO);
	ft_putstr_fd(tok, STDERR_FILENO);
	ft_putendl_fd("'", STDERR_FILENO);
	set_exit_status(2);
	n->syntax_flag = true;
	free(line);
	return (envp);
}

char	**check_braces(char *line, char **envp, t_node *n)
{
	int		i;

	i = 0;
	while (line[i] && ft_strchr(" \t", line[i]))
		i++;
	if (line[i] == '{')
	{
		ft_putendl_fd("minishell: unexpected end of file", STDERR_FILENO);
		set_exit_status(2);
		n->syntax_flag = true;
		free(line);
		return (envp);
	}
	if (line[i] == '}')
		return (report_syntax_token("}", envp, n, line));
	return (NULL);
}

static int	check_quote_state(char *line, int *quote_state, char *quote_char)
{
	int		i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '"')
		{
			if (*quote_state == 0)
			{
				*quote_state = 1;
				*quote_char = line[i];
			}
			else if (line[i] == *quote_char)
				*quote_state = 0;
		}
		i++;
	}
	return (i);
}

static void	print_quote_error(char quote_char, t_node *n)
{
	ft_putstr_fd("minishell: unexpected EOF while looking for matching `",
		STDERR_FILENO);
	ft_putchar_fd(quote_char, STDERR_FILENO);
	ft_putendl_fd("'", STDERR_FILENO);
	set_exit_status(2);
	n->syntax_flag = true;
}

int	handle_unmatched_quotes(char *line, t_node *n)
{
	int		quote_state;
	char	quote_char;

	quote_state = 0;
	check_quote_state(line, &quote_state, &quote_char);
	if (quote_state != 0)
	{
		print_quote_error(quote_char, n);
		free(line);
		return (1);
	}
	return (0);
}
