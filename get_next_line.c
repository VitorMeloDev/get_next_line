/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfreitass <vfreitas@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/16 05:33:19 by vfreitass         #+#    #+#             */
/*   Updated: 2026/06/16 08:27:51 by vfreitass        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

char *subresto(char *str, int start, int size)
{
    char *resto;
    int size_r;
    int i = 0;
    start++;
    size_r = size - start;
    resto = malloc(sizeof(char) * (size_r + 1));
    while (i < size_r)
    {
        if (str[start + i] == '\n')
            break;
        resto[i] = str[start + i];
        i++;
    }
    resto[i] = '\0';
    return (resto);
}

char *checar(char *str, int size)
{
    int i = 0;

    while (str[i] != '\0')
    {
        if(str[i] == '\n')
            return (subresto(str, i, size));
        i++;
    }
    return (NULL);
}

char    *pegar_str(char *str)
{
    char *str_s;
    int size = 0;
    int i = 0;
    while (str[size] != '\0' && str[size] != '\n')
        size++;
    str_s = malloc(sizeof(char) * (size + 1));
    while (i < size)
    {
        str_s[i] = str[i];
        i++;
    }
    str_s[i] = '\0';
    return (str_s);
}

char    *get_next_line(int fd);

int main(void)
{
    int fd = open("Hello", O_RDONLY);
    char *str = get_next_line(fd);
    printf("%s", str);
}

char    *get_next_line(int fd)
{
    int size_buffer = 100;
    char    str[size_buffer];
    static char *resto = NULL;
    ssize_t n = 0;

    n = read(fd, str, size_buffer);
    str[n] = '\0';
    resto = checar(str, n);

    //write(1, str, size_buffer -1);
    close(fd);
    printf("%s", resto);
    return (pegar_str(str));
}