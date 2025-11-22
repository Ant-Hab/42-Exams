#include <unistd.h>

int is_balanced(char *s)
{
    int i = 0;
    int count = 0;
    while (s[i])
    {
        if (s[i] == '(')
            count++;
        else if (s[i] == ')')
        {
            count--;
            if (count < 0)
                return 0;
        }
        i++;
    }
    if (count == 0)
        return 1;
    return 0;
}

void write_str(char *s)
{
    int i = 0;
    while (s[i])
        i++;
    write(1, s, i);
    write(1, "\n", 1);
}

void remove_invalid(char *s, int start, int last_remove, char par[2])
{
    int i;
    int count = 0;
    i = start;
    while (s[i])
    {
        if (s[i] == par[0])
            count++;
        if (s[i] == par[1])
            count--;
        if (count >= 0)
        {
            i++;
            continue;
        }
        int j = last_remove;
        while (j <= i)
        {
            if (s[j] == par[1] && (j == last_remove || s[j - 1] != par[1]))
            {
                s[j] = ' ';
                remove_invalid(s, i + 1, j, par);
                s[j] = par[1];
            }
            j++;
        }
        return;
    }
   
    char rev[1024];
    int len = 0;
    while (s[len])
        len++;
    int k = 0;
    while (len - 1 - k >= 0)
    {
        rev[k] = s[len - 1 - k];
        k++;
    }
    rev[k] = 0;
    if (par[0] == '(')
    {
        char new_par[2];
        new_par[0] = ')';
        new_par[1] = '(';
        remove_invalid(rev, 0, 0, new_par);
    }
    else
    {
        write_str(rev);
    }
}

int main(int argc, char **argv)
{
    if (argc != 2)
        return 1;
    remove_invalid(argv[1], 0, 0, (char[2]){'(', ')'});
    return 0;
}
