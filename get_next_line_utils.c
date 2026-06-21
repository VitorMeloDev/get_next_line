/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfreitass <vfreitas@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/21 13:23:26 by vfreitass         #+#    #+#             */
/*   Updated: 2026/06/21 13:23:26 by vfreitass        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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

char	*get_rest(char *buf)
{
	int		i;

	i = 0;
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
	char	*line;
	int		i;

	i = 0;
	line = malloc(sizeof(char) * (ft_strlen(str) + 1));
	while (str[i] != '\0' && str[i] != '\n')
	{
		line[i] = str[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}
