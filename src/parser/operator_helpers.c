/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operator_helpers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatmtahmdabrahym <fatmtahmdabrahym@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by fatima            #+#    #+#             */
/*   Updated: 2025/09/20 13:30:00 by fatmtahmdab      ###   ########.fr       */
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

bool	isdp(char *str)
{
	return (str && !ft_strncmp(str, "||", 3));
}
