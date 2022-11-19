#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <unistd.h>


int main(int argc, char* argv[]) {
	struct stat attrs;
	const char* file_name = argv[1];

	int32_t res = stat(file_name, &attrs);
	if (res == -1) {
		perror("Stat syscall failed");
		return -1;
	}

	if ((attrs.st_mode & S_IFMT) == S_IFREG) {
		printf("File is regular\n");
	}
	if ((attrs.st_mode & S_IFMT) == S_IFDIR) {
		printf("File is direcotry\n");
	}
	if ((attrs.st_mode & S_IFMT) == S_IFLNK) {
		printf("File is symbolic link\n");
	}

	printf("Size: %ld\n", attrs.st_size);

	return 0;

}