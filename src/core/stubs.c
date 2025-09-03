/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stubs.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatima <fatima@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by fatmtahmdab       #+#    #+#             */
/*   Updated: 2025/09/03 09:27:06 by fatima           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
t_language	get_lang(char **envp)
{
	(void)envp;
	return (english);
}

const char	*i18n(t_message arg, t_language language)
{
	static const char	*en[] = {
		": command not found\n",
		": filename argument required\n",
		": invalid alias name\n",
		": invalid alias name\n",
		": not a valid identifier\n",
		": not a valid identifier\n",
		": not found\n",
		": numeric argument required\n",
		": OLDPWD not set\n",
		": syntax error near unexpected token `",
		"'\n",
		": too many arguments\n"
	};

	(void)language;
	if (arg < 0 || arg > toomanyarguments)
		return ("");
	return (en[arg]);
}

#ifndef BUILD_BONUS
char	**split_operators(char *s, char **envp, t_node *n)
{
	(void)s;
	(void)n;
	return (envp);
}

char	**subshell(char *str, char **envp, t_node *node)
{
	(void)str;
	(void)node;
	return (envp);
}
#endif
