/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racamach <racamach@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 16:39:39 by racamach          #+#    #+#             */
/*   Updated: 2025/01/24 17:21:46 by racamach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h>

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

	len = get_line_length(buffer_list);
	line = (char *)malloc(sizeof(char) * (len + 1));
	if (!line)
		return (NULL);
	line[0] = '\0';
	current = buffer_list;
	while (current)
	{
		ft_strlcat(line, current->content, len + 1);
		if (ft_strchr(current->content, '\n'))
			break ;
		current = current->next;
	}
	return (line);
}

int	get_line_length(t_list *buffer_list)
{
	int		length;
	t_list	*current;
	int		i;

	length = 0;
	current = buffer_list;
	while (current)
	{
		i = 0;
		while (current->content[i] && current->content[i] != '\n')
			i++;
		length += i;
		if (current->content[i] == '\n')
		{
			length++;
			break ;
		}
		current = current->next;
	}
	return (length);
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
