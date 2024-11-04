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
    static t_list    *buffer_list;
    char            *buffer;
    char            *line;
    int             bytes_read;

    if (fd < 0 || BUFFER_SIZE <= 0)
        return (NULL);
    buffer = (char *)malloc(BUFFER_SIZE + 1);
    if (!buffer)
        return (NULL);
    while (!newline(buffer_list))
    {
        bytes_read = read(fd, buffer, BUFFER_SIZE);
        if (bytes_read < 0)
        {
            free(buffer);
            free_until_newline(buffer_list);
            return (NULL);
        }
        if (bytes_read == 0)
            break;
        buffer[bytes_read] = '\0';
        if (!ft_lstcreate_and_add_back(&buffer_list, ft_strdup(buffer)))
        {
            free(buffer);
            free_until_newline(buffer_list);
            return (NULL);
        }
    }
    line = get_line_from_buffer(buffer_list);
    buffer_list = free_until_newline(buffer_list);
    return (free(buffer), line);
}

t_list	*create_node(char *content)
{
	t_list	*new_node;

	new_node = (t_list *)malloc(sizeof(t_list));
	if (!new_node)
		return (NULL);
	new_node->content = content;
	new_node->next = NULL;
	return (new_node);
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

t_list	*free_until_newline(t_list *buffer_list)
{
	t_list	*temp;
	char	*newline_pos;

	if (!buffer_list)
		return (NULL);
	while (buffer_list)
	{
		newline_pos = ft_strchr(buffer_list->content, '\n');
		if (newline_pos && *(newline_pos + 1))
		{
			temp = (t_list *)malloc(sizeof(t_list));
			temp->content = ft_strdup(newline_pos + 1);
			if (!temp || !temp->content)
				return (free(temp), NULL);
			temp->next = buffer_list->next;
			return (free(buffer_list->content), free(buffer_list), temp);
		}
		temp = buffer_list->next;
		free(buffer_list->content);
		free(buffer_list);
		buffer_list = temp;
	}
	/* Return NULL when no remaining content after newline */
	return (NULL);
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

char	*get_line_from_buffer(t_list *buffer_list)
{
	char	*line;
	int		i;
	int		len;
	t_list	*current;
	char	*content;

	if (!buffer_list)
		return (NULL);
	len = 0;
	current = buffer_list;
	while (current)
	{
		content = (char *)current->content;
		i = 0;
		while (content[i] && content[i] != '\n')
			i++;
		len += i;
		if (content[i] == '\n')
		{
			len++;
			break ;
		}
		current = current->next;
	}
	line = (char *)malloc(sizeof(char) * (len + 1));
	if (!line)
		return (NULL);
	current = buffer_list;
	len = 0;
	while (current)
	{
		content = (char *)current->content;
		i = 0;
		while (content[i] && content[i] != '\n')
			line[len++] = content[i++];
		if (content[i] == '\n')
		{
			line[len++] = '\n';
			break ;
		}
		current = current->next;
	}
	line[len] = '\0';
	return (line);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	const char	*s;
	size_t		src_len;
	size_t		copy_len;

	s = src;
	src_len = ft_strlen(s);
	if (size != 0)
	{
		if (src_len >= size)
		{
			copy_len = size - 1;
		}
		else
		{
			copy_len = src_len;
		}
		ft_memcpy(dst, s, copy_len);
		dst[copy_len] = '\0';
	}
	return (src_len);
}

char	*ft_strjoin(char *s1, char *s2)
{
	size_t	len1;
	size_t	len2;
	char	*result;
	size_t	i;

	if (!s1 || !s2)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	result = (char *)malloc(len1 + len2 + 1);
	if (!result)
		return (NULL);
	i = 0;
	while (i < len1)
	{
		result[i] = s1[i];
		i++;
	}
	while (i < len1 + len2)
	{
		result[i] = s2[i - len1];
		i++;
	}
	result[i] = '\0';
	return (result);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
	{
		i++;
	}
	return (i);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char	*src_ptr;
	char	*dest_ptr;

	src_ptr = (char *)src;
	dest_ptr = (char *)dest;
	if (!dest && !src)
		return (NULL);
	while (n--)
	{
		*dest_ptr++ = *src_ptr++;
	}
	return (dest);
}

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

char	*ft_strdup(const char *s1)
{
	char	*duplicate;
	size_t	len;

	len = ft_strlen(s1) + 1;
	duplicate = (char *)malloc(len * sizeof(char));
	if (duplicate == NULL)
	{
		return (NULL);
	}
	ft_memcpy(duplicate, s1, len);
	return (duplicate);
}

int	main(void)
{
	int		fd;
	char	*line;

	// Open the file for reading
	fd = open("hello.txt", O_RDONLY);
	if (fd < 0)
	{
		perror("Error opening file");
		return (1);
	}
	// Read and print each line
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("%s", line); // Print the line
		free(line);         // Free the line after use
	}
	// Close the file descriptor
	close(fd);
	return (0);
}
