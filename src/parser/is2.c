/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is2.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatmtahmdabrahym <fatmtahmdabrahym@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by lcouturi          #+#    #+#             */
/*   Updated: 2025/08/29 21:33:36 by fatmtahmdab      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

bool	isrr(char *str)
{
	return (str && (!ft_strncmp(str, ">", 2) || !ft_strncmp(str, "2>", 3)
			|| !ft_strncmp(str, ">|", 3) || !ft_strncmp(str, "2>|", 4)));
}

bool	istlr(char *str)
{
	return (str && !ft_strncmp(str, "<<<", 4));
}

bool	isdlr(char *str)
{
	return (str && !ft_strncmp(str, "<<", 3));
}

bool	isdrr(char *str)
{
	return (str && !ft_strncmp(str, ">>", 3));
}

bool	islrr(char *str)
{
	return (str && !ft_strncmp(str, "<>", 3));
}

bool	isdp(char *str)
{
	return (str && !ft_strncmp(str, "||", 3));
}

bool	isda(char *str)
{
	return (str && !ft_strncmp(str, "&&", 3));
}
