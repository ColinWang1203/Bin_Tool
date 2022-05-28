
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>
#include <errno.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <linux/types.h>
#include <linux/input.h>
#include <linux/hidraw.h>

uint8_t *bin_data1;
int32_t bin_size1;
uint8_t *bin_data2;
int32_t bin_size2;
uint8_t *bin_data3;
int32_t bin_size3;

#define NVT_LOG_HEX(data, len) {              \
			for (int i = 0; i < len; i++) {   \
				printf("%02X", *(data + i));  \
				if ((i + 1) % 16 == 0)         \
					printf("\n");             \
				else                          \
					printf(" ");              \
			}                                 \
			printf("\n");                     \
		}

int get_binary(char *path1,char *path2)
{
	int fd;
	fd = open(path1, O_RDONLY);
	if(fd < 0)
		return -EINVAL;
	bin_size1 = lseek(fd, 0, SEEK_END);
	bin_data1 = malloc(bin_size1);
	lseek(fd, 0, SEEK_SET);
	if(bin_size1 != read(fd, bin_data1, bin_size1))
		return -EINVAL;
	close(fd);
	fd = open(path2, O_RDONLY);
	if(fd < 0)
		return -EINVAL;
	bin_size2 = lseek(fd, 0, SEEK_END);
	bin_data2 = malloc(bin_size2);
	lseek(fd, 0, SEEK_SET);
	if(bin_size2 != read(fd, bin_data2, bin_size2))
		return -EINVAL;
	close(fd);
	bin_size3 = bin_size1 + bin_size2;
	bin_data3 = malloc(bin_size3);
	memcpy(bin_data3, bin_data1, bin_size1);
	memcpy(bin_data3 + bin_size1, bin_data2, bin_size2);
	return 0;
}

int32_t main(int32_t argc, char *argv[])
{
	FILE *pf = 0;
	if (argc == 1) {
		printf("./Convert_bin_to_txt xxx.bin\n");
		goto end;
	}
	get_binary(argv[1], argv[2]);
	pf = fopen("output.bin", "wb+");
	fwrite(bin_data3, bin_size3, 1, pf);
	NVT_LOG_HEX(bin_data3, bin_size3);
end:
	return 0;
}

