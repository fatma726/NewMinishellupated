/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is4.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatmtahmdabrahym <fatmtahmdabrahym@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by fatmtahmdab       #+#    #+#             */
/*   Updated: 2025/09/06 17:11:43 by fatmtahmdab      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	isdp(char *str)
{
	return (str && !ft_strncmp(str, "||", 3));
}

bool	isda(char *str)
{
	return (str && !ft_strncmp(str, "&&", 3));
}
