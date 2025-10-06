/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_operators_main.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatmtahmdabrahym <fatmtahmdabrahym@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by fatima            #+#    #+#             */
/*   Updated: 2025/10/06 21:32:02 by fatmtahmdab      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/bonus.h"

void	advance_to(char *s, size_t *i, t_node *n, char op)
{
	int	depth;

	depth = 0;
	while (s[*i])
	{
		if (!quote_check(s, (int)*i, n))
		{
			if (s[*i] == '(')
				depth++;
			else if (s[*i] == ')')
				depth -= (depth > 0);
			else if (depth == 0)
			{
				if (op == '|' && s[*i] == '&' && s[*i + 1] == '&')
					break ;
				if (op == '&' && s[*i] == '|' && s[*i + 1] == '|')
					break ;
			}
		}
		(*i)++;
	}
}

int	find_top_level_op(char *s, t_node *n)
{
	int	i;
	int	depth;

	i = 0;
	depth = 0;
	while (s[i])
	{
		if (!quote_check(s, i, n))
		{
			if (s[i] == '(')
				depth++;
			else if (s[i] == ')')
				depth -= (depth > 0);
			else if (depth == 0 && is_operator_pair(s, (size_t)i, n))
				return (i);
			else if (depth == 0 && s[i] == '&' && s[i + 1] != '&')
				return (i);
		}
		i++;
	}
	return (-1);
}

/* moved is_wrapped_group to helpers3 */

static char	**eval_group(char *inner, char **envp, t_node *n)
{
	int		pid;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		envp = process_command(inner, envp, n);
		cleanup_env(envp, n);
		exit(get_exit_status());
	}
	free(inner);
	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status))
		set_exit_status(128 + WTERMSIG(status));
	else if (WIFEXITED(status))
		set_exit_status(WEXITSTATUS(status));
	else
		set_exit_status(0);
	return (envp);
}

/* split_operators_tail moved to helpers3 */
/* handle_syntax_errors moved to split_operators_helpers2.c */

static char	**split_operators_after_index(
	char *s, int i, char **envp, t_node *n)
{
	char	*left;
	char	**result;

	if (i < 0)
		return (parser(s, envp, n));
	result = handle_syntax_errors(s, i, envp, n);
	if (result)
		return (result);
	left = ft_substr(s, 0, (size_t)i);
	if (!left)
		return (free(s), envp);
	envp = parser(left, envp, n);
	return (split_operators_tail(s, (size_t)i, envp, n));
}

char	**split_operators(char *s, char **envp, t_node *n)
{
	int		i;
	size_t	inner_start;
	size_t	inner_len;
	char	*inner;

	if (n->syntax_flag)
	{
		free(s);
		return (envp);
	}
	if (has_mixed_op_error(s, n))
	{
		free(s);
		return (envp);
	}
	if (is_wrapped_group(s, n, &inner_start, &inner_len))
	{
		inner = ft_substr(s, (unsigned int)(inner_start), inner_len);
		free(s);
		if (!inner)
			return (envp);
		return (eval_group(inner, envp, n));
	}
	i = find_top_level_op(s, n);
	return (split_operators_after_index(s, i, envp, n));
}
