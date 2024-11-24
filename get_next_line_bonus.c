/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racamach <racamach@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 19:16:00 by racamach          #+#    #+#             */
/*   Updated: 2024/11/24 00:17:32 by racamach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*get_next_line(int fd)
{
	static t_list	*buffer_list[FOPEN_MAX];
	char			*line;

	if (fd < 0 || fd >= FOPEN_MAX || BUFFER_SIZE <= 0)
		return (NULL);
	if (!read_to_buffer_list(fd, &buffer_list[fd]))
		return (NULL);
	if (!buffer_list[fd])
		return (NULL);
	line = get_line_from_buffer(buffer_list[fd]);
	free_until_newline(&buffer_list[fd]);
	if (!buffer_list[fd])
		buffer_list[fd] = NULL;
	return (line);
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
		if (bytes_read < 0)
			return (free(buffer), free_until_newline(buffer_list), 0);
		if (bytes_read > 0)
		{
			buffer[bytes_read] = '\0';
			if (!ft_lstcreate_and_add_back(buffer_list, ft_strdup(buffer)))
				return (free(buffer), free_until_newline(buffer_list), 0);
		}
	}
	return (free(buffer), 1);
}

void	free_until_newline(t_list **buffer_list)
{
	t_list	*temp;
	char	*newline_pos;

	while (*buffer_list)
	{
		newline_pos = ft_strchr((*buffer_list)->content, '\n');
		if (newline_pos && *(newline_pos + 1))
		{
			temp = (t_list *)malloc(sizeof(t_list));
			if (!temp)
				return ;
			temp->content = ft_strdup(newline_pos + 1);
			if (!temp->content)
				return (free(temp), (void)0);
			temp->next = NULL;
			(free((*buffer_list)->content), free(*buffer_list));
			*buffer_list = temp;
			return ;
		}
		temp = (*buffer_list)->next;
		(free((*buffer_list)->content), free(*buffer_list));
		*buffer_list = temp;
	}
}

char	*ft_strchr(const char *s, int c)
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