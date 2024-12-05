/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racamach <racamach@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 01:54:10 by racamach          #+#    #+#             */
/*   Updated: 2024/11/30 15:52:51 by racamach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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

size_t	calculate_line_length(t_list *buffer_list)
{
	t_list	*current;
	size_t	len;
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
	return (len);
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
