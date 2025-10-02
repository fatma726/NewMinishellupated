/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatmtahmdabrahym <fatmtahmdabrahym@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by fatima            #+#    #+#             */
/*   Updated: 2025/10/01 00:37:28 by fatmtahmdab      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_unquoted_oror(const char *s, t_node *n)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (!quote_check(s, i, n) && s[i] == '|' && s[i + 1] == '|')
			return (i);
		i++;
	}
	return (-1);
}

static char	**handle_oror_error(char *left, char *right, char *hashed,
		char **envp)
{
	set_exit_status(2);
	ft_putstr_fd("minishell: syntax error near unexpected token `",
		STDERR_FILENO);
	ft_putendl_fd("||'", STDERR_FILENO);
	free(left);
	free(right);
	free(hashed);
	return (envp);
}

char	**run_oror(char *hashed, int idx, char **envp, t_node *n)
{
	char	*left;
	char	*right;
	size_t	off;

	left = ft_substr(hashed, 0, (size_t)idx);
	off = (size_t)(idx + 2);
	right = ft_substr(hashed, (unsigned int)off, ft_strlen(hashed) - off);
	if (is_blank(left) || is_blank(right))
	{
		n->syntax_flag = true;
		return (handle_oror_error(left, right, hashed, envp));
	}
	envp = parser(left, envp, n);
	if (get_exit_status())
		envp = parser(right, envp, n);
	else
		free(right);
	free(hashed);
	return (envp);
}

char	**dispatch_line(char *hashed, char **envp, t_node *n)
{
	int	idx;
	int	i;

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

char	**process_command(char *line, char **envp, t_node *n)
{
	char		*expanded;
	char		*hashed;
	char		**result;

	if (!line || is_blank(line))
		return (free(line), envp);
	if (handle_unmatched_quotes(line, n))
		return (envp);
	if (has_semicolon(line, n))
		return (process_semicolon_commands(line, envp, n));
	result = check_standalone_operators(line, envp, n);
	if (result)
		return (result);
	result = check_braces(line, envp, n);
	if (result)
		return (result);
	expanded = escape_handler(line, n);
	hashed = hash_handler(expanded, n);
	envp = dispatch_line(hashed, envp, n);
	if (n->syntax_flag)
		set_exit_status(2);
	return (envp);
}
