/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racamach <racamach@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 19:15:58 by racamach          #+#    #+#             */
/*   Updated: 2024/11/19 19:16:26 by racamach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE__BONUS_H

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

typedef struct s_list
{
	char			*content;
	struct s_list	*next;
}					t_list;

void				free_until_newline(t_list **buffer_list);
char				*get_next_line(int fd);
t_list				*create_node(char *content);
int					newline(t_list *buffer_list);
int					ft_lstcreate_and_add_back(t_list **lst, char *content);
char				*get_line_from_buffer(t_list *buffer_list);
char				*ft_strchr(const char *s, int c);
size_t				ft_strlcat(char *dest, const char *src, size_t n);
int					get_line_length(t_list *buffer_list);
char				*ft_strdup(char *s1);
int					read_to_buffer_list(int fd, t_list **buffer_list);
#endif