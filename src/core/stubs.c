/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stubs.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatima <fatima@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by fatmtahmdab       #+#    #+#             */
/*   Updated: 2025/09/03 09:27:06 by fatima           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Removed internationalization system - not required for evaluation

#ifndef BUILD_BONUS

char	**split_operators(char *s, char **envp, t_node *n)
{
	(void)s;
	(void)n;
	return (envp);
}

char	**subshell(char *str, char **envp, t_node *node)
{
	return (parser(str, envp, node));
}

#endif
