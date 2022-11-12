#include <assert.h>
#include <ctype.h>
#include <fcntl.h>
#include <inttypes.h>
#include <stdbool.h>
#include <unistd.h>

typedef enum {
    kMaxSize = 256,
} constatn_t;

bool write_file(int fd, char* buffer, int32_t size) {
    int32_t start = 0;
    while(size > 0) {
        int32_t write_count = write(fd, buffer + start, size);
        if (write_count < 0) {
            return false;
        }
        start += write_count;
        size -= write_count;
    }
    return true;
}

bool check_capacity(int32_t buffer_len) {
    return buffer_len == kMaxSize;
}

int main(int argc, char *argv[]) {
    assert(argc == 4);

    int32_t ret = 0;
    const char *input_file_name = argv[1];

    int32_t input_fd = open(input_file_name, O_RDONLY);
    if (input_fd < 0) {
        goto no_input_file;
    }

    int32_t numbers_fd = open(argv[2], O_RDWR | O_CREAT, 0664);
    if (numbers_fd < 0) {
        goto numbers_file_error;
    }

    int32_t remains_fd = open(argv[3], O_RDWR | O_CREAT, 0664);
    if (remains_fd < 0) {
        goto remains_file_error;
    }

    bool is_open = true;
    char buffer[kMaxSize];
    char numbers[kMaxSize];
    char remains[kMaxSize];
    int32_t numbers_len = 0;
    int32_t remains_len = 0;

    while (is_open) {
        int32_t read_bytes = read(input_fd, buffer, kMaxSize);
        if (read_bytes == 0) {
            break;
        } else if (read_bytes < 0) {
            goto io_error;
        }
        numbers_len = 0;
        remains_len = 0;
        for (size_t i = 0; i < read_bytes; ++i) {
            if (check_capacity(numbers_len)) {
                if (!write_file(numbers_fd, numbers, numbers_len)) {
                    goto io_error;
                }   
            }
            if (check_capacity(remains_len)) {
                if (!write_file(remains_fd, remains, remains_len)) {
                    goto io_error;
                }
            }
            if (isdigit(buffer[i])) {
                numbers[numbers_len++] = buffer[i];
                continue;
            }
            remains[remains_len++] = buffer[i];
        }

        if (!write_file(numbers_fd, numbers, numbers_len)) {
            goto io_error;
        }   
       
        if (!write_file(remains_fd, remains, remains_len)) {
            goto io_error;
        }

    }
     



success:
    ret = 0;
    goto close_all_fds;

no_input_file:
    ret = 1;
    goto exit;

numbers_file_error:
    close(input_fd);
    ret = 2;
    goto exit;

remains_file_error:
    close(input_fd);
    close(numbers_fd);
    ret = 2;
    goto exit;

io_error:
    ret = 3;

close_all_fds:
    close(input_fd);
    close(numbers_fd);
    close(remains_fd);

exit:
    _exit(ret);
}