/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcouturi <lcouturi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 12:34:09 by lcouturi          #+#    #+#             */
/*   Updated: 2023/10/27 13:43:24 by lcouturi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	i2;

	i = 0;
	i2 = 0;
	if (!haystack || !needle || !needle[0])
		return (haystack);
	while (haystack[i] && i < len)
	{
		while (haystack[i] == needle[i2] && i < len)
		{
			if (!needle[i2 + 1])
			{
				return (&haystack[i - i2]);
			}
			i++;
			i2++;
		}
		i -= i2;
		i++;
		i2 = 0;
	}
	return (0);
}
