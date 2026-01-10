#include "get_next_line.h"
#include <stdlib.h>
#include <unistd.h>

char *ft_strchr(char *s, int c)
{
    int i = 0;
    if (!s)
        return NULL;
    while (s[i])
    {
        if (s[i] == (char)c)
            return s + i;
        i++;
    }
    if ((char)c == '\0')
        return s + i;
    return NULL;
}

void *ft_memcpy(void *dest, const void *src, size_t n)
{
    size_t i = 0;
    if (!dest || !src)
        return dest;
    while (i < n)
    {
        ((char *)dest)[i] = ((char *)src)[i];
        i++;
    }
    return dest;
}

size_t ft_strlen(char *s)
{
    size_t res = 0;
    if (!s)
        return 0;
    while (*s)
    {
        s++;
        res++;
    }
    return res;
}

int str_append_mem(char **s1, char *s2, size_t size2)
{
    size_t size1 = ft_strlen(*s1);
    char *tmp = malloc(size1 + size2 + 1);
    if (!tmp)
        return 0;
    ft_memcpy(tmp, *s1, size1);
    ft_memcpy(tmp + size1, s2, size2);
    tmp[size1 + size2] = '\0';
    if (*s1)
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
    static char b[BUFFER_SIZE + 1] = "";
    char *ret = NULL;
    char *tmp;
    int read_ret;
    int i;

    while (!(tmp = ft_strchr(b, '\n')))
    {
        if (*b && !str_append_str(&ret, b))
        {
            if (ret)
                free(ret);
            return NULL;
        }

        read_ret = read(fd, b, BUFFER_SIZE);
        if (read_ret <= 0)
        {
            if (read_ret == -1)
            {
                if (ret)
                    free(ret);
                return NULL;
            }
            if (ret && *ret)
            {
                b[0] = '\0';
                return ret;
            }
            if (ret)
                free(ret);
            return NULL;
        }
        b[read_ret] = '\0';
    }

    if (!str_append_mem(&ret, b, tmp - b + 1))
    {
        if (ret)
            free(ret);
        return NULL;
    }

    tmp++;
    i = 0;
    while (*tmp)
        b[i++] = *tmp++;
    b[i] = '\0';

    return ret;
}
