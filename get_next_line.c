/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfreitass <vfreitas@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/21 13:20:56 by vfreitass         #+#    #+#             */
/*   Updated: 2026/06/21 13:20:56 by vfreitass        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <fcntl.h>
#include "get_next_line.h"

char	*get_next_line(int fd)
{
	int			buffer_size;
	static char	*line;
	char		*str;
	char		*to_re;
	int			n;

	buffer_size = 10;
	n = 1;
	str = malloc(sizeof(char) * (buffer_size + 1));
	while (!ft_strchr(str, '\n') && n != 0)
	{
		n = read(fd, str, buffer_size);
		str[n] = '\0';
		line = vm_strjoin(line, str);
	}
	to_re = line;
	line = get_rest(line);
	return (extract_line(to_re));
}

int	main(void)
{
	int		fd;
	char	*str;

	fd = open("Hello", O_RDONLY);
	if (fd < 0)
		return (1);
	str = get_next_line(fd);
	printf(" - 1: %s\n", str);
	free(str);
	str = get_next_line(fd);
	printf(" - 2: %s\n", str);
	free(str);
	str = get_next_line(fd);
	printf(" - 3: %s\n", str);
	free(str);
	str = get_next_line(fd);
	printf(" - 4: %s\n", str);
	free(str);
	close(fd);
	return (0);
}
