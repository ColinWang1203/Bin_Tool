
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

uint8_t *bin_data;
int32_t bin_size;

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

int get_binary(char *path)
{
	int fd;
	fd = open(path, O_RDONLY);
	if(fd < 0)
		return -EINVAL;
	bin_size = lseek(fd, 0, SEEK_END);
	bin_data = malloc(bin_size);
	lseek(fd, 0, SEEK_SET);
	if(bin_size != read(fd, bin_data, bin_size))
		return -EINVAL;
	//WIP add check "NVT" back if fw has trailing bytes
	close(fd);
	return 0;
}

int32_t main(int32_t argc, char *argv[])
{
	if (argc == 1) {
		printf("./Convert_bin_to_txt xxx.bin\n");
		goto end;
	}
	get_binary(argv[1]);
	NVT_LOG_HEX(bin_data, bin_size);
end:
	return 0;
}

