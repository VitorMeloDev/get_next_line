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

char	*get_str(int fd, char *rest)
{
	char		*str;
	ssize_t		n;

	str = malloc (sizeof(char) * (BUFFER_SIZE + 1));
	if (!str)
		return (rest);
	str[0] = '\0';
	n = 1;
	while (!ft_strchr(str, '\n') && n != 0)
	{
		n = read(fd, str, BUFFER_SIZE);
		if (n <= 0)
		{
			free(str);
			if (rest && rest[0] != '\0')
				return (rest);
			free(rest);
			return (NULL);
		}
		str[n] = '\0';
		rest = ft_strjoin(rest, str);
	}
	free(str);
	return (rest);
}

char	*extract_line(char *str)
{
	char	*line;
	int		i;

	if (!str)
		return (NULL);
	i = 0;
	line = malloc(sizeof(char) * (ft_strlen(str) + 2));
	if (!line)
		return (NULL);
	while (str[i] != '\0' && str[i] != '\n')
	{
		line[i] = str[i];
		i++;
	}
	if (str[i] == '\n')
	{
		line[i] = '\n';
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*get_rest(char *buf)
{
	int		i;
	int		j;
	char	*new_buf;

	i = 0;
	while (buf[i] != '\0' && buf[i] != '\n')
		i++;
	if (buf[i] == '\n')
		i++;
	if (buf[i] == '\0')
	{
		free(buf);
		return (NULL);
	}
	new_buf = malloc(sizeof(char) * (ft_strlen(&buf[i]) + 1));
	if (!new_buf)
		return (NULL);
	j = 0;
	while (buf[i] != '\0')
		new_buf[j++] = buf[i++];
	new_buf[j] = '\0';
	free(buf);
	return (new_buf);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*buf;

	if (fd < 0)
		return (NULL);
	buf = get_str(fd, buf);
	if (!buf)
		return (NULL);
	line = extract_line(buf);
	if (!line)
	{
		free(buf);
		buf = NULL;
		return (NULL);
	}
	buf = get_rest(buf);
	return (line);
}

/*int	main(void)
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
}*/