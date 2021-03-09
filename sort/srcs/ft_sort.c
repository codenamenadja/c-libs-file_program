/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junehan <junehan.dev@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 19:29:24 by junehan           #+#    #+#             */
/*   Updated: 2021/03/09 17:15:20 by junehan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	<sys/types.h>
#include	<sys/stat.h>
#include	<fcntl.h>
#include	<unistd.h>
#include	<stdlib.h>
#include 	<string.h>
#define		MAXLINES 4096

char	*lineptr[MAXLINES];

char	*copylines(char *buf, char *prev ,int *curline)
{
	char	*buf_pt;
	char 	*new;
	int		i;

	buf_pt = buf;
	i = 0;
	while (*(buf_pt + i)) {
		if (*(buf_pt + i) == '\n') {
			new = strndup(buf_pt, i);
			/* Critical error */
			if (!new)
				return (NULL);
			
			*(lineptr + *curline) = new;
			(*curline) += 1;
			buf_pt += i;
			i = 0;
		}
		i++;
	}
	if (*(buf_pt + i - 1) != '\n') {
		prev = strdup(buf_pt);
		if (!prev)
			return (NULL);
		return (prev);
	}
	return (buf_pt);
}

int	readlines(int fd, size_t read_size, int *curline)
{
	size_t	rb;
	char	tmp[read_size + 1];
	char	*tmp_pt;
	size_t	prev_len;
	char	*prev;

	rb = read_size;
	prev = NULL;
	while (rb == read_size && *curline < MAXLINES)
	{
		rb = read(fd, tmp, read_size);
		tmp[rb] = '\0';
		tmp_pt = tmp;
		if (prev) {
			while (*tmp_pt != '\n' && *tmp_pt)
				tmp_pt++;
			/* too long per line, free all and fin */
			if (*tmp_pt == '\0')
				return (-1);
			prev_len = strlen(prev);
			prev = (char *)realloc(prev, prev_len + (tmp_pt - tmp + 1));
			/* realloc error, free all and fin */
			if (!prev)
				return (-1);

			strncpy(prev + prev_len, tmp, tmp_pt - tmp + 1);
			lineptr[*curline] = prev;
			curline++;
		}

		prev = NULL;
		if (*tmp_pt != '\n' && *tmp_pt)
			if (!copylines(tmp_pt, prev, curline))
				return (-1);

	}
	return (*curline);
}

void	flush_lines(void)
{
	int i;
	i = 0;
	while (*(lineptr + i)) {
		write(STDOUT_FILENO, *(lineptr + i), strlen(*(lineptr + i)));
		//printf("%s", *(lineptr+i));
		free(*(lineptr+i));
		i++;
	}
	//printf("expected : %d , actual: %d\n", lineno, i);
}

int		main(int argc, const char *argv[])
{
	int fd;
	int	lineno;
	int	ret;

	if (argc != 2 && argc != 3)
		return (EXIT_FAILURE);

	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		return (EXIT_FAILURE);

	lineno = 0;
	ret = readlines(fd, 1024, &lineno);
	close(fd);
	flush_lines();
	if (ret != lineno)
		return (EXIT_FAILURE);

	return (EXIT_SUCCESS);
}

