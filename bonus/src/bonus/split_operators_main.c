/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_operators_main.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatmtahmdabrahym <fatmtahmdabrahym@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by fatima            #+#    #+#             */
/*   Updated: 2025/10/01 23:56:56 by fatmtahmdab      ###   ########.fr       */
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
	char	**envp_copy;

	pid = fork();
	if (pid == 0)
	{
		envp_copy = strarrdup(envp);
		parser(inner, envp_copy, n);
		strarrfree(envp_copy);
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

static char	**split_operators_after_index(
	char *s, int i, char **envp, t_node *n)
{
	char	*left;

	if (i < 0)
	{
		envp = parser(s, envp, n);
		return (envp);
	}
	if (handle_invalid_start_and_report(s, (size_t)i, n))
		return (envp);
	if (has_triple_ops(s, (size_t)i))
		return (syntax_err_pair(s, (size_t)i, n, 0), envp);
	if (ft_strchr(s, '>'))
		if (!check_redirection_syntax(s, n))
			return (envp);
	left = ft_substr(s, 0, (size_t)i);
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
		return (envp);
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
