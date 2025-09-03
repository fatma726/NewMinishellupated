/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatmtahmdabrahym <fatmtahmdabrahym@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 22:22:36 by fatmtahmdab       #+#    #+#             */
/*   Updated: 2025/09/02 15:33:29 by fatmtahmdab      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	cmd_history(char **args, t_node *node)
{
	/* HIST_ENTRY	**hist_list; */
	/* int			i; */
	/* int			start_num; */

	(void)args;
	(void)node;
	/* hist_list = history_list(); */
	/* if (!hist_list) */
	/* { */
		write(1, "No history available\n", 20);
		return ;
	/* } */
	/* start_num = 1; */
	/* i = 0; */
	/* while (hist_list[i]) */
	/* { */
	/* 	ft_putnbr_fd(start_num + i, 1); */
	/* 	write(1, "  ", 2); */
	/* 	write(1, hist_list[i]->line, ft_strlen(hist_list[i]->line)); */
	/* 	write(1, "\n", 1); */
	/* 	i++; */
	/* } */
}
