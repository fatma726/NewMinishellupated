/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_envvar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatmtahmdabrahym <fatmtahmdabrahym@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by lcouturi          #+#    #+#             */
/*   Updated: 2025/08/28 21:18:18 by fatmtahmdab      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	insert_int(char *str, int *i)
{
	int	j;

	j = 1000000000;
	while (j)
	{
		if (get_exit_status() / j)
			str[i[1]++] = (char)(get_exit_status() / j % 10 + '0');
		j /= 10;
	}
	if (!get_exit_status())
		str[i[1]++] = '0';
	i[0] += 2;
}

static void	no_env(int *i, char *str, char *str2)
{
	if (!i[3] && (ft_strchr("<>|", str[i[0]]) || (str[i[0]] == '2' && str[i[0]
					+ 1] == '>')))
	{
		str2[i[1]++] = ' ';
		str2[i[1]++] = str[i[0]++];
		if (i[0] && str[i[0] - 1] == '2')
			str2[i[1]++] = str[i[0]++];
		else if (i[0] && str[i[0] - 1] == '>')
		{
			if (str[i[0]] == '>' || str[i[0]] == '|')
				str2[i[1]++] = str[i[0]++];
		}
		else if (i[0] && str[i[0] - 1] == '<')
		{
			if (str[i[0]] == '<' || str[i[0]] == '>')
			{
				str2[i[1]++] = str[i[0]++];
				if (str[i[0]] == '<' && str[i[0] - 1] != '>')
					str2[i[1]++] = str[i[0]++];
			}
		}
		str2[i[1]++] = ' ';
	}
	else
		str2[i[1]++] = str[i[0]++];
}

static void	handle_envvar(int *i, char **str, char **envp, t_node *node)
{
	char	*var_name;
	char	*var_value;

	(void)envp;
	i[5] = ++i[0];
	while (ft_isalnum(str[0][i[5]]) || str[0][i[5]] == '_')
		i[5]++;
	var_name = ft_substr(str[0], (unsigned int)i[0], (size_t)(i[5] - i[0]));
	var_value = getenv(var_name);
	if (var_value)
	{
		while (*var_value)
		{
			if (ft_strchr("<>|", *var_value))
			{
				str[1][i[1]++] = '\\';
				node->escape_skip = false;
			}
			str[1][i[1]++] = *var_value++;
		}
	}
	free(var_name);
	i[0] = i[5];
}

static void	expand_envvar_loop(char **str, char **envp, t_node *node)
{
	int	i[7];

	i[0] = 0;
	i[1] = 0;
	while (str[0][i[0]])
	{
		i[3] = quote_check(str[0], i[0], node);
		if (in_heredoc(str[0], i[0]))
			no_env(i, str[0], str[1]);
		else if (i[3] < 2 && str[0][i[0]] == '$' && (ft_isalnum(str[0][i[0]
					+ 1]) || str[0][i[0] + 1] == '_' || (i[3] != 1
					&& str[0][i[0] + 1] == '\"') || (i[3] < 2 && str[0][i[0]
					+ 1] == '\'')))
			handle_envvar(i, str, envp, node);
		else if (i[3] < 2 && !ft_strncmp(str[0] + i[0], "$?", 2))
			insert_int(str[1], i);
		else
			no_env(i, str[0], str[1]);
	}
	str[1][i[1]] = '\0';
}

char	*expand_envvar(char *str, char **envp, t_node *node)
{
	int		i[6];
	char	*strs[2];

	i[0] = -1;
	i[5] = 0;
	while (str[++i[0]])
	{
		get_length(str, envp, i, node);
		if (!str[i[0]])
			break ;
	}
	strs[1] = malloc(((size_t)i[5] + 1) * sizeof(char));
	if (!strs[1])
	{
		free(str);
		strarrfree(envp);
		exit(EXIT_FAILURE);
	}
	strs[0] = str;
	expand_envvar_loop(strs, envp, node);
	free(str);
	return (strs[1]);
}
