#include <assert.h>
#include <inttypes.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    int32_t process_count = 1;
    pid_t current_pid = 0;
    int is_parent_process = 0;
    while (is_parent_process == 0) {
        current_pid = fork();
        if (current_pid == 0) {
            ++process_count;
            continue;
        }
        is_parent_process = 1;
    }
    if (current_pid >= 0) {
        int status;
        assert(waitpid(current_pid, &status, 0) != -1);
    } else {
        printf("%i", process_count);
    }
    return 0;
}
