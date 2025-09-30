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
#include <stdio.h>

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

    /* In non-interactive (piped) mode, continuation prompts are not needed. */
    if (!isatty(STDIN_FILENO))
        return (readline(NULL));

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
    char	*prompt;

    if (!isatty(STDIN_FILENO))
    {
        /* Fully bypass readline in non-tty mode to avoid control sequences */
        char    *buf;
        size_t  cap;
        ssize_t nread;

        buf = NULL;
        cap = 0;
        nread = getline(&buf, &cap, stdin);
        if (nread < 0)
        {
            if (buf)
                free(buf);
            return (NULL);
        }
        /* detect non-text (binary) bytes in the raw input line */
        {
            size_t i;
            int    nontext = 0;
            for (i = 0; i < (size_t)nread; i++)
            {
                unsigned char c = (unsigned char)buf[i];
                if (c == '\n')
                    continue;
                if ((c < 32 && c != '\t') || c >= 128)
                {
                    nontext = 1;
                    break;
                }
            }
            if (nontext)
                set_nontext_input(true);
        }
        if (nread > 0 && buf[nread - 1] == '\n')
            buf[nread - 1] = '\0';
        return (buf);
    }
    prompt = ft_strdup(str);
    line = get_continuation_line(prompt);
    free(prompt);
    return (line);
}
