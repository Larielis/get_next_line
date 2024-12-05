/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racamach <racamach@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 13:19:10 by racamach          #+#    #+#             */
/*   Updated: 2024/11/30 15:52:00 by racamach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

typedef struct s_list
{
	char			*content;
	struct s_list	*next;
}					t_list;

// Function prototypes
void				ft_lstclear(t_list **lst, void (*del)(void *));
int					ft_lstcreate_and_add_back(t_list **lst, char *content);
char				*get_line_from_buffer(t_list *buffer_list);
void				free_until_newline(t_list **buffer_list);
size_t				calculate_line_length(t_list *buffer_list);
int					read_to_buffer_list(int fd, t_list **buffer_list);
char				*get_next_line(int fd);
char				*ft_strdup(char *s1);
char				*ft_strchr(char *s, int c);
int					newline(t_list *buffer_list);

#endif