#include "get_next_line.h"

char *ft_strchr(char *s, int c)
{
    size_t i = 0;
    if (!s)
        return NULL;
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

void *ft_memcpy(void *dest, const void *src, size_t n)
{
    size_t i;
    if (!dest || !src)
        return dest;
    i = 0;
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
    while (s[res])
        res++;
    return res;
}

int str_append_mem(char **s1, char *s2, size_t size2)
{
    size_t size1 = ft_strlen(*s1);
    char *tmp = malloc(size2 + size1 + 1);
    if (!tmp)
        return 0;
    if (*s1)
        ft_memcpy(tmp, *s1, size1);
    ft_memcpy(tmp + size1, s2, size2);
    tmp[size1 + size2] = '\0';
    free(*s1);
    *s1 = tmp;
    return 1;
}

void *ft_memmove(void *dest, const void *src, size_t n)
{
    size_t i;
    if (!dest || !src)
        return dest;
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
        i = 0;
        while (i < n)
        {
            ((char *)dest)[i] = ((char *)src)[i];
            i++;
        }
    }
    return dest;
}

char *get_next_line(int fd)
{
    static char b[BUFFER_SIZE + 1] = "";
    char *ret = NULL;
    char *tmp;
    int read_ret;

    if (fd < 0 || BUFFER_SIZE <= 0)
        return NULL;
    while (1)
    {
        tmp = ft_strchr(b, '\n');
        if (tmp)
        {
            if (!str_append_mem(&ret, b, (size_t)(tmp - b + 1)))
            {
                free(ret);
                return NULL;
            }
            ft_memmove(b, tmp + 1, ft_strlen(tmp + 1) + 1);
            return ret;
        }
        if (!str_append_mem(&ret, b, ft_strlen(b)))
        {
            free(ret);
            return NULL;
        }
        read_ret = read(fd, b, BUFFER_SIZE);
        if (read_ret <= 0)
        {
            b[0] = '\0';
            if (ret && *ret)
                return ret;
            free(ret);
            return NULL;
        }
        b[read_ret] = '\0';
    }
}
