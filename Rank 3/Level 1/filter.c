#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

int main(int argc, char **argv)
{
    if (argc != 2 || !argv[1][0])
        return 1;

    char *pattern = argv[1];
    size_t pat_len = strlen(pattern);
    if (pat_len == 0)
        return 1;

    ssize_t bytes_read;
    size_t buf_size = 4096;
    char *buf = malloc(buf_size);
    if (!buf)
    {
        perror("Error: malloc failed");
        return 1;
    }

    while ((bytes_read = read(0, buf, buf_size)) > 0)
    {
        char *start = buf;
        char *found;
        while ((found = memmem(start, buf + bytes_read - start, pattern, pat_len)) != NULL)
        {
            if (found != start)
                if (write(1, start, found - start) == -1)
                {
                    perror("Error: write failed");
                    free(buf);
                    return 1;
                }
            // write '*' instead of pattern
            for (size_t i = 0; i < pat_len; i++)
                if (write(1, "*", 1) == -1)
                {
                    perror("Error: write failed");
                    free(buf);
                    return 1;
                }
            start = found + pat_len;
        }
        if (start < buf + bytes_read)
            if (write(1, start, buf + bytes_read - start) == -1)
            {
                perror("Error: write failed");
                free(buf);
                return 1;
            }
    }

    if (bytes_read < 0)
    {
        perror("Error: read failed");
        free(buf);
        return 1;
    }

    free(buf);
    return 0;
}
