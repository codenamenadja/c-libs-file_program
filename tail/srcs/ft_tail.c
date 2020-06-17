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
    char *err_str;

    if (errno)
    {
        i = 0;
        err_str = strerror(errno);
        while (*(err_str + i))
            i++;
        write(STDOUT_FILENO, err_str, i);
    }   else
        write(STDOUT_FILENO, "unknown error!\n", 15);
    return (EXIT_FAILURE);
}

int open_handler(char *filename)
{
    int fd;

    fd = open(filename, O_RDONLY);
    return (fd);
}

size_t ft_strlen(char *str)
{
    size_t bytes;

    bytes = 0;

    while (*(str + bytes))
        bytes++;
    return bytes;
}

char *ft_strdup(char *str)
{
    char *res; 
    size_t len;
    size_t i;

    len = ft_strlen(str);
    res = malloc(sizeof(char) * len + 1);
    if(!res)
        return NULL;
    i = 0;
    while (i < len)
    {
        *(res+i) = *(str+i);
        i++;
    }
    *(res + i) = 0;
    return (res);
}

void ft_bzero(char *str)
{
    while (*str)
        *str++ = 0;
}

void ft_fflush(char **linebuf)
{
    while ((*linebuf) != NULL)
        free(*linebuf++);
}
int ft_tail(int fd, unsigned int option)
{
    char strbuf[BUFSIZ];
    char *linebuf[BUFSIZ];
    ssize_t read_bytes;
    char *buf_pt;
    int lines;

    if (option)
    {
        lines = 0;
        while ((read_bytes = read(fd, strbuf, BUFSIZ)) == BUFSIZ)
        {
            if (read_bytes == -1)
                return ft_perror();
            *(linebuf + lines) = ft_strdup(strbuf);
            lines++;
        }
        *(linebuf + lines) = ft_strdup(strbuf);
        while ((read_bytes = (ft_strlen(*(linebuf+lines)))) < option && lines != 0)
        {
            option -= read_bytes;
            lines--;
        }
        read_bytes = (read_bytes <= option) ? 0: read_bytes - option;
        write(STDOUT_FILENO, ((*(linebuf+lines)) + read_bytes), ft_strlen((*(linebuf+lines))+read_bytes)); 
        lines++;
        while ((*(linebuf + lines)) != NULL)
        {
            write(STDOUT_FILENO, *(linebuf+lines), ft_strlen(*(linebuf+lines)));
            lines++;
        }
    } else {
        lines = 0;
        buf_pt = strbuf;
        while(read_bytes = read(fd, buf_pt, 1))
        {
            if(read_bytes == -1)
            {
                ft_fflush(linebuf);
                return ft_perror();
            }
            if(*buf_pt++ == '\n')
            {
                *(linebuf+lines) = ft_strdup(strbuf);
                lines++;
                ft_bzero(strbuf);
                buf_pt = strbuf;
            }
        }
        *(linebuf+lines) = ft_strdup(strbuf);
        if (lines > 10)
            lines -= 10;
        else
            lines = 0;
        while (*(linebuf+lines))
        {
            write(STDOUT_FILENO, *(linebuf+lines), ft_strlen(*(linebuf+lines)));
            lines++;
        }
    }
    ft_fflush(linebuf);
    return EXIT_SUCCESS;
}

unsigned int option_handler(char *option)
{
    unsigned int    res;
    char            key;

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
                {
                    res = (res == 0) ? 1 : res;
                    return (res);
                }
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
    unsigned int option;

    if (argc == 2)
        if ((fd = open_handler(argv[1])) != -1)
        {
            ft_tail(fd, 0);
            close(fd);
            return (EXIT_SUCCESS);
        }
    if (argc == 3) {
        if((fd = open_handler(argv[1])) != -1 && (option = option_handler(argv[2])) != 0)
        {
            ft_tail(fd, option);
            close(fd);
            return (EXIT_SUCCESS);
        }
        else if((fd = open_handler(argv[2])) != -1 && (option = option_handler(argv[1])) != 0)
        {
            ft_tail(fd, option);
            close(fd);
            return (EXIT_SUCCESS);
        }
    }
    if (fd == -1)
        return ft_perror();
    write(STDOUT_FILENO, "error!\n", 7);
    close(fd);
    return EXIT_FAILURE; 
}

