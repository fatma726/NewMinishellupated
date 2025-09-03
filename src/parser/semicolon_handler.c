/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semicolon_handler.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatmtahmdabrahym <fatmtahmdabrahym@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by lcouturi          #+#    #+#             */
/*   Updated: 2025/08/30 10:07:56 by fatmtahmdab      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	handle_leading_semicolon(char **envp, t_node *node)
{
	char	semicolon[2];

	ft_strlcpy(semicolon, ";", 2);
	error_message(semicolon, envp, node);
}

static char	**process_semicolon_split(char *str, t_node *node)
{
	char	semicolon[2];
	char	**split;

	ft_strlcpy(semicolon, ";", 2);
	split = escape_split(str, semicolon, node);
	return (split);
}

static char	**process_semicolon_commands(char **split, char **envp, t_node *node)
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

static bool	check_invalid_operator_sequences_in_string(char *str, t_node *node)
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
			{
				node->syntax_flag = true;
				set_exit_status(2);
				ft_putstr_fd("minishell: syntax error near unexpected token `", STDERR_FILENO);
				ft_putchar_fd('|', STDERR_FILENO);
				ft_putendl_fd("'", STDERR_FILENO);
				return (false);
			}
		}
		else if (str[i] == '&')
		{
			amp_count++;
			pipe_count = 0;
			if (amp_count >= 3)
			{
				node->syntax_flag = true;
				set_exit_status(2);
				ft_putstr_fd("minishell: syntax error near unexpected token `", STDERR_FILENO);
				ft_putchar_fd('&', STDERR_FILENO);
				ft_putendl_fd("'", STDERR_FILENO);
				return (false);
			}
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

char	**semicolon_handler(char *str, char **envp, t_node *node)
{
	int		i;
	char	**split;

	if (node->syntax_flag)
	{
		free(str);
		return (envp);
	}
	// Check for invalid operator sequences before processing
	if (!check_invalid_operator_sequences_in_string(str, node))
	{
		free(str);
		return (envp);
	}
	i = 0;
	while (str[i] && ft_strchr(" \t", str[i]))
		i++;
	if (str[i] == ';')
	{
		handle_leading_semicolon(envp, node);
		return (envp);
	}
	i = -1;
	split = process_semicolon_split(str, node);
	if (ft_strchr(str, ';') && !semicolon_syntax_check(split, envp, node))
		return (strarrfree(split), envp);
	envp = process_semicolon_commands(split, envp, node);
	return (free(str), free(split), envp);
}
