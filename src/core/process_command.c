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
	int		 i;

	i = 0;
	while (s && s[i])
	{
		if (s[i] != ' ' && s[i] != '\t')
			return (false);
		i++;
	}
	return (true);
}

static bool	has_conditional_or_semicolon(const char *s, t_node *n)
{
	int		 i;

	i = -1;
	while (s && s[++i])
		if (!quote_check(s, i, n)
			&& (s[i] == ';'
				|| (s[i] == '&' && s[i + 1] == '&')
				|| (s[i] == '|' && s[i + 1] == '|')
				|| (s[i] == '&' && s[i + 1] != '&')))
			return (true);
	return (false);
}

static int	find_unquoted_oror(const char *s, t_node *n)
{
    int i;

    i = -1;
    while (s && s[++i])
        if (!quote_check(s, i, n) && s[i] == '|' && s[i + 1] == '|')
            return (i);
    return (-1);
}

static char	**dispatch_line(char *hashed, char **envp, t_node *n)
{
    int	idx;
    char	*left;
    char	*right;
    size_t start;
    size_t len;

    idx = find_unquoted_oror(hashed, n);
    if (idx >= 0)
    {
        left = ft_substr(hashed, 0, (size_t)idx);
        start = (size_t)(idx + 2);
        len = ft_strlen(hashed) - start;
        right = ft_substr(hashed, (unsigned int)start, len);
        envp = parser(left, envp, n);
        if (get_exit_status())
            envp = parser(right, envp, n);
        free(hashed);
        return (envp);
    }
    if (has_conditional_or_semicolon(hashed, n))
        return (subshell(hashed, envp, n));
    return (parser(hashed, envp, n));
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
