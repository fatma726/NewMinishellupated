/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatmtahmdabrahym <fatmtahmdabrahym@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by kyung-ki          #+#    #+#             */
/*   Updated: 2025/08/28 19:29:48 by fatmtahmdab      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	printchar(char c)
{
	char	tab_escape[7];

	if (c == '\\' || c == '\"' || c == '$')
		ft_putchar_fd('\\', STDOUT_FILENO);
	if (c == '\t')
	{
		ft_strlcpy(tab_escape, "$\'\\t\'", 7);
		ft_putstr_fd(tab_escape, STDOUT_FILENO);
	}
	else
		ft_putchar_fd(c, STDOUT_FILENO);
}

static void	print_variable_name(char *str)
{
	int	i;

	i = 0;
	ft_putchar_fd(str[i], STDOUT_FILENO);
	while (str[++i - 1] != '=')
	{
		if (!str[i - 1])
		{
			ft_putchar_fd('\n', STDOUT_FILENO);
			return ;
		}
		ft_putchar_fd(str[i], STDOUT_FILENO);
	}
}

static void	print_variable_value(char *str, int start)
{
	int		i;
	char	quote_newline[3];
	char	newline[2];

	i = start;
	if (!ft_strchr(str, '\t'))
		ft_putchar_fd('\"', STDOUT_FILENO);
	while (str[i])
		printchar(str[i++]);
	if (!ft_strchr(str, '\t'))
	{
		ft_strlcpy(quote_newline, "\"\n", 3);
		ft_putstr_fd(quote_newline, STDOUT_FILENO);
	}
	else
	{
		ft_strlcpy(newline, "\n", 2);
		ft_putstr_fd(newline, STDOUT_FILENO);
	}
}

void	printenv(char *str)
{
	char	declare_x[13];

	ft_strlcpy(declare_x, "declare -x ", 13);
	ft_putstr_fd(declare_x, STDOUT_FILENO);
	print_variable_name(str);
	if (ft_strchr(str, '='))
		print_variable_value(str, (int)(ft_strchr(str, '=') - str + 1));
}
