/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatmtahmdabrahym <fatmtahmdabrahym@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 11:25:00 by fatima            #+#    #+#             */
/*   Updated: 2025/09/25 23:29:33 by fatmtahmdab      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_non_printable_start(char *line)
{
	int				i;
	unsigned char	c;

	i = 0;
	while (line[i] == ' ' || line[i] == '\t' || line[i] == '\r'
		|| line[i] == '\v' || line[i] == '\f')
		i++;
	c = (unsigned char)line[i];
	if (line[i] && (c == '\n' || c == 0))
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
		if (c == '\n')
			ft_putstr_fd("newline", 2);
		else
			write(2, &c, 1);
		ft_putendl_fd("'", 2);
		set_exit_status(258);
		free(line);
		return (1);
	}
	return (0);
}

static void	prepare_node_for_line(t_node *n, char *line)
{
	init_node(n);
	n->argmode = false;
	n->escape_skip = !ft_strchr(line, '\'') && !ft_strchr(line, '"')
		&& !ft_strchr(line, '\\');
}

/* moved to process_command_helpers.c */

int	find_unquoted_oror(const char *s, t_node *n)
{
	int			i;

	i = -1;
	while (s && s[++i])
		if (!quote_check(s, i, n) && s[i] == '|' && s[i + 1] == '|')
			return (i);
	return (-1);
}

char	**process_command(char *line, char **envp, t_node *n)
{
	char		*expanded;
	char		*hashed;
	char		**result;

	if (!line || is_blank(line))
		return (free(line), envp);
	if (handle_non_printable_start(line))
		return (envp);
	if (handle_unmatched_quotes(line, n))
		return (envp);
	prepare_node_for_line(n, line);
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
