#include <inttypes.h>
#include <inttypes.h>
#include <malloc.h>
#include <stdio.h>
#include <string.h>


int main() {
    char* str = calloc(50, sizeof(char));
    scanf("%s", str);

    uint32_t len = 0;
    for (uint32_t i = 0; str[i] != '\0' ; ++i) {
        ++len;
    }

    char* append_str = "Appended";
    uint32_t append_len = strlen(append_str);
    for (uint32_t i = len; i < len + append_len; ++i) {
        str[i] = append_str[i - len];
    }

    printf("%s", str);
    
    free(str);
    return 0;
}
