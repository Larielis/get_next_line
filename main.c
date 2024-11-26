/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: racamach <racamach@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 23:59:04 by racamach          #+#    #+#             */
/*   Updated: 2024/11/26 19:24:12 by racamach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int	main(int argc, char **argv)
{
	int		fd;
	char	*lineFile1;
	
	if (argc != 2)
		return (printf("Invalid arguments\n"), EXIT_FAILURE);

	fd = open(argv[1], O_RDONLY);
	if (!fd)
	{
		return (-1);
	}
	
	while ((lineFile1 = (get_next_line(fd))) != NULL)
	{
		printf("%s", lineFile1);
		free(lineFile1);
	}
	
	close(fd);
	return (0);
}
