#include <stdarg.h>
#include <stdio.h>
#include <ctype.h>

int ft_scanf(const char *fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    int ret = 0, c = fgetc(stdin);
    if (c == EOF) return EOF;
    ungetc(c, stdin);
    while (*fmt)
    {
        if (isspace(*fmt))
        {
            while (isspace(c = fgetc(stdin)));
            ungetc(c, stdin);
        }
        else if (*fmt == '%' && fmt[1])
        {
            fmt++;
            if (*fmt == 'c')
            {
                c = fgetc(stdin);
                if (c == EOF) break;
                *va_arg(ap, char *) = c;
                ret++;
            }
            else if (*fmt == 's')
            {
                while (isspace(c = fgetc(stdin)));
                if (c == EOF) break;
                char *s = va_arg(ap, char *);
                int i = 0;
                while (c != EOF && !isspace(c))
                {
                    s[i++] = c;
                    c = fgetc(stdin);
                }
                s[i] = 0;
                ungetc(c, stdin);
                ret++;
            }
            else if (*fmt == 'd')
            {
                while (isspace(c = fgetc(stdin)));
                int sgn = 1, ok = 0, first = c;
                long v = 0;
                if (c == '-' || c == '+')
                {
                    if (c == '-') sgn = -1;
                    c = fgetc(stdin);
                }
                while (isdigit(c))
                {
                    v = v * 10 + c - '0';
                    ok = 1;
                    c = fgetc(stdin);
                }
                ungetc(c, stdin);
                if (!ok)
                {
                    if (first == '-' || first == '+') ungetc(first, stdin);
                    break;
                }
                *va_arg(ap, int *) = v * sgn;
                ret++;
            }
        }
        else
        {
            c = fgetc(stdin);
            if (c != *fmt)
            {
                ungetc(c, stdin);
                break;
            }
        }
        fmt++;
    }
    va_end(ap);
    return ret;
}