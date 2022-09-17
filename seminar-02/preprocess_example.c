#include "preprocess_example.h"

#define OPTION_1 1

// Some magic counting
int count() {
    int amount = 0;
    
    #ifdef OPTION_1
        amount = 33;
    #else
        amount = 77;
    #endif

    if (convert_euros_to_rubles(&amount) == 0) {
        return amount;
    }
    return ERROR_CODE;
}
