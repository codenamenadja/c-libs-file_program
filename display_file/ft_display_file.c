#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>

int open_handler(char *path)
{
    int     fd;

    fd = open(path, O_RDONLY);
    if(fd == -1)
        return (-1);
    return (fd);
}


int main(int argc, char *argv[])
{
    int i;
    int fd;
    ssize_t read_bytes;
    char buf[BUFSIZ];
    int res;

    i = 1;
    res = 0;
    if (argc == 1)
    {
        write(STDOUT_FILENO, "non filepath given to an argument\n", BUFSIZ);
        return (EXIT_FAILURE);
    }
    while(i < argc)
    {
        fd = open_handler(argv[i]);
        if (fd == -1 && i++)
            continue;
        while((read_bytes = read(fd, buf, BUFSIZ)) > 0)
            write(STDOUT_FILENO, buf, read_bytes);
        res++;
        close(fd);
        i++;
    }
    return (res);
}
