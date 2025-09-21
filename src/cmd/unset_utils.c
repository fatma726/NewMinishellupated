/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatmtahmdabrahym <fatmtahmdabrahym@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by fatmtahmdabrahym #+#    #+#             */
/*   Updated: 2025/01/29 19:31:40 by fatmtahmdabrahym ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_invalid_identifier(char *arg)
{
	char	unset_error[25];
	char	not_valid[30];

	ft_strlcpy(unset_error, "minishell: unset: `", 25);
	ft_putstr_fd(unset_error, STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_strlcpy(not_valid, "': not a valid identifier\n", 30);
	ft_putstr_fd(not_valid, STDERR_FILENO);
}

void	process_unset_args(char **args, char **envp, t_node *node, int *flag)
{
	int		i;
	bool	has_error;

	i = 0;
	has_error = false;
	while (args[++i])
	{
		if (!is_valid_identifier(args[i]))
		{
			handle_invalid_identifier(args[i]);
			has_error = true;
		}
		else
			envp = delete_env(args[i], envp, node, flag);
	}
	if (has_error)
		set_exit_status(EXIT_FAILURE);
	else if (*flag != 1)
		set_exit_status(EXIT_FAILURE);
	else
		set_exit_status(EXIT_SUCCESS);
}
