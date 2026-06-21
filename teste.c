/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   teste.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfreitass <vfreitas@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/17 09:36:37 by vfreitass         #+#    #+#             */
/*   Updated: 2026/06/17 09:36:37 by vfreitass        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>

char	*ft_strchr(const char *s, int c)
{
	size_t			i;
	unsigned char	v;

	v = (unsigned char)c;
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == v)
			return ((char *)&s[i]);
		i++;
	}
	if (v == '\0')
		return ((char *)&s[i]);
	return (NULL);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*vm_strjoin(char *s1, char *s2)
{
	char	*str;
	int		i;
	int		j;
	int		size;

	if (!s2)
		return (NULL);
	size = 0;
	if (s1)
		size += ft_strlen(s1);
	size += ft_strlen(s2);
	str = malloc(size + 1);
	if (!str)
		return (NULL);
	i = 0;
	j = 0;
	if (s1)
	{
		while (s1[i])
		{
			str[i] = s1[i];
			i++;
		}
	}
	while (s2[j])
		str[i++] = s2[j++];
	str[i] = '\0';
	return (str);
}

char *get_rest(char *buf)
{
	char *str;
	int i = 0;
	while (buf[i] != '\0' && buf[i] != '\n')
		i++;
	if (buf[i] == '\0')
		return (NULL);
	if (buf[i] == '\n')
		i++;
	return (&buf[i]);
}

char	*extract_line(char *str)
{
	char *line;
	int i = 0;

	line = malloc (sizeof(char) * (ft_strlen(str) + 1));
	while (str[i] != '\0' && str[i] != '\n')
	{
		line[i] = str[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char *get_next_line(int fd)
{
	int buffer_size = 10;
	char static *line;
	char *str;
	char *to_re;
	int n = 1;

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

int main(void)
{
    int fd = open("Hello", O_RDONLY);
    if (fd < 0) return 1;

    char *str = get_next_line(fd);
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
    return 0;
}