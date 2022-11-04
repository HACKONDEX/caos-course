#include <unistd.h>

int main() {
    char output[] = "Hellow!";
    write(1, output, sizeof(output));
    return 0;
}