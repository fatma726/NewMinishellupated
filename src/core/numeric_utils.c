/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   numeric_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatmtahmdabrahym <fatmtahmdabrahym@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by fatmtahmdab      #+#    #+#             */
/*   Updated: 2025/08/26 19:55:00 by fatmtahmdab      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

long	ft_atol(const char *str)
{
	long	i[3];

	if (!str)
		return (0);
	i[0] = 0;
	i[2] = 0;
	i[1] = 1;
	while (1)
	{
		if ((str[i[0]] > '\b' && str[i[0]] <= '\r') || str[i[0]] == ' ')
			i[0]++;
		else
			break ;
	}
	if (str[i[0]] == '-')
		i[1] = -1;
	i[0] += (str[i[0]] == '+' || str[i[0]] == '-');
	while (str[i[0]] >= '0' && str[i[0]] <= '9')
		i[2] = i[2] * 10 + (str[i[0]++] - '0');
	return (i[2] *= i[1], i[2]);
}

long long	ft_atoll(const char *str)
{
	long long	i[3];

	if (!str)
		return (0);
	i[0] = 0;
	i[2] = 0;
	i[1] = 1;
	while (1)
	{
		if ((str[i[0]] > '\b' && str[i[0]] <= '\r') || str[i[0]] == ' ')
			i[0]++;
		else
			break ;
	}
	if (str[i[0]] == '-')
		i[1] = -1;
	i[0] += (str[i[0]] == '+' || str[i[0]] == '-');
	while (str[i[0]] >= '0' && str[i[0]] <= '9')
		i[2] = i[2] * 10 + (str[i[0]++] - '0');
	return (i[2] *= i[1], i[2]);
}
