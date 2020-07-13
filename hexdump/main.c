#include "./includes/ft_hexdump.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>


char        **ft_buffer(const char *str)
{
    // convert string to hex_based key string.

    char        **buf;
    int         i;


    if (strlen(str) > BUFSIZ)
        return (NULL);

    i = 0;
    buf = malloc(sizeof(char *) * (strlen(str)+1));
    if(!buf)
        return (NULL);
    while (*(str + i))
    {
        *(buf + i) = ft_itox(*(str + i));
        i++;
    }
    *(buf + i) = NULL;
    return (buf);
}

int main()
{
    char **res;
    int i;

    i = 0;
    res = ft_buffer("123456\0");
    while(*(res + i) != NULL)
    {
        printf("%d: %s, ",i,  *(res + i));
        free(*(res + i));
        i++;
    }
    printf("\n");
}
