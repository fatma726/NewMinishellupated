/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatima <fatima@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by fatima            #+#    #+#             */
/*   Updated: 1970/01/01 00:00:00 by fatima           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	status_store(int value, int set_flag)
{
	static int	stored_status = 0;

	if (set_flag)
		stored_status = value;
	return (stored_status);
}

int	get_exit_status(void)
{
	return (status_store(0, 0));
}

void	set_exit_status(int status)
{
	(void)status_store(status, 1);
}
