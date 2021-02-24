/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_display_file.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junehan <junehan.dev@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 16:10:58 by junehan           #+#    #+#             */
/*   Updated: 2021/02/24 17:10:59 by junehan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	<unistd.h>
#include	<sys/types.h>
#include	<fcntl.h>

#define		BUFSIZ	1024
enum {EXIT_SUCCESS, EXIT_FAILURE};


int	open_handler(char *path);
ssize_t	read_handler(int fd, void *buf);

int main(int argc, char *argv[])
{
    ssize_t rb;
	int		fd;
    char	buf[BUFSIZ];
    int		reads;

    reads = 1;
	
    if (argc == 1) {
        write(STDOUT_FILENO, "File name missing.\n", 19);
        return (EXIT_FAILURE);
	}

    while (reads < argc) {
		fd = open_handler(argv[reads++]);

		if (fd > STDERR_FILENO) {
			do {
				rb = read_handler(fd, buf);
				write(STDOUT_FILENO, buf, rb);
			} while (rb == BUFSIZ);
			close(fd);
		} else {
			write(STDOUT_FILENO, "cannot read file.\n", 18);
		}

	}

	if (reads == 1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

ssize_t	read_handler(int fd, void *buf)
{
	return read(fd, buf, BUFSIZ);
}

int	open_handler(char *path)
{
    int	fd;

	if (!path)
		fd = 0;
	else if ((fd = open(path, O_RDONLY)) <= STDERR_FILENO) {
		close(fd);
		fd = -1;
	}

	return (fd);
}
