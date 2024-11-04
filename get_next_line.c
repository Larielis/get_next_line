/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racamach <racamach@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 11:31:38 by racamach          #+#    #+#             */
/*   Updated: 2024/11/04 11:31:38 by racamach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char *get_next_line(int fd)
{
    static t_list *buffer_list = NULL;
    char          *buffer;
    int           bytes_read;

    if (fd < 0 || BUFFER_SIZE <= 0)
        return (NULL);
    buffer = (char *)malloc(BUFFER_SIZE + 1);
    if (!buffer)
        return (NULL);
    while (!newline(buffer_list))
    {
        bytes_read = read(fd, buffer, BUFFER_SIZE);
        if (bytes_read <= 0)
        {
            if (bytes_read == -1)
                free_until_newline(buffer_list);
            return (free(buffer), NULL);
        }
        buffer[bytes_read] = '\0';
        ft_lstcreate_and_add_back(&buffer_list, strdup(buffer));
        if (!buffer_list || !buffer_list->content)
            return (free_until_newline(buffer_list), free(buffer), NULL);
    }
    return (free(buffer), get_line_from_buffer(buffer_list));
}


t_list *create_node(char *content)
{
    t_list *new_node;

    new_node = (t_list *)malloc(sizeof(t_list));
    if (!new_node)
        return (NULL);
    new_node->content = content;
    new_node->next = NULL;
    return (new_node);
}

int newline(t_list *buffer_list)
{
    t_list *temp = buffer_list;
    while (temp)
    {
        if (strchr(temp->content, '\n'))
            return (1);
        temp = temp->next;
    }
    return (0);
}


t_list *free_until_newline(t_list *buffer_list)
{
    t_list *temp;
    t_list *remainder;
    char   *newline_pos;

    while (buffer_list)
    {
        newline_pos = ft_strchr(buffer_list->content, '\n');
        if (newline_pos)
        {
            remainder = buffer_list->next;
            free(buffer_list->content);
            free(buffer_list);
            return (remainder);
        }
        temp = buffer_list;
        buffer_list = buffer_list->next;
        free(temp->content);
        free(temp);
    }
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

char *get_line_from_buffer(t_list *buffer_list)
{
    t_list *temp = buffer_list;
    char   *line = NULL;
    char   *newline_pos;
    char   *partial_line;

    while (temp)
    {
        newline_pos = ft_strchr(temp->content, '\n');
        if (newline_pos)
        {
            size_t len = newline_pos - (char *)temp->content + 1;
            partial_line = (char *)malloc(len + 1);
            if (!partial_line)
                return (NULL);
            ft_strlcpy(partial_line, temp->content, len + 1);
            line = ft_strjoin(line, partial_line);
            free(partial_line);
            break;
        }
        line = ft_strjoin(line, temp->content);
        temp = temp->next;
    }
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

char	*ft_strjoin(char const *s1, char const *s2)
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

void ft_lstcreate_and_add_back(t_list **lst, char *content)
{
    t_list *new_node;
    t_list *last;

    new_node = (t_list *)malloc(sizeof(t_list));
    if (!new_node)
        return;
    new_node->content = content;
    new_node->next = NULL;

    if (*lst == NULL)
    {
        *lst = new_node;
    }
    else
    {
        last = *lst;
        while (last->next != NULL)
            last = last->next;
        last->next = new_node;
    }
}

int main(void)
{
    int     fd;
    char    *line;

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
        printf("%s", line);   // Print the line
        free(line);           // Free the line after use
    }

    // Close the file descriptor
    close(fd);
    return (0);
}
