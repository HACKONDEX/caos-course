# Low-Level IO

### inf-08-0

```C
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
```

### lseek

- `off_t lseek(int fildes, off_t offset, int whence);`
  
- `fildes` - is the file descriptor

- `offset` - is the offset in bytes regarding `whence`

- `whence` - have only __3__ validate values 
   1. `SEEK_SET` - The offset is set to `offset` bytes from the beginning of the file
   2. `SEEK_CUR` - The offset is set as the current offset plus `offset` bytes
   3. `SEEK_END` - The offset is set as the file size plus `offset` bytes

#### lseek example 

```C
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
```

# files-io on Windows 

- We will need windows gcc compiler, and executor for widows code

- `sudo apt install gcc-mingw-w64` __-__ install compiler

- `sudo apt install wine64` __-__ install executor

```C
#include <windows.h>
#include <stdio.h>
#include <assert.h>
#include <inttypes.h>
// #include </usr/share/mingw-w64/include/winbase.h>

int main() {
    HANDLE fileHandle = CreateFileA(argv[1], GENERIC_READ, FILE_SHARE_READ, NULL,
        OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

    DWORD bytes_read;
    BOOL success;

    char buffer[256];

    success = ReadFile(fileHandle, buffer, 5,
                           &bytes_read, NULL);

    LARGE_INTEGER offset;
    offset.QuadPart = 11;
    success = SetFilePointerEx(fileHandle, offset, NULL, FILE_BEGIN);

    CloseHandle(fileHandle);
    return 0;
}
```

- Compile and run example

- `i686-w64-mingw64-gcc windows_example.c -o win.exe`
  
- `WINEDEBUG=-all wine winapi_example.exe file.txt`

