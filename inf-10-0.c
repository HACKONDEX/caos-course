#include <fcntl.h>
#include <inttypes.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>

void calculate_prefix_values(int64_t *prefix_value, const char *template, int64_t length) {
    for (size_t i = 0; i <= length; ++i) {
        prefix_value[i] = 0;
    }
    int64_t current_substring_length = 0;
    prefix_value[0] = -1;
    for (size_t i = 2; i <= length; ++i) {
        current_substring_length = prefix_value[i - 1];
        while (current_substring_length >= 0) {
            if (template[i - 1] == template[current_substring_length]) {
                prefix_value[i] = current_substring_length + 1;
                break;
            }
            current_substring_length = prefix_value[current_substring_length];
        }
    }
}

/// CMP - substr search algorithm
void print_all_entry_positions(char *template, char *text, int64_t text_length) {
    int64_t template_length = strlen(template);
    void *mapped = mmap(NULL, (template_length + 1) * sizeof(int64_t),
                        PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    int64_t *prefix_value = (int64_t *) (mapped);
    calculate_prefix_values(prefix_value, template, template_length);
    int64_t previous_prefix_length = 0;
    int64_t current_prefix_length = 0;
    int suffix_found = 0;
    for (size_t i = 0; i < text_length; ++i) {
        previous_prefix_length = suffix_found ? current_prefix_length : 0;
        suffix_found = 0;
        while (previous_prefix_length >= 0) {
            if (text[i] == template[previous_prefix_length]) {
                suffix_found = 1;
                current_prefix_length = previous_prefix_length + 1;
                if (current_prefix_length == template_length) {
                    printf("%" PRIu64 "\n", i - template_length + 1);
                }
                break;
            }
            previous_prefix_length = prefix_value[previous_prefix_length];
        }
    }
    munmap(mapped, (template_length + 1) * sizeof(int64_t));
}

int main(int argc, char *argv[]) {
    int file_fd = open(argv[1], O_RDONLY);
    if (file_fd < 0) {
        return -1;
    }
    struct stat file_attributes;
    int success = fstat(file_fd, &file_attributes);
    if (success < 0) {
        return -1;
    }
    void *mapped = mmap(NULL, file_attributes.st_size, PROT_READ, MAP_PRIVATE, file_fd, 0);
    char *text = (char *) (mapped);

    print_all_entry_positions(argv[2], text, file_attributes.st_size);

    munmap(mapped, file_attributes.st_size);
    close(file_fd);
    return 0;
}