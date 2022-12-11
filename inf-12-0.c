#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

const int MaxSize = 1024;
const char* file_name = "tmptmptmp.py";

int main()
{
    char buffer[MaxSize];
    fgets(buffer, MaxSize, stdin);

    int fd = open(file_name, O_RDWR | O_CREAT, 0777);
    const char prefix[] = "print(";
    write(fd, prefix, sizeof(prefix) - 1);

    char* end = memchr(buffer, '\n', MaxSize);
    if (end != NULL) {
        end[0] = '\0';
    }

    write(fd, buffer, strlen(buffer));
    const char suffix[] = ")\n\n";
    write(fd, suffix, sizeof(suffix) - 1);

    close(fd);
    execlp("python3", "python3", file_name, NULL);
    return 0; // Unreachable
}
