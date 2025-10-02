/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_tokens_group.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatmtahmdabrahym <fatmtahmdabrahym@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by fatima            #+#    #+#             */
/*   Updated: 2025/09/30 23:00:00 by fatmtahmdab      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

bool	is_ampersand(char *str)
{
	return (str && !ft_strncmp(str, "&", 2));
}

bool	is_open_paren(char *str)
{
	return (str && !ft_strncmp(str, "(", 2));
}

bool	is_close_paren(char *str)
{
	return (str && !ft_strncmp(str, ")", 2));
}
