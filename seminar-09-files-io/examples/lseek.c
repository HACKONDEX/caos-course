#include <fcntl.h>
#include <inttypes.h>
#include <stdio.h>
#include <unistd.h>

const char* file_name = "lseek_test";

typedef enum {
    KLen = 256,
}
constants_t;

int main() {
    int file_fd = open(file_name, O_RDWR);
    if (file_fd < 0) {
       perror("Something wrong with file"); 
    }

    int32_t file_size = lseek(file_fd, 0, SEEK_END);
    printf("%d\n", file_size);

    char buffer[KLen];
    int32_t read_size = read(file_fd, buffer, KLen);
    printf("%d\n", read_size);
    lseek(file_fd, 0, SEEK_SET);

    read_size = read(file_fd, buffer, 5);
    printf("%d\n%.*s\n", read_size, 5, buffer);

    lseek(file_fd, 6, SEEK_CUR);
    read_size = read(file_fd, buffer, 5);
    printf("%d\n%.*s\n", read_size, 5, buffer);

    ///////////////

    lseek(file_fd, 0, SEEK_SET);
    const char str_1[] = "Hola!";
    int32_t write_bytes = write(file_fd, str_1, sizeof(str_1) - 1);
    printf("%d\n", write_bytes);

    lseek(file_fd, 6, SEEK_CUR);
    const char str_2[] = "Barcelona!";
    write(file_fd, str_2, sizeof(str_2) - 1);

    lseek(file_fd, 0, SEEK_SET);
    read_size = read(file_fd, buffer, KLen);
    printf("%d\n%.*s\n", read_size, read_size, buffer);

    return 0;
}