/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatima <fatima@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by lcouturi          #+#    #+#             */
/*   Updated: 2025/09/03 08:41:49 by fatima           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	*add_spaces_around_ampersand(char *str, t_node *node)
{
	char	*result;
	int		i;
	int		j;
	size_t	len;

	if (!str)
		return (NULL);
	len = ft_strlen(str);
	result = malloc((len * 2 + 1) * sizeof(char));
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '&' && !quote_check(str, i, node))
		{
			if (i == 0 || str[i - 1] != '&')
			{
				if (i > 0 && str[i - 1] != ' ' && str[i - 1] != '\t')
					result[j++] = ' ';
				result[j++] = '&';
				if (str[i + 1] && str[i + 1] != '&'
					&& str[i + 1] != ' ' && str[i + 1] != '\t')
					result[j++] = ' ';
			}
			else
				result[j++] = '&';
		}
		else
			result[j++] = str[i];
		i++;
	}
	result[j] = '\0';
	free(str);
	return (result);
}

char	**find_command(char **args, char **envp, t_node *node)
{
    int	i;

    if (!args || !args[0])
        return (envp);
    i = 0;
    while (args[i] && args[i + 1] && !isp(node->ori_args[i + 1]))
        i++;
    envp = ft_setenv("_", args[i], envp);
	if (args[0] && !ft_strncmp(args[0], "alias", 6))
		cmd_alias(args, envp, node);
	else if (args[0] && !ft_strncmp(args[0], "cd", 3))
		envp = cmd_cd(args, envp, node);
	else if (args[0] && !ft_strncmp(args[0], "exit", 5))
		cmd_exit(args, envp, node);
	else if (args[0] && !ft_strncmp(args[0], "env", 4))
		envp = cmd_env(args, envp, node);
	else if (args[0] && !ft_strncmp(args[0], "export", 7))
		envp = cmd_export(args, envp, node);
	else if (args[0] && !ft_strncmp(args[0], "pwd", 4))
		cmd_pwd(node);
	else if (args[0] && !ft_strncmp(args[0], "echo", 5))
		cmd_echo(args, node);
	else if (args[0] && !ft_strncmp(args[0], "unset", 6))
		envp = cmd_unset(args, envp, node);
	else if (args[0] && !ft_strncmp(args[0], "history", 8))
		cmd_history(args, node);
	else if (args[0])
		envp = cmd_exec(args, envp, node);
	return (envp);
}

static char	**process_parser_input(char *str, char **envp, t_node *node)
{
	char	**args;
	char	charset[4];

	str = expand_alias(expand_envvar(str, envp, node), node);
	str = add_spaces_around_ampersand(str, node);
	ft_strlcpy(charset, " \t", 4);
	args = escape_split(str, charset, node);
	args = expand_wildcard(args, envp, node);
	free(str);
	node->ori_args = strarrdup(args);
	return (args);
}

static char	**handle_parser_errors(char **args, char **envp, t_node *node)
{
	if (!args)
		return (envp);
	if (args[0] && !syntax_check(node->ori_args, envp, node))
	{
		handle_syntax_error(envp, node);
		strarrfree(args);
		strarrfree(node->ori_args);
		return (envp);
	}
	return (NULL);
}

static char	**process_quotes_and_exec(char **args, char **envp, t_node *node)
{
	args = rm_quotes(args, node);
	if (!args)
	{
		clear_history();
		strarrfree(envp);
		exit(EXIT_FAILURE);
	}
	envp = execute(args, envp, node);
	strarrfree(args);
	strarrfree(node->ori_args);
	return (envp);
}

char	**parser(char *str, char **envp, t_node *node)
{
	char	**args;

	args = process_parser_input(str, envp, node);
	if (handle_parser_errors(args, envp, node))
		return (envp);
	return (process_quotes_and_exec(args, envp, node));
}
