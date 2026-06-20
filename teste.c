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

int main(void)
{
    int fd = open("Hello", O_RDONLY);
    if (fd < 0) return 1;

    char *str = get_next_line(fd);
    printf(" - 1: %s\n", str);
    free(str);

    /*str = get_next_line(fd);
    printf(" - 2: %s\n", str);
    free(str);
    
    str = get_next_line(fd);
    printf(" - 3: %s\n", str);
    free(str);

    str = get_next_line(fd);
    printf(" - 4: %s\n", str);
    free(str);*/

    close(fd);
    return 0;
}