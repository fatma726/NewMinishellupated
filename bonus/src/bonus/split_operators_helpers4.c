/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_operators_helpers4.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatmtahmdabrahym <fatmtahmdabrahym@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 18:50:00 by fatmtahmdab      #+#    #+#             */
/*   Updated: 2025/10/06 18:50:00 by fatmtahmdab      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "../../include/bonus.h"

char	**handle_syntax_errors(char *s, int i, char **envp, t_node *n)
{
	if (handle_invalid_start_and_report(s, (size_t)i, n))
		return (envp);
	if (has_triple_ops(s, (size_t)i))
		return (syntax_err_pair(s, (size_t)i, n, 0), envp);
	if (ft_strchr(s, '>') && !check_redirection_syntax(s, n))
		return (free(s), envp);
	return (NULL);
}
