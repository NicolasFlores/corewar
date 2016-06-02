#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <fcntl.h>
#include "../libftprintf/ft_printf.h"
#include "../libftprintf/libft.h"

#define ABS(x) x > 0 ? x:-x

int main(int argc, char **argv)
{
/*	int ret = 0;
	char *buf = (char *)malloc(129);
	int fd;
	int i = 0;

	fd = open(argv[1], O_RDONLY);
	while ((ret = read(fd, buf, 300)))
	{
		buf[ret] = '\0';
		while (i < ret)
		{
			printf("%.2x ", buf[i]);
			if (i != 0 && i % 32 == 0)
				printf("\n");
			i++;
		}
		}
	free(buf);*/
	printf("int: %d short: %hd", 0xfffe, (short)0xfffe);
	return 0;
}
