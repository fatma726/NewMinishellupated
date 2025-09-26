/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_spaces_redirections_helpers.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatmtahmdabrahym <fatmtahmdabrahym@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by kyung-ki          #+#    #+#             */
/*   Updated: 2025/09/24 11:16:31 by fatmtahmdab      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	need_space_before(char *s, int i)
{
	return (i > 0 && s[i - 1] != ' ' && s[i - 1] != '\t');
}

static int	need_space_after(char *s, int i)
{
	return (s[i + 1] && s[i + 1] != '&' && s[i + 1] != ' ' && s[i + 1] != '\t');
}

int	copy_double_left(char *str, char *result, int i, int *j)
{
	if (need_space_before(str, i))
		result[(*j)++] = ' ';
	result[(*j)++] = '<';
	result[(*j)++] = '<';
	if (need_space_after(str, i + 1))
		result[(*j)++] = ' ';
	return (i + 2);
}

int	copy_double_right(char *str, char *result, int i, int *j)
{
	if (need_space_before(str, i))
		result[(*j)++] = ' ';
	result[(*j)++] = '>';
	result[(*j)++] = '>';
	if (need_space_after(str, i + 1))
		result[(*j)++] = ' ';
	return (i + 2);
}

int	copy_single_redir(char *str, char *result, int i, int *j)
{
	if (need_space_before(str, i))
		result[(*j)++] = ' ';
	result[(*j)++] = str[i];
	if (need_space_after(str, i))
		result[(*j)++] = ' ';
	return (i + 1);
}
