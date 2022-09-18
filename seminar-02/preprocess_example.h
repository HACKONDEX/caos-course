#define ERROR_CODE -1
#define SUCCESS_CODE 0

int convert_euros_to_rubles(int* amount) {
    if (*amount > 0) {
        *amount *= 60;
        return SUCCESS_CODE;
    }
    return ERROR_CODE;
}
