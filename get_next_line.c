/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racamach <racamach@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 11:31:38 by racamach          #+#    #+#             */
/*   Updated: 2024/11/30 15:51:56 by racamach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	ft_lstcreate_and_add_back(t_list **lst, char *content)
{
	t_list	*new_node;
	t_list	*last;

	if (!lst || !content)
		return (0);
	new_node = (t_list *)malloc(sizeof(t_list));
	if (!new_node)
		return (0);
	new_node->content = content;
	new_node->next = NULL;
	if (*lst == NULL)
		*lst = new_node;
	else
	{
		last = *lst;
		while (last->next)
			last = last->next;
		last->next = new_node;
	}
	return (1);
}

char	*get_line_from_buffer(t_list *buffer_list)
{
	char	*line;
	size_t	len;
	size_t	i;
	size_t	line_index;

	len = calculate_line_length(buffer_list);
	line = malloc(len + 1);
	if (!line)
		return (NULL);
	line_index = 0;
	while (buffer_list && line_index < len)
	{
		i = 0;
		while (buffer_list->content[i] && buffer_list->content[i] != '\n'
			&& line_index < len)
			line[line_index++] = buffer_list->content[i++];
		if (buffer_list->content[i] == '\n' && line_index < len)
		{
			line[line_index++] = '\n';
			break ;
		}
		buffer_list = buffer_list->next;
	}
	line[line_index] = '\0';
	return (line);
}

void	free_until_newline(t_list **buffer_list)
{
	t_list	*temp;
	char	*newline_pos;

	if (!buffer_list || !*buffer_list)
		return ;
	newline_pos = ft_strchr((*buffer_list)->content, '\n');
	if (newline_pos && *(newline_pos + 1))
	{
		temp = (t_list *)malloc(sizeof(t_list));
		if (!temp)
			return (ft_lstclear(buffer_list, free), (void)0);
		temp->content = ft_strdup(newline_pos + 1);
		if (!temp->content)
		{
			free(temp);
			ft_lstclear(buffer_list, free);
			return ;
		}
		temp->next = NULL;
		ft_lstclear(buffer_list, free);
		*buffer_list = temp;
	}
	else
		ft_lstclear(buffer_list, free);
}

int	read_to_buffer_list(int fd, t_list **buffer_list)
{
	char	*buffer;
	int		bytes_read;

	buffer = (char *)malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (0);
	bytes_read = 1;
	while (!newline(*buffer_list) && bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read <= 0)
		{
			if (bytes_read == -1)
				ft_lstclear(buffer_list, free);
			free(buffer);
			return (bytes_read == 0);
		}
		buffer[bytes_read] = '\0';
		if (!ft_lstcreate_and_add_back(buffer_list, ft_strdup(buffer)))
			return (free(buffer), ft_lstclear(buffer_list, free), 0);
	}
	free(buffer);
	return (1);
}

char	*get_next_line(int fd)
{
	static t_list	*buffer_list;
	char			*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!read_to_buffer_list(fd, &buffer_list))
		return (NULL);
	if (!buffer_list)
		return (NULL);
	line = get_line_from_buffer(buffer_list);
	free_until_newline(&buffer_list);
	return (line);
}
