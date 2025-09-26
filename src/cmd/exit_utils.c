/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatmtahmdabrahym <fatmtahmdabrahym@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by kyung-ki          #+#    #+#             */
/*   Updated: 2025/09/26 18:20:09 by fatmtahmdab      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <limits.h>
#include <readline/readline.h>
#include <readline/history.h>

static bool	parse_strict_ll(const char *s, long long *out)
{
	long long	res;
	int			sign;
	size_t		i;

	if (!s)
		return (false);
	i = 0;
	while ((s[i] > '\b' && s[i] <= '\r') || s[i] == ' ')
		i++;
	sign = 1;
	if (s[i] == '+' || s[i] == '-')
	{
		sign = (s[i] == '-') ? -1 : 1;
		i++;
	}
	if (!ft_isdigit(s[i]))
		return (false);
	res = 0;
	if (sign > 0)
	{
		while (ft_isdigit(s[i]))
		{
			int d = s[i] - '0';
			if (res > (LLONG_MAX - d) / 10)
				return (false);
			res = res * 10 + d;
			i++;
		}
	}
	else
	{
		while (ft_isdigit(s[i]))
		{
			int d = s[i] - '0';
			if (res < (LLONG_MIN + d) / 10)
				return (false);
			res = res * 10 - d;
			i++;
		}
	}
	while ((s[i] > '\b' && s[i] <= '\r') || s[i] == ' ')
		i++;
	if (s[i] != '\0')
		return (false);
	*out = res;
	return (true);
}

static int	normalize_status(long long n)
{
	/* Match bash: exit value is truncated to unsigned char */
	return ((int)((unsigned char)n));
}

bool	handle_exit_with_args(char **args)
{
	long long	exit_num;

	if (!ft_isalldigit(args[1]))
	{
		handle_numeric_error(args[1]);
		return (true);
	}
	if (strarrlen(args) > 2)
	{
		handle_too_many_args();
		return (false);
	}
	if (!parse_strict_ll(args[1], &exit_num))
	{
		handle_numeric_error(args[1]);
		return (true);
	}
	set_exit_status(normalize_status(exit_num));
	return (true);
}

void	cleanup_and_exit(char **args, char **envp, t_node *node)
{
	free(node->pwd);
	if (node->path_fallback)
		free(node->path_fallback);
	if (node->ori_args)
	{
		strarrfree(node->ori_args);
		node->ori_args = NULL;
	}
	strarrfree(args);
	strarrfree(envp);
	clear_history();
	restore_termios();
	exit(get_exit_status());
}
