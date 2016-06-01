/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflores <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/10 17:06:22 by nflores           #+#    #+#             */
/*   Updated: 2016/05/18 16:30:16 by nflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/vm.h"

static int	init_arg(char **buf, char *arg)
{
	int fd;

	fd = open(arg, O_RDONLY);
	if (fd == -1)
		exit(write(2, "Open error\n", 11));
	*buf = (char *)malloc(sizeof(char) * 4096);
	if (!(*buf))
		exit(write(2, "Malloc error\n", 13));
	return (fd);
}

static int	read_arg(char **buf, int fd)
{
	int i;
	int rd;

	i = 0;
	while ((rd = read(fd, (*buf) + i, 1)))
	{
		if (rd == -1)
			exit(write(2, "Read error\n", 11));
		i += rd;
	}
	(*buf)[i] = '\0';
	return (i);
}

void		display_error(char *arg, int errnum)
{
	if (errnum == 1)
	{
		write(2, arg, ft_strlen(arg));
		exit(write(2, " is to small to be a champion\n", 30));
	}
	else if (errnum == 2)
	{
		write(2, arg, ft_strlen(arg));
		exit(write(2, " is too large\n", 15));
	}
	else if (errnum == 3)
	{
		write(2, arg, ft_strlen(arg));
		exit(write(2, " has an invalid header\n", 23));
	}
}

int			check_arg(char **buf, char *arg)
{
	int		i;
	int		fd;

	fd = init_arg(buf, arg);
	i = read_arg(buf, fd);
	if (i < PROG_NAME_LENGTH + COMMENT_LENGTH)
		display_error(arg, 1);
	if (((*buf)[PROG_NAME_LENGTH + sizeof(int) * 2] << 24 |
		(0x00ff0000 & ((*buf)[PROG_NAME_LENGTH + sizeof(int) * 2 + 1] << 16)) |
		(0x0000ff00 & ((*buf)[PROG_NAME_LENGTH + sizeof(int) * 2 + 2] << 8)) |
		(0x000000ff & (*buf)[PROG_NAME_LENGTH + sizeof(int) * 2 + 3])) >
		CHAMP_MAX_SIZE)
		display_error(arg, 2);
	if ((((*buf)[0] << 24) | (0x00ff0000 & ((*buf)[1] << 16)) |
		(0x0000ff00 & ((*buf)[2] << 8)) | (0x000000ff & (*buf)[3])) !=
		COREWAR_EXEC_MAGIC)
		display_error(arg, 3);
	return (i);
}
