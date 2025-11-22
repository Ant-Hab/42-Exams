#include <stdlib.h>

int *ft_range(int start, int end)
{
    int i = 0;
    int len;
    
    if (end > start)
        len = end - start + 1;
    else
        len = start - end + 1;
    
    int *range = malloc(sizeof(int) * len);
    if (!range)
        return (NULL);
    
    while (i < len)
    {
        if (start < end)
            range[i] = start + i;
        else
            range[i] = start - i;
        i++;
    }
    return (range);
}