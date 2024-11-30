/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racamach <racamach@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 11:31:38 by racamach          #+#    #+#             */
/*   Updated: 2024/11/30 03:01:02 by racamach         ###   ########.fr       */
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
	t_list	*current;
	size_t	i;

	len = 0;
	current = buffer_list;
	while (current)
	{
		i = 0;
		while (current->content[i] && current->content[i] != '\n')
			i++;
		len += i + (current->content[i] == '\n');
		if (current->content[i] == '\n')
			break ;
		current = current->next;
	}
	if (!(line = malloc(len + 1)))
		return (NULL);
	line[0] = '\0';
	while (buffer_list && (ft_strlcat(line, buffer_list->content, len + 1), 1))
	{
		if (ft_strchr(buffer_list->content, '\n'))
			break ;
		buffer_list = buffer_list->next;
	}
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

char	*ft_strdup(char *s1)
{
	char	*duplicate;
	size_t	len;
	size_t	i;

	len = 0;
	while (s1[len] != '\0')
		len++;
	duplicate = (char *)malloc((len + 1) * sizeof(char));
	if (duplicate == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		duplicate[i] = s1[i];
		i++;
	}
	duplicate[i] = '\0';
	return (duplicate);
}

char	*ft_strchr(char *s, int c)
{
	while (*s != '\0')
	{
		if (*s == (char)c)
		{
			return ((char *)s);
		}
		s++;
	}
	if (*s == (char)c)
	{
		return ((char *)s);
	}
	return (NULL);
}

size_t	ft_strlcat(char *dest, const char *src, size_t n)
{
	size_t	dsize;
	size_t	ssize;
	size_t	i;

	dsize = 0;
	while (dest[dsize] != '\0')
		dsize++;
	ssize = 0;
	while (src[ssize] != '\0')
		ssize++;
	if (n == 0 || dsize >= n)
		return (ssize + n);
	i = 0;
	while (src[i] != '\0' && (dsize + i) < (n - 1))
	{
		dest[dsize + i] = src[i];
		i++;
	}
	dest[dsize + i] = '\0';
	return (dsize + ssize);
}

int	newline(t_list *buffer_list)
{
	t_list	*temp;

	temp = buffer_list;
	while (temp)
	{
		if (ft_strchr(temp->content, '\n'))
			return (1);
		temp = temp->next;
	}
	return (0);
}

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*current;
	t_list	*next;

	if (lst == NULL || del == NULL)
		return ;
	current = *lst;
	while (current != NULL)
	{
		next = current->next;
		del(current->content);
		free(current);
		current = next;
	}
	*lst = NULL;
}

int	main(void)
{
	int		fd;
	char	*line;

	// Open file for reading
	fd = open("HP1.txt", O_RDONLY);
	if (fd == -1)
	{
		printf("Error opening file\n");
		return (1);
	}
	// Read file line by line
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("%s", line);
		free(line);
	}
	close(fd);
	return (0);
}
