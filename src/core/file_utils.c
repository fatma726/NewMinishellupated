/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatmtahmdabrahym <fatmtahmdabrahym@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by fatmtahmdab      #+#    #+#             */
/*   Updated: 2025/08/26 19:58:00 by fatmtahmdab      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	process_file_buffer(char *buffer, int *i)
{
	while (1)
	{
		if (buffer[*i] == '\n')
			break ;
		(*i)++;
		if (*i >= 1023)
			break ;
	}
}

static char	*read_file_line(int fd)
{
	char	buffer[1024];
	char	*line;
	ssize_t	bytes_read;
	size_t	i;

	line = malloc(1024);
	if (!line)
		return (NULL);
	i = 0;
	while (1)
	{
		bytes_read = read(fd, &buffer[i], 1);
		if (bytes_read <= 0)
			break ;
		process_file_buffer(buffer, (int *)&i);
		if (bytes_read <= 0 && i == 0)
		{
			free(line);
			return (NULL);
		}
		break ;
	}
	buffer[i] = '\0';
	ft_strlcpy(line, buffer, i + 1);
	return (line);
}

static void	process_file_content(t_list *lst, char **file)
{
	int		i;
	t_list	*old;

	i = 0;
	while (lst->content)
	{
		file[i] = malloc(ft_strlen(lst->content));
		ft_strlcpy(file[i], lst->content, ft_strlen(lst->content));
		free(lst->content);
		old = lst;
		lst = lst->next;
		free(old);
		if (!file[i++])
			break ;
	}
	file[i] = 0;
}

char	**get_file(int fd)
{
	char	**file;
	t_list	*lst;

	lst = ft_lstnew(read_file_line(fd));
	while (ft_lstlast(lst)->content)
		ft_lstadd_back(&lst, ft_lstnew(read_file_line(fd)));
	file = malloc((size_t)(ft_lstsize(lst) + 1) * 8);
	process_file_content(lst, file);
	free(lst->content);
	free(lst);
	return (file);
}
