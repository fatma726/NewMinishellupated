/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatmtahmdabrahym <fatmtahmdabrahym@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by lcouturi          #+#    #+#             */
/*   Updated: 2025/08/29 21:37:35 by fatmtahmdab      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
