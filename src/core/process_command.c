/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatima <fatima@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 11:25:00 by fatima            #+#    #+#             */
/*   Updated: 2025/09/03 11:25:00 by fatima           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static bool	is_blank(const char *s)
{
	int	i;

	i = 0;
	while (s && s[i])
	{
		if (s[i] != ' ' && s[i] != '\t')
			return (false);
		i++;
	}
	return (true);
}

static int	find_unquoted_oror(const char *s, t_node *n)
{
	int	i;

	i = -1;
	while (s && s[++i])
		if (!quote_check(s, i, n) && s[i] == '|' && s[i + 1] == '|')
			return (i);
	return (-1);
}

static char	**run_oror(char *hashed, int idx, char **envp, t_node *n)
{
	char	*left;
	char	*right;
	size_t	off;

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

static char	**dispatch_line(char *hashed, char **envp, t_node *n)
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
	char	*expanded;
	char	*hashed;

	init_node(n);
	n->argmode = false;
	if (!line || is_blank(line))
		return (free(line), envp);
	n->escape_skip = !ft_strchr(line, '\'') && !ft_strchr(line, '"')
		&& !ft_strchr(line, '\\');
	expanded = escape_handler(line, n);
	hashed = hash_handler(expanded, n);
	envp = dispatch_line(hashed, envp, n);
	if (n->syntax_flag)
		set_exit_status(2);
	return (envp);
}
