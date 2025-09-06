/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is3.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatmtahmdabrahym <fatmtahmdabrahym@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by fatmtahmdabrahym #+#    #+#             */
/*   Updated: 2025/01/29 19:31:40 by fatmtahmdabrahym ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
