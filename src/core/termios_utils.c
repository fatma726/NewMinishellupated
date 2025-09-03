/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termios_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatmtahmdabrahym <fatmtahmdabrahym@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by kyung-ki          #+#    #+#             */
/*   Updated: 2025/08/30 02:19:36 by fatmtahmdab      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <termios.h>

void	set_termios(void)
{
	struct termios	termios;
	struct termios	original;

	if (tcgetattr(STDIN_FILENO, &original) == 0)
	{
		termios = original;
		termios.c_lflag &= ~(tcflag_t)ECHOCTL;
		tcsetattr(STDIN_FILENO, TCSANOW, &termios);
	}
}

void	restore_termios(void)
{
	struct termios	original;

	if (tcgetattr(STDIN_FILENO, &original) == 0)
	{
		original.c_lflag |= (tcflag_t)ECHOCTL;
		tcsetattr(STDIN_FILENO, TCSANOW, &original);
	}
}
