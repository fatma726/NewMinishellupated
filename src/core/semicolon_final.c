/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semicolon_final.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatmtahmdabrahym <fatmtahmdabrahym@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by fatmtahmdab      #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by fatmtahmdab     ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**split_by_semicolons(char *line, t_node *n)
{
	char	**commands;
	size_t	count;

	count = count_semicolons(line, n);
	commands = malloc((count + 2) * sizeof(char *));
	if (!commands)
		return (NULL);
	return (process_semicolon_split(line, n, commands));
}
