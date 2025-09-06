/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_helpers4.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatmtahmdabrahym <fatmtahmdabrahym@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by fatmtahmdabrahym #+#    #+#             */
/*   Updated: 2025/01/29 19:31:40 by fatmtahmdabrahym ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static const char	*check_counts(int pipe_count, int amp_count)
{
	if (pipe_count >= 3)
		return ("|");
	if (amp_count >= 3)
		return ("&");
	return (NULL);
}

static void	update_counts(char c, int *pipe_count, int *amp_count)
{
	if (c == '|')
	{
		(*pipe_count)++;
		*amp_count = 0;
	}
	else if (c == '&')
	{
		(*amp_count)++;
		*pipe_count = 0;
	}
	else
	{
		*pipe_count = 0;
		*amp_count = 0;
	}
}

const char	*check_invalid_operator_sequences(char **args, int i)
{
	int		pipe_count;
	int		amp_count;
	int		j;
	char	c;

	if (!args[i] || ft_strlen(args[i]) < 3)
		return (NULL);
	pipe_count = 0;
	amp_count = 0;
	j = 0;
	while (args[i][j])
	{
		c = args[i][j];
		update_counts(c, &pipe_count, &amp_count);
		if (check_counts(pipe_count, amp_count))
			return (check_counts(pipe_count, amp_count));
		j++;
	}
	return (NULL);
}
