#include <stdarg.h>
#include <stdio.h>
#include <ctype.h>

int match_space(FILE *f)
{
    int c;
    while (isspace(c = fgetc(f)));
    return (ungetc(c, f), 1);
}

int match_char(FILE *f, char c)
{
    int k = fgetc(f);
    if (k == c)
        return (1);
    return (ungetc(k, f), 0);
}

int scan_char(FILE *f, va_list ap)
{
    int c = fgetc(f);
    if (c == EOF)
        return (0);
    *va_arg(ap, char *) = c;
    return (1);
}

int scan_int(FILE *f, va_list ap)
{
    long    res = 0;
    int     sgn = 1, c = fgetc(f), digits = 0;

    if (c == '-')
        sgn = -1;
    if (c == '-' || c == '+')
        c = fgetc(f);
    while (isdigit(c))
    {
        res = res * 10 + c - '0';
        c = fgetc(f);
        digits++;
    }
    ungetc(c, f);
    if (!digits)
        return (0);
    *va_arg(ap, int *) = (int)(res * sgn);
    return (1);
}

int scan_string(FILE *f, va_list ap)
{
    char    *s = va_arg(ap, char *);
    int     c = fgetc(f), i = 0;

    if (c == EOF)
        return (0);
    while (c != EOF && !isspace(c))
    {
        s[i++] = c;
        c = fgetc(f);
    }
    ungetc(c, f);
    s[i] = 0;
    return (1);
}

int match_conv(FILE *f, const char **format, va_list ap)
{
    switch (**format)
    {
        case 'c': return scan_char(f, ap);
        case 'd': match_space(f); return scan_int(f, ap);
        case 's': match_space(f); return scan_string(f, ap);
        default: return (-1);
    }
}

int ft_vfscanf(FILE *f, const char *format, va_list ap)
{
    int nconv = 0;
    int c = fgetc(f);

    if (c == EOF)
        return (EOF);
    ungetc(c, f);
    while (*format)
    {
        if (*format == '%')
        {
            format++;
            if (match_conv(f, &format, ap) != 1)
                break;
            nconv++;
        }
        else if (isspace(*format))
            match_space(f);
        else if (match_char(f, *format) != 1)
            break;
        format++;
    }
    return (nconv);
}

int ft_scanf(const char *format, ...)
{
    va_list ap;
    int     ret;

    va_start(ap, format);
    ret = ft_vfscanf(stdin, format, ap);
    va_end(ap);
    return (ret);
}