/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racamach <racamach@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 11:31:38 by racamach          #+#    #+#             */
/*   Updated: 2024/11/04 21:00:39 by racamach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h>
#include <unistd.h>

char *get_next_line(int fd)
{
    static t_list *buffer_list;
    char *buffer;
    char *line;
    int bytes_read;

    if (fd < 0 || BUFFER_SIZE <= 0)
        return (NULL);
    buffer = (char *)malloc(BUFFER_SIZE + 1);
    if (!buffer)
        return (NULL);
    bytes_read = 1;
    while (!newline(buffer_list) && bytes_read > 0)
    {
        bytes_read = read(fd, buffer, BUFFER_SIZE);
        if (bytes_read < 0)
            return (free(buffer), free_until_newline(buffer_list), NULL);
        buffer[bytes_read] = '\0';
        if (!ft_lstcreate_and_add_back(&buffer_list, ft_strdup(buffer)))
            return (free(buffer), free_until_newline(buffer_list), NULL);
    }
    free(buffer);
    if (!buffer_list)
        return (NULL);
    line = get_line_from_buffer(buffer_list);
    buffer_list = free_until_newline(buffer_list);
    return (line);
}


t_list *free_until_newline(t_list *buffer_list)
{
    t_list  *temp;
    char    *newline_pos;

    if (!buffer_list)
        return (NULL);
    while (buffer_list)
    {
        newline_pos = ft_strchr(buffer_list->content, '\n');
        if (newline_pos && *(newline_pos + 1))
        {
            temp = create_node(ft_strdup(newline_pos + 1));
            return (free(buffer_list->content), free(buffer_list), temp);
        }
        temp = buffer_list->next;
        free(buffer_list->content);
        free(buffer_list);
        buffer_list = temp;
    }
    return (NULL);
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

