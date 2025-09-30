/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatima <fatima@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by lcouturi          #+#    #+#             */
/*   Updated: 2025/09/22 22:22:01 by fatima           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#ifdef BUILD_BONUS
# include "../../bonus/include/bonus.h"
#endif

static char	**process_parser_input(char *str, char **envp, t_node *node)
{
	char	**args;
	char	charset[4];

	str = expand_envvar(str, envp, node);
	str = add_spaces_around_ampersand(str, node);
	str = add_spaces_around_redirections(str, node);
	ft_strlcpy(charset, " \t", 4);
	args = escape_split(str, charset, node);
	args = apply_wildcard_phase(args, envp, node, str);
	if (!args)
		return (NULL);
	free(str);
	node->ori_args = strarrdup(args);
	return (args);
}

static char	**handle_parser_errors(char **args, char **envp, t_node *node)
{
	if (!args)
		return (envp);
	if (args[0] && !syntax_check(node->ori_args, envp, node))
	{
		handle_syntax_error(envp, node);
		strarrfree(args);
		if (node->ori_args)
		{
			strarrfree(node->ori_args);
			node->ori_args = NULL;
		}
		return (envp);
	}
	return (NULL);
}

static char	**process_quotes_and_exec(char **args, char **envp, t_node *node)
{
	args = rm_quotes(args, node);
	if (!args)
	{
		clear_history();
		strarrfree(envp);
		exit(EXIT_FAILURE);
	}
	envp = execute(args, envp, node);
	strarrfree(args);
	if (node->ori_args)
		strarrfree(node->ori_args);
	return (envp);
}

char	**parser(char *str, char **envp, t_node *node)
{
    char	**args;

    if (!isatty(STDIN_FILENO) && get_nontext_input())
    {
        clear_nontext_input();
        set_exit_status(127);
        return (envp);
    }
    args = process_parser_input(str, envp, node);
    if (handle_parser_errors(args, envp, node))
    {
        return (envp);
    }
	return (process_quotes_and_exec(args, envp, node));
}
