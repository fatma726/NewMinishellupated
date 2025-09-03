/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatmtahmdabrahym <fatmtahmdabrahym@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by fatmtahmdab       #+#    #+#             */
/*   Updated: 2025/08/30 10:19:04 by fatmtahmdab      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	printalias(char *str)
{
	int		i;
	char	alias_msg[7];
	char	quote_msg[3];

	i = 0;
	ft_strlcpy(alias_msg, "alias ", 7);
	ft_strlcpy(quote_msg, "\'\n", 3);
	ft_putstr_fd(alias_msg, STDOUT_FILENO);
	ft_putchar_fd(str[i], STDOUT_FILENO);
	while (str[++i - 1] != '=')
		ft_putchar_fd(str[i], STDOUT_FILENO);
	ft_putchar_fd('\'', STDOUT_FILENO);
	while (str[i])
		ft_putchar_fd(str[i++], STDOUT_FILENO);
	ft_putstr_fd(quote_msg, STDOUT_FILENO);
}

void	set_alias(char *arg, char **envp, t_node *node)
{
	int		i;
	char	*name;
	char	invalid1[20];
	char	invalid2[20];

	(void)envp;
	i = -1;
	name = ft_substr(arg, 0, (size_t)(ft_strchr(arg, '=') - arg));
	while (name[++i])
	{
		if (ft_strchr("\t\n \"$&\'()/;<=>\\`|", name[i]))
		{
			ft_strlcpy(invalid1, "invalid alias name 1", 20);
			ft_strlcpy(invalid2, "invalid alias name 2", 20);
			ft_putstr_fd(invalid1, STDERR_FILENO);
			ft_putstr_fd(name, STDERR_FILENO);
			ft_putstr_fd(invalid2, STDERR_FILENO);
			break ;
		}
	}
	if (!name[i])
		node->aliases = ft_setenv(name, ft_strchr(arg, '=') + 1,
				node->aliases);
	free(name);
}

char	*find_lowest_alias(char **aliases, char *lowest_old, unsigned int i2)
{
	char	*lowest;
	int		i;

	lowest = NULL;
	i = -1;
	while (aliases[++i])
	{
		if ((!lowest || ft_strncmp(aliases[i], lowest,
					ft_strlen(aliases[i])) < 0)
			&& (!i2 || ft_strncmp(aliases[i], lowest_old,
					ft_strlen(aliases[i])) > 0))
			lowest = aliases[i];
	}
	return (lowest);
}
