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

bool	is_blank(const char *s)
{
	int			i;

	i = 0;
	while (s && s[i])
	{
		if (s[i] != ' ' && s[i] != '\t' && s[i] != '\r'
			&& s[i] != '\v' && s[i] != '\f')
			return (false);
		i++;
	}
	return (true);
}

int	find_unquoted_oror(const char *s, t_node *n)
{
	int			i;

	i = -1;
	while (s && s[++i])
		if (!quote_check(s, i, n) && s[i] == '|' && s[i + 1] == '|')
			return (i);
	return (-1);
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

char	**check_braces(char *line, char **envp, t_node *n)
{
	int	i;

	i = 0;
	while (line[i] && ft_strchr(" \t", line[i]))
		i++;
	if (line[i] == '{')
	{
		ft_putendl_fd("minishell: unexpected end of file", STDERR_FILENO);
		set_exit_status(2);
		n->syntax_flag = true;
		return (free(line), envp);
	}
	if (line[i] == '}')
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `",
			STDERR_FILENO);
		ft_putendl_fd("}'", STDERR_FILENO);
		set_exit_status(2);
		n->syntax_flag = true;
		return (free(line), envp);
	}
	return (NULL);
}
