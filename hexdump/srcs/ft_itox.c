#include <string.h>

char    *ft_itox(int val)
{
    char    ret[3];
    char    key;

    if (val < 0 || val > 127)
        return (NULL);
    ret[0] = '0';
    ret[1] = '0';
    if (val)
    {
        key = val / 16;
        ret[0] = '0' + key;
        if (key > 9)
            ret[0] = 'a' + (key - 10);
        key = val % 16;
        ret[1] = '0' + key;
        if (key > 9)
            ret[1] = 'a' + (key - 10);
    }
    ret[2] = '\0';
    return (strdup(ret));
}
