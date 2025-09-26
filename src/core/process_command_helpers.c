/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_command_helpers.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatmtahmdabrahym <fatmtahmdabrahym@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by fatmtahmdabrahym #+#    #+#             */
/*   Updated: 2025/01/29 19:31:40 by fatmtahmdabrahym ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_quote_state(char *line, int *quote_state, char *quote_char)
{
	int	i;

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

char	**run_oror(char *hashed, int idx, char **envp, t_node *n)
{
	char		*left;
	char		*right;
	size_t		off;

	left = ft_substr(hashed, 0, (size_t)idx);
	off = (size_t)(idx + 2);
	right = ft_substr(hashed, (unsigned int)off, ft_strlen(hashed) - off);
	if (is_blank(left) || is_blank(right))
	{
		set_exit_status(2);
		n->syntax_flag = true;
		ft_putstr_fd("minishell: syntax error near unexpected token `",
			STDERR_FILENO);
		ft_putendl_fd("||'", STDERR_FILENO);
		free(left);
		free(right);
		free(hashed);
		return (envp);
	}
	envp = parser(left, envp, n);
	if (get_exit_status())
		envp = parser(right, envp, n);
	free(hashed);
	return (envp);
}

char	**dispatch_line(char *hashed, char **envp, t_node *n)
{
	int			idx;
	int			i;

	i = 0;
	while (hashed[i] && (hashed[i] == ' ' || hashed[i] == '\t'))
		i++;
	if (hashed[i] == ';')
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `",
			STDERR_FILENO);
		ft_putendl_fd(";'", STDERR_FILENO);
		set_exit_status(2);
		n->syntax_flag = true;
		free(hashed);
		return (envp);
	}
	idx = find_unquoted_oror(hashed, n);
	if (idx >= 0)
		return (run_oror(hashed, idx, envp, n));
	return (subshell(hashed, envp, n));
}
