#include <stdio.h> // BUFSIZ, EXIT_SUCCESS, EXIT_FAILURE
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h> // open
#include <unistd.h> // write, read, close
#include <string.h> // char *strerror(int errnum);
#include <libgen.h> // char *basename(char *path);
#include <errno.h> // errno

int ft_perror()
{
    int i;
    char buf[64];
    char *err_str;
    if (errno)
    {
        i = -1;
        while(*err_str && ++i < 64)
            *(buf+i) = *(err_str+i);
        write(STDOUT_FILENO, buf, 64);
    }   else
        write(STDOUT_FILENO, "invalid args\n", 13);
    return (EXIT_FAILURE);
}

int open_handler(char *filename)
{
    int fd;

    fd = open(filename, O_RDONLY);
    return (fd);
}

int ft_tail(int fd, unsigned long long option)
{
    char buf[BUFSIZ];
    ssize_t read_bytes;
    printf("ft_tail fd : %d, option : %llu\n", fd, option);

    while ((read_bytes = read(fd, buf, BUFSIZ)) && read_bytes != -1)
        if (option < (unsigned long long)read_bytes)
        {
            write(STDOUT_FILENO, buf + option, read_bytes - (ssize_t)option);
            option = 0;
        }   else if (!option)
            write(STDOUT_FILENO, buf, read_bytes);
        else
            option -= (unsigned long long)read_bytes;
    if (read_bytes == -1)
        return ft_perror();
    return (EXIT_SUCCESS);
}

unsigned long long option_handler(char *option)
{
    unsigned long long res;
    unsigned long long key;

    if (*option++ == '-')
        if(*option++ == 'c')
        {
            res = 0;
            while ((key = (*option++ - '0')) >= 0 && key <= 9)
            {
                if (res)
                    res *= 10;
                res += key;    
                if (*option == 0)
                    return (res);
            }
        }
    return (0);
}

int main(int argc, char *argv[])
{
    // basically print last 10 line of file.: default
    // -c option only 
    // -c+num option prints all excepts num bytes from the head.

    int i;
    int fd;
    unsigned long long option;

    if (argc != 2 && argc != 3)
    {
        write(STDOUT_FILENO, "argc not valid\n", 15);
        return ft_perror();
    }
    if (argc == 2 && (fd = open_handler(argv[1])) != -1)
        return ft_tail(fd, 0); // last 10 lines
    if (fd != -1 && (option = option_handler(argv[2])))
        return ft_tail(fd, option); // first was filename with valid option
    if (fd == -1 && (fd = open_handler(argv[2]) != -1))
        if ((option = option_handler(argv[1])))
            return ft_tail(fd, option); // second was filename with valid option
    write(STDOUT_FILENO, "error!\n", 7);
    return EXIT_FAILURE; 
}

