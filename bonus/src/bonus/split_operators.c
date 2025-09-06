/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_operators.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatima <fatima@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by lcouturi          #+#    #+#             */
/*   Updated: 2025/09/04 11:02:50 by fatima           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "../../include/bonus.h"

static void	advance_to(char *s, size_t *i, t_node *n, char op)
{
	if (op == '|')
		while (s[*i]
			&& (s[*i] != '&' || s[*i + 1] != '&')
			&& !quote_check(s, (int)*i, n))
			(*i)++;
	else
		while (s[*i]
			&& (s[*i] != '|' || s[*i + 1] != '|')
			&& !quote_check(s, (int)*i, n))
			(*i)++;
}

/* syntax_err_pair moved to helpers2 */

static size_t	find_split_index(char *s, t_node *n)
{
	size_t	i;

	i = 0;
	while (s[i] && !is_operator_pair(s, i, n))
	{
		if (!quote_check(s, (int)i, n) && s[i] == '&' && s[i + 1] != '&')
			break ;
		i++;
	}
	return (i);
}

static char	**split_operators_tail(char *s, size_t i, char **envp, t_node *n)
{
	char	*new_str;
	int		skip;

	if (!s[i])
		return (envp);
	while (!get_exit_status() && s[i] && s[i] == '|' && s[i + 1] == '|')
		advance_to(s, &i, n, '|');
	while (get_exit_status() && s[i] && s[i] == '&' && s[i + 1] == '&')
		advance_to(s, &i, n, '&');
	if (s[i] == '&' && s[i + 1] != '&')
		skip = 1;
	else
		skip = 2;
	new_str = ft_substr(s, (unsigned int)(i + (size_t)skip),
			ft_strlen(s) - (i + (size_t)skip));
	free(s);
	return (split_operators(new_str, envp, n));
}

/* helpers moved to helpers2 */

char	**split_operators(char *s, char **envp, t_node *n)
{
	char	*new_str;
	size_t	i;

	if (n->syntax_flag)
		return (envp);
	if (has_mixed_op_error(s, n))
		return (envp);
	i = find_split_index(s, n);
	if (handle_invalid_start_and_report(s, i, n))
		return (envp);
	if (has_triple_ops(s, i))
		return (syntax_err_pair(s, i, n, 0), envp);
	if (ft_strchr(s, '>'))
		if (!check_redirection_syntax(s, n))
			return (envp);
	new_str = ft_substr(s, 0, i);
	envp = parser(new_str, envp, n);
	return (split_operators_tail(s, i, envp, n));
}
