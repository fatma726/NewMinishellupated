/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatmtahmdabrahym <fatmtahmdabrahym@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by kyung-ki          #+#    #+#             */
/*   Updated: 2025/09/03 19:00:33 by fatmtahmdab      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	handle_signals(void)
{
	if (get_signal_number() == SIGINT)
	{
		set_exit_status(130);
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
	set_termios();
	line = get_line(prompt);
	if (prompt)
		free(prompt);
	n->line_nbr++;
	if (!line)
	{
		restore_termios();
		exit(get_exit_status());
	}
	envp = process_command(line, envp, n);
	return (envp);
}

int	main(int argc, char **argv)
{
	extern char	**environ;
	char		**envp;
	t_node		node;

	set_exit_status(0);
	envp = shlvl_plus_plus(setpwd(&node, strarrdup(environ)));
	envp = ft_setenv("_", argv[0], envp);
	node.path_fallback = NULL;
	node.line_nbr = 0;
	node.aliases = malloc(sizeof(char **));
	node.aliases[0] = NULL;
	if (!ft_getenv("PATH", envp))
		node.path_fallback = ft_strdup("/usr/bin:/bin");
	set_signal();
	if (argc > 2 && !ft_strncmp(argv[1], "-c", 3))
	{
		argmode(NULL, argv[2], envp, &node);
		restore_termios();
		exit(get_exit_status());
	}
	envp = run_commands(envp, &node);
	while (1)
		envp = main_loop(envp, &node);
}
