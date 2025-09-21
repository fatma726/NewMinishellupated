/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatmtahmdabrahym <fatmtahmdabrahym@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by fatmtahmdabrahym #+#    #+#             */
/*   Updated: 2025/01/29 19:31:40 by fatmtahmdabrahym ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	need_space_before(char *s, int i)
{
	return (i > 0 && s[i - 1] != ' ' && s[i - 1] != '\t');
}

static int	need_space_after(char *s, int i)
{
	return (s[i + 1] && s[i + 1] != '&' && s[i + 1] != ' ' && s[i + 1] != '\t');
}

static int	copy_with_ampersands(char *str, t_node *node, char *result)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '&' && !quote_check(str, i, node))
		{
			if (i == 0 || str[i - 1] != '&')
			{
				if (need_space_before(str, i))
					result[j++] = ' ';
				result[j++] = '&';
				if (need_space_after(str, i))
					result[j++] = ' ';
			}
			else
				result[j++] = '&';
		}
		else
			result[j++] = str[i];
		i++;
	}
	return (j);
}

char	*add_spaces_around_ampersand(char *str, t_node *node)
{
	char	*result;
	size_t	len;

	if (!str)
		return (NULL);
	len = ft_strlen(str);
	result = malloc((len * 2 + 1) * sizeof(char));
	if (!result)
	{
		free(str);
		return (NULL);
	}
	len = (size_t)copy_with_ampersands(str, node, result);
	result[len] = '\0';
	free(str);
	return (result);
}

char	**find_command(char **args, char **envp, t_node *node)
{
	int	i;

	if (!args || !args[0])
		return (envp);
	i = 0;
	while (args[i] && args[i + 1] && !isp(node->ori_args[i + 1]))
		i++;
	envp = ft_setenv_envp("_", args[i], envp);
	return (dispatch_builtin(args, envp, node));
}
