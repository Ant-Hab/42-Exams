#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int argo(json *dst, FILE *stream);

static int parse_string(char **dst, FILE *stream)
{
	if (!expect(stream, '"')) return -1;
	
	int cap = 64, len = 0, c;
	char *s = malloc(cap);
	
	while ((c = getc(stream)) != EOF && c != '"')
	{
		if (c == '\\')
		{
			c = getc(stream);
			if (c != '\\' && c != '"') return (free(s), -1);
		}
		if (len + 1 >= cap)
			s = realloc(s, cap *= 2);
		s[len++] = c;
	}
	if (c == EOF) return (free(s), unexpected(stream), -1);
	s[len] = '\0';
	*dst = s;
	return 1;
}

int argo(json *dst, FILE *stream)
{
	int c = peek(stream);

	if (c == '"')
	{
		dst->type = STRING;
		return parse_string(&dst->string, stream);
	}
	else if (c == '{')
	{
		accept(stream, '{');
		dst->type = MAP;
		dst->map.size = 0;
		dst->map.data = NULL;
		
		if (accept(stream, '}')) return 1;
		while (1)
		{
			dst->map.data = realloc(dst->map.data, sizeof(pair) * (dst->map.size + 1));
			if (parse_string(&dst->map.data[dst->map.size].key, stream) == -1) return -1;
			if (!expect(stream, ':')) return -1;
			if (argo(&dst->map.data[dst->map.size].value, stream) == -1) return -1;
			dst->map.size++;
			
			if (accept(stream, '}')) break;
			if (!expect(stream, ',')) return -1;
		}
		return 1;
	}
	else if (isdigit(c) || c == '-')
	{
		dst->type = INTEGER;
		if (fscanf(stream, "%d", &dst->integer) != 1) return -1;
		return 1;
	}
	
	unexpected(stream);
	return -1;
}