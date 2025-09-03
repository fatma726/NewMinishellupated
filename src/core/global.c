/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatmtahmdabrahym <fatmtahmdabrahym@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by kyung-ki          #+#    #+#             */
/*   Updated: 2025/08/30 04:00:14 by fatmtahmdab      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <signal.h>
#include <termios.h>
#include <readline/readline.h>
#include <readline/history.h>

t_global_state	g_state = {0, 0};

static void	sigint_handler(int sig)
{
	(void)sig;
	g_state.signal_number = SIGINT;
	write(STDOUT_FILENO, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

static void	sigquit_handler(int sig)
{
	(void)sig;
	g_state.signal_number = SIGQUIT;
}

void	set_signal(void)
{
	set_termios();
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, sigquit_handler);
}
