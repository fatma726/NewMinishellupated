/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_wildcard.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatmtahmdabrahym <fatmtahmdabrahym@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by lcouturi          #+#    #+#             */
/*   Updated: 2025/09/06 19:38:38 by fatmtahmdab      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/bonus.h"

char	**expand_wildcard(char **args, char **envp, t_node *node)
{
	char	**newargs;
	int		count;

	(void)envp;
	(void)node;
	count = count_wildcard_matches(args);
	if (count == 0)
		return (args);
	newargs = malloc((strarrlen(args) + (size_t)count) * sizeof(char *));
	if (!newargs)
		return (args);
	if (process_all_args(args, newargs) == -1)
	{
		cleanup_and_return(newargs, 0, args);
		return (NULL);
	}
	strarrfree(args);
	return (newargs);
}
