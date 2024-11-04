/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racamach <racamach@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 13:19:10 by racamach          #+#    #+#             */
/*   Updated: 2024/11/04 13:19:10 by racamach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
#define GET_NEXT_LINE_H

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h> 

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 42
#endif

typedef struct s_list
{
    char            *content;
    struct s_list   *next;
}                   t_list;

char    *get_next_line(int fd);
t_list  *free_until_newline(t_list *buffer_list);
int     newline(t_list *buffer_list);
char	*ft_strchr(char *s, int c);
char 	*get_line_from_buffer(t_list *buffer_list);
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
size_t	ft_strlen(const char *s);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void ft_lstcreate_and_add_back(t_list **lst, char *content);

#endif
