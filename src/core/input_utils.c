/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatmtahmdabrahym <fatmtahmdabrahym@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by fatmtahmdab      #+#    #+#             */
/*   Updated: 2025/08/26 19:50:00 by fatmtahmdab      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* join into result with a newline between chunks */

static void	set_continuation_prompt(char **current_prompt, char *original)
{
	if (*current_prompt != original)
		free(*current_prompt);
	*current_prompt = ft_strdup("> ");
}

static int	append_line(char **result, char *line)
{
	char	*tmp;

	if (*result)
	{
		tmp = ft_strjoin(*result, "\n");
		free(*result);
		*result = ft_strjoin(tmp, line);
		free(tmp);
	}
	else
		*result = ft_strdup(line);
	free(line);
	return (*result != NULL);
}

static int	process_read_line(char **result, char **cur_prompt, char *orig)
{
	char	*line;

	line = readline(*cur_prompt);
	if (!line)
	{
		if (*result)
			free(*result);
		return (-1);
	}
	if (!append_line(result, line))
		return (-1);
	if (quote_check(*result, (int)ft_strlen(*result), NULL) == 0)
		return (0);
	set_continuation_prompt(cur_prompt, orig);
	return (1);
}

static char	*get_continuation_line(char *prompt)
{
	char	*result;
	char	*current_prompt;
	int		st;

	result = NULL;
	current_prompt = prompt;
	while (1)
	{
		st = process_read_line(&result, &current_prompt, prompt);
		if (st < 0)
		{
			if (current_prompt != prompt)
				free(current_prompt);
			return (NULL);
		}
		if (st == 0)
		{
			if (current_prompt != prompt)
				free(current_prompt);
			return (result);
		}
	}
	if (current_prompt != prompt)
		free(current_prompt);
	return (result);
}

char	*get_line(char *str)
{
	char	*line;
	char	*line2;
	char	*prompt;

	if (isatty(STDIN_FILENO))
	{
		prompt = ft_strdup(str);
		line = get_continuation_line(prompt);
		free(prompt);
	}
	else if (MSTEST_MODE)
		line = readline(NULL);
	else
	{
		line2 = read_line_simple();
		if (!line2)
			return (NULL);
		line = ft_strtrim(line2, "\n");
		free(line2);
	}
	return (line);
}
