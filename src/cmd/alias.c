/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatmtahmdabrahym <fatmtahmdabrahym@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by lcouturi          #+#    #+#             */
/*   Updated: 2025/08/30 02:36:18 by fatmtahmdab      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	handle_alias_search(char **aliases, char *arg, int i)
{
	char	*name;

	while (aliases[++i])
	{
		name = ft_substr(aliases[i], 0, (size_t)(ft_strchr(aliases[i], '=')
					- aliases[i]));
		if (!ft_strncmp(name, arg, ft_strlen(arg)))
		{
			printalias(aliases[i]);
			free(name);
			return ;
		}
		free(name);
	}
}

static void	handle_alias_not_found(char *arg)
{
	char	alias_error[20];
	char	not_found_msg[11];

	ft_strlcpy(alias_error, "minishell: alias: ", 20);
	ft_strlcpy(not_found_msg, "not found", 11);
	ft_putstr_fd(alias_error, STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putstr_fd(not_found_msg, STDERR_FILENO);
}

static void	alias_loop(char *arg, char **envp, t_node *node)
{
	if (arg[0] != '=' && ft_strchr(arg, '='))
	{
		set_alias(arg, envp, node);
		return ;
	}
	handle_alias_search(node->aliases, arg, -1);
	handle_alias_not_found(arg);
}

static void	print_all_aliases(t_node *node)
{
	unsigned int	i2;
	char			*lowest;
	char			*lowest_old;

	i2 = 0;
	while (i2 < strarrlen(node->aliases))
	{
		lowest = find_lowest_alias(node->aliases, lowest_old, i2);
		printalias(lowest);
		lowest_old = lowest;
		i2++;
	}
}

void	cmd_alias(char **args, char **envp, t_node *node)
{
	int	i;

	i = 0;
	while (args[++i])
		alias_loop(args[i], envp, node);
	if (i == 1)
		print_all_aliases(node);
}
