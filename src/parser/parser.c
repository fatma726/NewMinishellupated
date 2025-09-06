/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatmtahmdabrahym <fatmtahmdabrahym@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by lcouturi          #+#    #+#             */
/*   Updated: 2025/09/06 20:53:40 by fatmtahmdab      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#ifdef BUILD_BONUS
# include "../../bonus/include/bonus.h"
#endif

static bool	check_wildcard_redirections(char **args)
{
    (void)args;
#ifdef BUILD_BONUS
	int		i;
	int		count;

	i = -1;
	while (args && args[++i])
	{
		/* skip here-doc tokens (<<, <<<) */
		if (isdlr(args[i]) || istlr(args[i]))
		{
			/* do not treat heredoc delimiter as an expandable file */
			i += (args[i + 1] != NULL);
			continue ;
		}
		if (islr(args[i]) || islrr(args[i]) || isrr(args[i]) || isdrr(args[i]))
		{
			if (args[i + 1] && ft_strchr(args[i + 1], '*'))
			{
				count = count_matching_files(args[i + 1]);
				if (count > 1)
				{
					ft_putstr_fd("bash: ", STDERR_FILENO);
					ft_putstr_fd(args[i + 1], STDERR_FILENO);
					ft_putendl_fd(": ambiguous redirect", STDERR_FILENO);
					return (false);
				}
			}
			/* skip operand */
			i += (args[i + 1] != NULL);
		}
	}
#endif
	return (true);
}

static char	**process_parser_input(char *str, char **envp, t_node *node)
{
	char	**args;
	char	charset[4];

	str = expand_envvar(str, envp, node);
	str = add_spaces_around_ampersand(str, node);
	ft_strlcpy(charset, " \t", 4);
	args = escape_split(str, charset, node);
	if (!check_wildcard_redirections(args))
	{
		free(str);
		strarrfree(args);
		set_exit_status(1);
		return (NULL);
	}
	args = expand_wildcard_if_bonus(args, envp, node);
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
		strarrfree(node->ori_args);
		return (envp);
	}
	return (NULL);
}

static char	**process_quotes_and_exec(char **args, char **envp, t_node *node)
{
	args = rm_quotes(args, node);
	if (!args)
	{
		rl_clear_history();
		strarrfree(envp);
		exit(EXIT_FAILURE);
	}
	envp = execute(args, envp, node);
	strarrfree(args);
	strarrfree(node->ori_args);
	return (envp);
}

char	**parser(char *str, char **envp, t_node *node)
{
	char	**args;

	args = process_parser_input(str, envp, node);
	if (handle_parser_errors(args, envp, node))
		return (envp);
	return (process_quotes_and_exec(args, envp, node));
}
