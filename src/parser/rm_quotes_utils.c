/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rm_quotes_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatmtahmdabrahym <fatmtahmdabrahym@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 15:40:00 by fatmtahmdab       #+#    #+#             */
/*   Updated: 2025/09/21 15:40:00 by fatmtahmdab      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*return_marked_unchanged(char *str)
{
	char	*newstr;
	size_t	len;

	len = ft_strlen(str);
	if (len == 0)
		return (str);
	newstr = (char *)malloc(len);
	if (!newstr)
	{
		free(str);
		exit(EXIT_FAILURE);
	}
	ft_memcpy(newstr, str + 1, len);
	newstr[len - 1] = '\0';
	free(str);
	return (newstr);
}

void	strip_wildmarks_inplace(char **args)
{
	int		i;
	char	*tmp;
	size_t	len;

	i = 0;
	while (args && args[i])
	{
		if (args[i][0] == (char)WILDMARK)
		{
			len = ft_strlen(args[i]);
			tmp = (char *)malloc(len);
			if (!tmp)
				exit(EXIT_FAILURE);
			ft_memcpy(tmp, args[i] + 1, len);
			tmp[len - 1] = '\0';
			free(args[i]);
			args[i] = tmp;
		}
		i++;
	}
}
