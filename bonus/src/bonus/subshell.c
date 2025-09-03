/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatmtahmdabrahym <fatmtahmdabrahym@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by lcouturi          #+#    #+#             */
/*   Updated: 2025/08/29 20:59:16 by fatmtahmdab      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*create_clean_string(char *str, t_node *node, int length)
{
	char	*new_str;
	size_t	size;
	int		i;

	size = (size_t)(length + 1) * sizeof(char);
	new_str = malloc(size);
	i = -1;
	length = 0;
	while (str[++i])
		if ((str[i] != '(' && str[i] != ')') || quote_check(str, i, node))
			new_str[length++] = str[i];
	new_str[length] = '\0';
	free(str);
	return (new_str);
}

static int	validate_parens(char *str, t_node *node, int *length)
{
	int	count;
	int	i;

	count = 0;
	*length = 0;
	i = -1;
	while (str[++i])
	{
		if ((str[i] != '(' && str[i] != ')') || quote_check(str, i, node))
		{
			(*length)++;
			continue ;
		}
		else if (str[i] == '(')
			count++;
		else if (--count < 0)
		{
			free(str);
			ft_putstr_fd("minishell: syntax error near unexpected token `)'\n",
				STDERR_FILENO);
			return (-1);
		}
	}
	return (count);
}

static char	*process_parentheses(char *str, t_node *node)
{
	int			count;
	int			length;
	const char	*msg;

	if (str && ft_strlen(str) >= 3 && ft_strncmp(str, ">>>", 3) == 0)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `>'\n",
			STDERR_FILENO);
		set_exit_status(2);
		node->syntax_flag = true;
		free(str);
		return (NULL);
	}
	count = validate_parens(str, node, &length);
	if (count == -1)
		return (NULL);
	if (count != 0)
	{
		msg = "minishell: syntax error near unexpected token `newline'\n";
		ft_putstr_fd(msg, STDERR_FILENO);
		free(str);
		return (NULL);
	}
	return (create_clean_string(str, node, length));
}

static char	**handle_quoted_content(char *str, char **envp, t_node *node)
{
	str = process_parentheses(str, node);
	if (!str)
		return (NULL);
	return (semicolon_handler(str, envp, node));
}

char	**subshell(char *str, char **envp, t_node *node)
{
	if (ft_strchr(str, '\'') || ft_strchr(str, '"'))
		return (handle_quoted_content(str, envp, node));
	str = process_parentheses(str, node);
	if (!str)
		return (envp);
	return (semicolon_handler(str, envp, node));
}
