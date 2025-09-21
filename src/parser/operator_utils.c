/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operator_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatmtahmdabrahym <fatmtahmdabrahym@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by fatima            #+#    #+#             */
/*   Updated: 2025/09/20 16:56:15 by fatmtahmdab      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	islr(char *str)
{
	return (str && !ft_strncmp(str, "<", 2));
}

bool	isp(char *str)
{
	return (str && !ft_strncmp(str, "|", 2));
}

bool	istr(char *str)
{
	return (str && !ft_strncmp(str, ">>>", 3));
}

bool	is_ampersand(char *str)
{
	return (str && !ft_strncmp(str, "&", 2));
}

bool	isrr(char *str)
{
	return (str && ((!ft_strncmp(str, ">", 2) && ft_strlen(str) == 1)
			|| !ft_strncmp(str, "2>", 3) || !ft_strncmp(str, ">|", 3)
			|| !ft_strncmp(str, "2>|", 4)));
}
