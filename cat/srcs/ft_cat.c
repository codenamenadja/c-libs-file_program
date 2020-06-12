#include <stdio.h> // BUFSIZ, EXIT_SUCCESS, EXIT_FAILURE
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h> // open
#include <unistd.h> // write, read, close
#include <string.h> // char *strerror(int errnum);
#include <libgen.h> // char *basename(char *path);
#include <errno.h> // errno

size_t ft_shallow_copy(char *dest, const char *src, size_t cur)
{
    size_t i;

    i = 0;
    while (*src)
    {
        if (cur == BUFSIZ)
        {
            write(STDOUT_FILENO, dest, BUFSIZ);
            cur = 0;
            i = 0;
        }
        *(dest + cur++) = *src++;
        i++;
    }
    return (i);
}

void ft_perror(char *path)
{
    char buf[BUFSIZ];
    char *buf_pt;
    size_t cur;

    cur = 0;
    buf_pt = buf;
    cur += ft_shallow_copy(buf, "cat: ", cur);
    cur += ft_shallow_copy(buf, path, cur);
    cur += ft_shallow_copy(buf, ": ", cur);
    cur += ft_shallow_copy(buf, strerror(errno), cur);
    cur += ft_shallow_copy(buf, "\n", cur);
    write(STDOUT_FILENO, buf, cur);
}

int open_handler(char *path)
{
    int     fd;
    int     i;

    fd = open(path, O_RDONLY);
    return (fd);
}

int main(int argc, char *argv[])
{
    int         i;
    int         fd;
    ssize_t     read_bytes;
    char        buf[BUFSIZ];

    i = 1;
    while (i < argc)
    {
        fd = open_handler(argv[i]);
        if (fd == -1)
        {
            ft_perror(argv[i]);
            i++;
            continue;
        }
        while ((read_bytes = read(fd, buf, BUFSIZ)) != -1)
        {
            if (!read_bytes)
                break;
            ft_shallow_copy(buf, "\n", (size_t)(read_bytes));
            write(STDOUT_FILENO, buf, (read_bytes + 1));
        }
        if(read_bytes == -1)
            ft_perror(argv[i]);
        close(fd);
        i++;
    }
    return (EXIT_SUCCESS);
}
