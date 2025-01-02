#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <errno.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc != 5) {
        fprintf(stderr, "Usage: %s <device_path> <cmd> <data> <data2>\n", argv[0]);
        return -1;
    }

    const char *device_path = argv[1];
    int cmd = atoi(argv[2]);
    int data[2];
    data[0] = atoi(argv[3]);
    data[1] = atoi(argv[4]);

    int fd = open(device_path, O_RDWR);
    if (fd < 0) {
        perror("open");
        return -1;
    }

    if (ioctl(fd, cmd, &data) < 0) {
        fprintf(stderr, "ioctl failed: %s\n", strerror(errno));
        close(fd);
        return -1;
    }

    printf("Received data: %d %d\n", data[0], data[1]);

    close(fd);
    return 0;
}