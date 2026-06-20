#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 3
#endif

size_t	ft_strlen(const char *s)
{
	size_t	i = 0;
	if (!s) return (0);
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*ft_strchr(const char *s, int c)
{
	size_t	i = 0;
	if (!s) return (NULL);
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
			return ((char *)&s[i]);
		i++;
	}
	if ((char)c == '\0')
		return ((char *)&s[i]);
	return (NULL);
}

char	*ft_strjoin(char *s1, char *s2)
{
	size_t	i, j;
	char	*str;

	str = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!str) 
        return (NULL);
	i = 0;
	while (s1 && s1[i] != '\0')
	{
		str[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2 && s2[j] != '\0')
	{
		str[i + j] = s2[j];
		j++;
	}
	str[i + j] = '\0';
	free(s1);
	return (str);
}

char	*get_line(char *s)
{
	char	*sub;
	size_t	i = 0;

	if (!s || s[0] == '\0') return (NULL);
	while (s[i] != '\0' && s[i] != '\n')
		i++;
	if (s[i] == '\n') i++;
	sub = malloc(sizeof(char) * (i + 1));
	if (!sub) return (NULL);
	i = 0;
	while (s[i] != '\0' && s[i] != '\n')
	{
		sub[i] = s[i];
		i++;
	}
	if (s[i] == '\n')
	{
		sub[i] = '\n';
		i++;
	}
	sub[i] = '\0';
	return (sub);
}

char	*get_rest(char *s)
{
	char	*rest;
	size_t	i = 0;
	size_t	j = 0;

	while (s[i] != '\0' && s[i] != '\n')
		i++;
	if (s[i] == '\0')
	{
		free(s);
		return (NULL);
	}
	rest = malloc(sizeof(char) * (ft_strlen(s) - i));
	if (!rest) return (NULL);
	i++;
	while (s[i] != '\0')
		rest[j++] = s[i++];
	rest[j] = '\0';
	free(s);
	return (rest);
}

char	*get_next_line(int fd)
{
	char		*buf;
	static char	*backup;
	char		*line;
	int			n;

	if (fd < 0 || BUFFER_SIZE <= 0) return (NULL);
	buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf) return (NULL);
	n = 1;
	while (!ft_strchr(backup, '\n') && n != 0)
	{
		n = read(fd, buf, BUFFER_SIZE);
		if (n == -1)
		{
			free(buf);
			return (NULL);
		}
		buf[n] = '\0';
		backup = ft_strjoin(backup, buf);
	}
	free(buf);
	line = get_line(backup);
	backup = get_rest(backup);
	return (line);
}

int main(void)
{
    int fd = open("Hello", O_RDONLY);
    if (fd < 0) return 1;

    char *str;
    int i = 1;
    while ((str = get_next_line(fd)) != NULL)
    {
        printf("Linha %d: %s", i++, str);
        free(str);
    }
    close(fd);
    return 0;
}
