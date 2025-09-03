/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatmtahmdabrahym <fatmtahmdabrahym@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by fatmtahmdab       #+#    #+#             */
/*   Updated: 2025/08/30 10:00:04 by fatmtahmdab      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	print_declare_line(char *entry)
{
    size_t	i;
    char	*name;
    char	*value;

    i = 0;
    while (entry[i] && entry[i] != '=')
        i++;
    name = ft_substr(entry, 0, i);
    if (entry[i] == '=')
        value = ft_strdup(entry + i + 1);
    else
        value = NULL;
    ft_putstr_fd("declare -x ", STDOUT_FILENO);
    ft_putstr_fd(name, STDOUT_FILENO);
    if (value && (value[0] || ft_strncmp(name, "OLDPWD", 7)))
    {
        ft_putstr_fd("=\"", STDOUT_FILENO);
        ft_putstr_fd(value, STDOUT_FILENO);
        ft_putstr_fd("\"", STDOUT_FILENO);
    }
    ft_putchar_fd('\n', STDOUT_FILENO);
    free(name);
    if (value)
        free(value);
}

char	**export_print(char **envp)
{
	int		i;
	size_t	i2;
	char	*lowest;
	char	*lowest_old;

	i2 = 0;
	while (i2 < strarrlen(envp))
	{
		lowest = 0;
		i = -1;
		while (envp[++i])
			if ((!lowest || ft_strncmp(envp[i], lowest, ft_strlen(envp[i])) < 0)
				&& (!i2 || ft_strncmp(envp[i], lowest_old,
						ft_strlen(envp[i])) > 0))
				lowest = envp[i];
		if (lowest && ft_strncmp(lowest, "_=", 2))
			print_declare_line(lowest);
		lowest_old = lowest;
		i2++;
	}
	fflush(stdout);
	return (envp);
}

void	handle_export_option_error(char **args)
{
	char	export_error[25];
	char	invalid_option[50];
	char	usage[50];

	ft_strlcpy(export_error, "minishell: export: ", 25);
	ft_putstr_fd(export_error, STDERR_FILENO);
	ft_putstr_fd(args[1], STDERR_FILENO);
	ft_strlcpy(invalid_option, ": invalid option\nexport: usage: export ", 50);
	ft_putstr_fd(invalid_option, STDERR_FILENO);
	ft_strlcpy(usage, "[-fn] [name[=value] ...] or export -p\n", 50);
	ft_putstr_fd(usage, STDERR_FILENO);
	set_exit_status(2);
}

void	process_export_args(char **args, char ***envp, t_node *node)
{
	int		i;
	bool	has_error;

	i = 0;
	has_error = false;
	while (args[++i] && (!node->pipe_idx || i + 1 < node->pipe_idx))
	{
		if (!process_export_arg(args[i], envp, node))
			has_error = true;
		// Continue processing remaining arguments even if one fails
	}
	if (has_error)
		set_exit_status(EXIT_FAILURE);
}
