#include <stdarg.h>
#include <stdio.h>
#include <ctype.h>

int match_space(FILE *f)
{
    int c;
    while ((c = fgetc(f)) != EOF && isspace(c))
        ;
    if (c != EOF)
        ungetc(c, f);
    return 0;
}

int match_char(FILE *f, char c)
{
    int r = fgetc(f);
    if (r == EOF)
        return -1;
    return (r == c) ? 1 : -1;
}

int scan_char(FILE *f, va_list ap)
{
    int c = fgetc(f);
    if (c == EOF)
        return -1;
    *va_arg(ap, char *) = (char)c;
    return 1;
}

int scan_int(FILE *f, va_list ap)
{
    int c, sign = 1, val = 0, digits = 0;

    match_space(f);
    c = fgetc(f);
    if (c == EOF)
        return -1;

    if (c == '-' || c == '+')
    {
        if (c == '-')
            sign = -1;
        c = fgetc(f);
    }

    while (isdigit(c))
    {
        val = val * 10 + (c - '0');
        digits++;
        c = fgetc(f);
    }
    if (c != EOF)
        ungetc(c, f);

    if (digits == 0)
        return -1;

    *va_arg(ap, int *) = val * sign;
    return 1;
}

int scan_string(FILE *f, va_list ap)
{
    int c;
    char *buf = va_arg(ap, char *);
    int i = 0;

    match_space(f);
    while ((c = fgetc(f)) != EOF && !isspace(c))
        buf[i++] = (char)c;
    buf[i] = '\0';
    if (c != EOF)
        ungetc(c, f);

    return (i > 0) ? 1 : -1;
}

int match_conv(FILE *f, const char **format, va_list ap)
{
    switch (**format)
    {
        case 'c': return scan_char(f, ap);
        case 'd': return scan_int(f, ap);
        case 's': return scan_string(f, ap);
        default: return -1;
    }
}

int ft_vfscanf(FILE *f, const char *format, va_list ap)
{
    int nconv = 0;
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
    return nconv;
}

int ft_scanf(const char *format, ...)
{
    va_list ap;
    int ret;
    va_start(ap, format);
    ret = ft_vfscanf(stdin, format, ap);
    va_end(ap);
    return ret;
}
