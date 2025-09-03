/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semicolon_helpers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatmtahmdabrahym <fatmtahmdabrahym@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by fatmtahmdabrahym #+#    #+#             */
/*   Updated: 2025/01/29 19:31:40 by fatmtahmdabrahym ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

bool	error_message(const char *token, char **envp, t_node *node)
{
	char	*msg1;
	char	*msg2;

	msg1 = ft_strdup(i18n(syntaxerrornearunexpectedtoken1, get_lang(envp)));
	msg2 = ft_strdup(i18n(syntaxerrornearunexpectedtoken2, get_lang(envp)));
	ft_putstr_fd(msg1, STDERR_FILENO);
	ft_putstr_fd(token, STDERR_FILENO);
	ft_putstr_fd(msg2, STDERR_FILENO);
	free(msg1);
	free(msg2);
	set_exit_status(2);
	node->syntax_flag = true;
	return (false);
}

bool	semicolon_syntax_check(char **split, char **envp, t_node *node)
{
	bool	empty;
	int		i;
	int		j;
	char	semicolon[2];

	i = -1;
	while (split[++i])
	{
		empty = true;
		j = -1;
		while (split[i][++j])
			if (!ft_strchr(" \t", split[i][j]))
				empty = false;
		if (empty)
		{
			ft_strlcpy(semicolon, ";", 2);
			return (error_message(semicolon, envp, node));
		}
	}
	return (true);
}

static bool	handle_pipe_amp_counts(char *str, t_node *node)
{
	int	i;
	int	pipe_count;
	int	amp_count;

	i = 0;
	pipe_count = 0;
	amp_count = 0;
	while (str[i])
	{
		if (str[i] == '|')
		{
			pipe_count++;
			amp_count = 0;
			if (pipe_count >= 3)
				return (error_message("|", NULL, node));
		}
		else if (str[i] == '&')
		{
			amp_count++;
			pipe_count = 0;
			if (amp_count >= 3)
				return (error_message("&", NULL, node));
		}
		else
		{
			pipe_count = 0;
			amp_count = 0;
		}
		i++;
	}
	return (true);
}

static bool	handle_redirect_ampersand(char *str, t_node *node)
{
	int	i;
	int	j;

	i = 0;
	while (str[i])
	{
		if (str[i] == '>' && !quote_check(str, i, node))
		{
			j = i + 1;
			while (str[j] && ft_strchr(" \t", str[j]))
				j++;
			if (str[j] == '&' && str[j + 1] == '&')
				return (error_message("&&", NULL, node));
			else if (str[j] == '&')
				return (error_message("&", NULL, node));
		}
		i++;
	}
	return (true);
}

bool	check_invalid_operator_sequences_in_string(char *str, t_node *node)
{
	if (!handle_pipe_amp_counts(str, node))
		return (false);
	if (!handle_redirect_ampersand(str, node))
		return (false);
	return (true);
}

char	**process_semicolon_commands(char **split, char **envp, t_node *node)
{
	int	i;
	int	last;

	if (split[0] && split[0][ft_strlen(split[0]) - 1] == ';')
		last = -1;
	else
		last = (int)strarrlen(split);
	i = -1;
	while (!node->syntax_flag && split[++i])
	{
		node->last = (i == last - 1 && last != -1);
		if (!node->syntax_flag)
			envp = split_operators(split[i], envp, node);
	}
	return (envp);
}
