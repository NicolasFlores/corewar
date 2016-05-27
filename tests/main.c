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
	int i = 4;
	char oct[4];
	int value = -1;
	while (i > 0)
    {
        if (i == 1)
            oct[i - 1] = 0x000000ff & value;
        else
            oct[i - 1] = (value >> ((i - 1) * 8)) | (0xff << ((i - 1) * 8));
        i--;
    }
	printf("%.2x %.2x %.2x %.2x\n", oct[0], oct[1], oct[2], oct[3]);
	return 0;
}
