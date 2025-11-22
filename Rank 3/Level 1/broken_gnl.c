#include "get_next_line.h"
#include <stdlib.h>
#include <unistd.h>

size_t ft_strlen(char *s)
{
    size_t len = 0;
    if (!s) return 0;
    while (s[len]) len++;
    return len;
}

char *ft_strchr(char *s, int c)
{
    size_t i = 0;
    if (!s) return NULL;
    while (s[i])
    {
        if (s[i] == (char)c)
            return s + i;
        i++;
    }
    if (c == '\0')
        return s + i;
    return NULL;
}

void *ft_memmove(void *dest, const void *src, size_t n)
{
    size_t i;
    if (!dest || !src) return NULL;
    if (dest > src)
    {
        i = n;
        while (i > 0)
        {
            i--;
            ((char *)dest)[i] = ((char *)src)[i];
        }
    }
    else
    {
        for (i = 0; i < n; i++)
            ((char *)dest)[i] = ((char *)src)[i];
    }
    return dest;
}

void *ft_memcpy(void *dest, const void *src, size_t n)
{
    size_t i;
    for (i = 0; i < n; i++)
        ((char *)dest)[i] = ((char *)src)[i];
    return dest;
}

int str_append_mem(char **s1, char *s2, size_t size2)
{
    size_t size1 = ft_strlen(*s1);
    char *tmp = malloc(size1 + size2 + 1);
    if (!tmp) return 0;
    if (*s1) ft_memcpy(tmp, *s1, size1);
    ft_memcpy(tmp + size1, s2, size2);
    tmp[size1 + size2] = '\0';
    free(*s1);
    *s1 = tmp;
    return 1;
}

int str_append_str(char **s1, char *s2)
{
    return str_append_mem(s1, s2, ft_strlen(s2));
}

char *get_next_line(int fd)
{
    static char buffer[BUFFER_SIZE + 1] = "";
    char *line = NULL;
    char *newline;
    int read_bytes;

    while (1)
    {
        newline = ft_strchr(buffer, '\n');
        if (newline)
        {
            if (!str_append_mem(&line, buffer, newline - buffer + 1))
                return free(line), NULL;
            ft_memmove(buffer, newline + 1, ft_strlen(newline + 1) + 1);
            return line;
        }

        if (!str_append_str(&line, buffer))
            return NULL;

        read_bytes = read(fd, buffer, BUFFER_SIZE);
        if (read_bytes <= 0)
        {
            buffer[0] = '\0';
            if (line && *line) return line;
            free(line);
            return NULL;
        }
        buffer[read_bytes] = '\0';
    }
}
