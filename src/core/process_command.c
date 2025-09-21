/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatima <fatima@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 11:25:00 by fatima            #+#    #+#             */
/*   Updated: 2025/09/15 17:29:33 by fatima           ###   ########.fr       */
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
	if (line[i] && !(c >= 32 && c <= 126))
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

char	**process_command(char *line, char **envp, t_node *n)
{
	char		*expanded;
	char		*hashed;
	char		**result;

	if (!line || is_blank(line))
		return (free(line), envp);
	if (handle_non_printable_start(line))
		return (envp);
	init_node(n);
	n->argmode = false;
	n->escape_skip = !ft_strchr(line, '\'') && !ft_strchr(line, '"')
		&& !ft_strchr(line, '\\');
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
