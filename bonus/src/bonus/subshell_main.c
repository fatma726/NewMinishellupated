/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshell_main.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatmtahmdabrahym <fatmtahmdabrahym@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by fatima            #+#    #+#             */
/*   Updated: 2025/09/20 17:10:30 by fatmtahmdab      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "../../include/bonus.h"

char	*create_clean_string(char *str, t_node *node, int length);
int		validate_parens(char *str, t_node *node, int *length);

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
