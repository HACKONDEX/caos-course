#include <inttypes.h>
#include <limits.h>
#include <malloc.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

void zero_terminate(char *str) {
    for (int i = 0;; ++i) {
        if (str[i] == '\n') {
            str[i] = '\0';
            break;
        }
    }
}

int main() {
    char *file_name = calloc(PATH_MAX, sizeof(char));
    int64_t size = 0;
    struct stat attrs;

    while (fgets(file_name, PATH_MAX, stdin) != NULL) {
        zero_terminate(file_name);

        if (lstat(file_name, &attrs) == 0) {
            if (S_ISREG(attrs.st_mode)) {
                size += attrs.st_size;
            }
        }
    }

    printf("%" PRId64, size);
    free(file_name);
    return 0;
}