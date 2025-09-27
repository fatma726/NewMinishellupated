/*
**
*/
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatima <fatima@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by kyung-ki          #+#    #+#             */
/*   Updated: 2025/09/22 20:17:35 by fatima           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_signals(void)
{
	if (get_signal_number() == SIGINT)
	{
		set_exit_status(130);
		clear_signal_number();
	}
	else if (get_signal_number() == SIGPIPE)
	{
		if (isatty(STDIN_FILENO))
			ft_putstr_fd(" Broken pipe\n", STDERR_FILENO);
		set_exit_status(141);
		clear_signal_number();
	}
}

static char	*get_and_process_prompt(char **envp, t_node *n)
{
	const char	*prompt;
	char		*prompt_copy;

	prompt = ft_getenv("PS1", envp);
	if (!prompt)
		prompt = "\\s-\\v\\$ ";
	prompt_copy = ft_strdup(prompt);
	return (expand_prompt(prompt_copy, envp, n));
}

static char	**main_loop(char **envp, t_node *n)
{
	char	*line;
	char	*prompt;

	handle_signals();
	prompt = get_and_process_prompt(envp, n);
	line = get_line(prompt);
	if (prompt)
		free(prompt);
	n->line_nbr++;
	if (!line)
		handle_eof_exit(envp, n);
	envp = process_command(line, envp, n);
	rl_clear_visible_line();
	rl_reset_line_state();
	return (envp);
}

int	main(int argc, char **argv, char **envp)
{
	t_node		node;

	(void)argc;
	init_node(&node);
	set_exit_status(0);
	envp = strarrdup(envp);
	envp = shlvl_plus_plus(setpwd(&node, envp));
	envp = ensure_oldpwd_export(envp);
	envp = ft_setenv_envp("_", argv[0], envp);
	node.path_fallback = NULL;
	node.line_nbr = 0;
	set_signal();
	while (1)
		envp = main_loop(envp, &node);
}
