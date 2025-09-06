/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatmtahmdabrahym <fatmtahmdabrahym@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by lcouturi          #+#    #+#             */
/*   Updated: 2025/09/06 22:32:22 by fatmtahmdab      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "../../include/bonus.h"

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

static int	redir_ampersand_token(char *str, int i, t_node *node)
{
	if (str[i + 1] == '&'
		|| (str[i + 1] == '>' && str[i + 2] == '&'))
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `",
			STDERR_FILENO);
		if (str[i + 1] == '&' && str[i + 2] == '&')
			ft_putendl_fd("&&'", STDERR_FILENO);
		else
			ft_putendl_fd("&'", STDERR_FILENO);
		set_exit_status(2);
		node->syntax_flag = true;
		free(str);
		return (-1);
	}
	return (0);
}

static int	validate_parens(char *str, t_node *node, int *length)
{
	int			count;
	int			i;

	count = 0;
	*length = 0;
	i = -1;
	while (str[++i])
	{
		if (str[i] == '>' && !quote_check(str, i, node))
			if (redir_ampersand_token(str, i, node) == -1)
				return (-1);
		if ((str[i] == '(' || str[i] == ')') && !quote_check(str, i, node))
		{
			if (str[i] == '(')
				count++;
			else if (--count < 0)
				return (-2);
		}
		else
			(*length)++;
	}
	return (count);
}

static char	*process_parentheses(char *str, t_node *node)
{
	int			count;
	int			length;

	if (str && ft_strlen(str) >= 3 && ft_strncmp(str, ">>>", 3) == 0)
		return (handle_triple_redir_error(str, node));
	count = validate_parens(str, node, &length);
	if (count == -1)
		return (free(str), NULL);
	str = handle_paren_error(str, count);
	if (!str)
		return (NULL);
	return (create_clean_string(str, node, length));
}

char	**subshell(char *str, char **envp, t_node *node)
{
	if (ft_strchr(str, '\'') || ft_strchr(str, '"'))
	{
		str = process_parentheses(str, node);
		if (!str)
			return (NULL);
		return (split_operators(str, envp, node));
	}
	str = process_parentheses(str, node);
	if (!str)
		return (envp);
	return (split_operators(str, envp, node));
}
