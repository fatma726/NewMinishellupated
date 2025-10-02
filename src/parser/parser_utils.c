/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatmtahmdabrahym <fatmtahmdabrahym@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by fatima            #+#    #+#             */
/*   Updated: 2025/09/30 23:46:10 by fatmtahmdab      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

char	*expand_prompt(char *fmt, char **envp, t_node *node)
{
	int		l;
	char	*new_fmt;
	char	*pwd;
	char	*pwd_orig;

	if (ft_getenv("PWD", envp))
		pwd_orig = ft_getenv("PWD", envp);
	else
		pwd_orig = node->pwd;
	pwd = get_pwd_for_prompt(envp, node);
	l = promptlen(fmt, envp, pwd, -1);
	if (!l)
	{
		free(fmt);
		if (pwd != pwd_orig)
			free(pwd);
		return (NULL);
	}
	new_fmt = expand_loop(fmt - 1, malloc((size_t)(l + 1)),
			ft_getenv("USER", envp), pwd);
	new_fmt[l] = '\0';
	free(fmt);
	if (pwd != pwd_orig)
		free(pwd);
	return (new_fmt);
}

char	**find_command(char **args, char **envp, t_node *node)
{
	int	i;

	if (!args || !args[0])
		return (envp);
	i = 0;
	while (args[i] && args[i + 1] && !isp(node->ori_args[i + 1]))
		i++;
	envp = ft_setenv_envp("_", args[i], envp);
	return (dispatch_builtin(args, envp, node));
}

/* From parser_helpers2.c */
char	**dispatch_builtin(char **args, char **envp, t_node *node)
{
	if (args[0] && !ft_strncmp(args[0], "cd", 3))
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
	else if (args[0])
		envp = cmd_exec(args, envp, node);
	return (envp);
}

/* From hash_handler.c */
static void	limit_history_size(void)
{
	int	history_size;
	int	i;

	history_size = history_length;
	if (history_size > 50)
	{
		i = 0;
		while (i < history_size - 50)
		{
			remove_history(0);
			i++;
		}
	}
}

char	*hash_handler(char *str, t_node *node)
{
	unsigned int	i;
	char			*new_str;

	if (isatty(STDIN_FILENO) && ft_strlen(str) && ft_strlen(str) < 1000)
	{
		add_history(str);
		limit_history_size();
	}
	node->syntax_flag = false;
	i = 0;
	while (str[i] && (str[i] != '#' || quote_check(str, (int)i, node)
			|| (i && !ft_strchr(" \t", str[i - 1]))))
		i++;
	if (i == ft_strlen(str))
		return (str);
	new_str = ft_substr(str, 0, i);
	free(str);
	return (new_str);
}
