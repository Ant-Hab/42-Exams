#include "get_next_line.h"

static char *add_to_line(char *line, char *buf, int n)
{
    char    *new_line;
    int     len = 0;
    int     i = 0;
    int     j = 0;

    while (line && line[len])
        len++;
    new_line = malloc(len + n + 1);
    if (!new_line)
    {
        free(line);
        return (NULL);
    }
    while (i < len)
    {
        new_line[i] = line[i];
        i++;
    }
    while (j < n)
        new_line[i++] = buf[j++];
    new_line[i] = '\0';
    free(line);
    return (new_line);
}

char *get_next_line(int fd)
{
    static char buf[BUFFER_SIZE + 1];
    char        *line = NULL;
    int         i, j, r;

    if (fd < 0 || BUFFER_SIZE <= 0)
        return (NULL);
    while (1)
    {
        if (!buf[0])
        {
            r = read(fd, buf, BUFFER_SIZE);
            if (r < 0)
                return (free(line), NULL);
            if (r == 0)
                return (line);
            buf[r] = '\0';
        }
        i = 0;
        while (buf[i] && buf[i] != '\n')
            i++;
        int has_nl = (buf[i] == '\n');
        line = add_to_line(line, buf, i + has_nl);
        if (!line)
            return (NULL);
        if (has_nl)
        {
            j = 0;
            i++;
            while (buf[i])
                buf[j++] = buf[i++];
            buf[j] = '\0';
            return (line);
        }
        buf[0] = '\0';
    }
}