#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
	const char* file_name = argv[1];

	int32_t fd = open(file_name, O_RDWR);
    if (fd == -1) {
        fd = open(file_name, O_DIRECTORY);
        if (fd == -1) {
            perror("open syscall error\n");
            return -1;
        }
    }

    struct stat attrs;
    if (fstat(fd, &attrs) == -1) {
        perror("fstat syscall error\n");
    }

    if (S_ISREG(attrs.st_mode)) {
		printf("File is regular\n");
	}

    if (S_ISDIR(attrs.st_mode)) {
        printf("File is direcotry\n");
    }
    	
	if ((S_ISLNK(attrs.st_mode))) {
		printf("File is symbolic link\n");
	}

    if ((attrs.st_mode & S_IRUSR) == S_IRUSR) {
        printf("Is executable\n");
    }


    close(fd);
    return 0;
}