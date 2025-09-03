/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatmtahmdabrahym <fatmtahmdabrahym@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by fatmtahmdab      #+#    #+#             */
/*   Updated: 2025/08/26 19:50:00 by fatmtahmdab      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*get_line(char *str)
{
	char	*line;
	char	*line2;

	if (!MSTEST_MODE || isatty(STDIN_FILENO))
		line = readline(str);
	else
	{
		line2 = read_line_simple();
		if (!line2)
			return (NULL);
		line = ft_strtrim(line2, "\n");
		free(line2);
	}
	return (line);
}

static void	handle_quote_error(int quote_type)
{
	char	eof_msg[35];

	ft_strlcpy(eof_msg, "minishell: unexpected EOF wh", 35);
	ft_putstr_fd(eof_msg, STDERR_FILENO);
	if (quote_type == 1)
		ft_putendl_fd("ile looking for matching `''", STDERR_FILENO);
	else
		ft_putendl_fd("ile looking for matching `\"'", STDERR_FILENO);
	set_exit_status(2);
}

static void	process_quotes(char *arg, t_node *node)
{
	if (quote_check(arg, (int)ft_strlen(arg), node) == 1
		|| quote_check(arg, (int)ft_strlen(arg), node) == 2)
		handle_quote_error(quote_check(arg, (int)ft_strlen(arg), node));
}

void	argmode(char *line, char *arg, char **envp, t_node *node)
{
	node->escape_skip = !ft_strchr(arg, '\'') && !ft_strchr(arg, '\"')
		&& !ft_strchr(arg, '\\');
	process_quotes(arg, node);
	init_node(node);
	node->argmode = true;
	if (ft_strncmp(line, "\0", 1))
		envp = subshell(hash_handler(line, node), envp, node);
	else
		free(line);
	strarrfree(envp);
	exit(get_exit_status());
}
