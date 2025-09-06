/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_validation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatmtahmdabrahym <fatmtahmdabrahym@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 19:45:00 by fatmtahmdabrahym #+#    #+#             */
/*   Updated: 2025/01/29 19:45:00 by fatmtahmdabrahym ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#ifdef DEBUG_MEMORY

/**
 * @brief Validates environment array integrity
 * @param envp Environment array to validate
 * @return true if valid, false if corrupted
 */
bool	validate_env_array(char **envp)
{
	size_t	i;

	if (!envp)
		return (false);
	i = 0;
	while (envp[i])
	{
		if (!envp[i] || !ft_strchr(envp[i], '='))
			return (false);
		i++;
	}
	return (true);
}

/**
 * @brief Counts environment variables
 * @param envp Environment array
 * @return Number of environment variables
 */
size_t	count_env_vars(char **envp)
{
	size_t	count;

	if (!envp)
		return (0);
	count = 0;
	while (envp[count])
		count++;
	return (count);
}

/**
 * @brief Debug function to print environment array
 * @param envp Environment array to print
 * @param label Label for the output
 */
void	debug_print_env(char **envp, const char *label)
{
	size_t	i;

	if (!envp)
	{
		ft_putstr_fd("DEBUG: ", STDERR_FILENO);
		ft_putstr_fd(label, STDERR_FILENO);
		ft_putendl_fd(" - envp is NULL", STDERR_FILENO);
		return ;
	}
	ft_putstr_fd("DEBUG: ", STDERR_FILENO);
	ft_putstr_fd(label, STDERR_FILENO);
	ft_putstr_fd(" - Count: ", STDERR_FILENO);
	ft_putnbr_fd((int)count_env_vars(envp), STDERR_FILENO);
	ft_putendl_fd("", STDERR_FILENO);
	i = 0;
	while (envp[i] && i < 5)
	{
		ft_putstr_fd("  [", STDERR_FILENO);
		ft_putnbr_fd((int)i, STDERR_FILENO);
		ft_putstr_fd("] ", STDERR_FILENO);
		ft_putendl_fd(envp[i], STDERR_FILENO);
		i++;
	}
	if (envp[i])
		ft_putendl_fd("  ...", STDERR_FILENO);
}

#endif
