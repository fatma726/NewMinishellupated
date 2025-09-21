/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatmtahmdabrahym <fatmtahmdabrahym@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by fatima            #+#    #+#             */
/*   Updated: 2025/09/20 13:30:00 by fatmtahmdab      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <signal.h>

static sig_atomic_t	*signal_slot(void)
{
	static sig_atomic_t	value = 0;

	return (&value);
}

int	get_signal_number(void)
{
	return (*signal_slot());
}

void	clear_signal_number(void)
{
	*signal_slot() = 0;
}

void	set_signal_number(int sig)
{
	*signal_slot() = sig;
}
