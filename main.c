/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racamach <racamach@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 23:59:04 by racamach          #+#    #+#             */
/*   Updated: 2024/11/10 17:39:48 by racamach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int	main(void)
{
	int		fd;
	char	*line;

	fd = open("1char.txt", O_RDONLY);
	if (fd < 0)
	{
		perror("Error opening file");
		return (1);
	}

	line = get_next_line(fd);
	if (line)
	{
		printf("Line 1: %s\n", line);
		free(line);
	}
	else
	{
		printf("Line 1: NULL\n");
	}

	line = get_next_line(fd);
	if (line)
	{
		printf("Line 2: %s\n", line);
		free(line);
	}
	else
	{
		printf("Line 2: NULL\n");
	}

	close(fd);
	return (0);
}
