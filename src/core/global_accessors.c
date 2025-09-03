/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global_accessors.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatmtahmdabrahym <fatmtahmdabrahym@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by fatmtahmdab       #+#    #+#             */
/*   Updated: 2025/08/30 04:08:22 by fatmtahmdab      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	get_signal_number(void)
{
	extern t_global_state	g_state;

	return (g_state.signal_number);
}

void	clear_signal_number(void)
{
	extern t_global_state	g_state;

	g_state.signal_number = 0;
}

int	get_exit_status(void)
{
	extern t_global_state	g_state;

	return (g_state.exit_status);
}

void	set_exit_status(int status)
{
	extern t_global_state	g_state;

	g_state.exit_status = status;
}
