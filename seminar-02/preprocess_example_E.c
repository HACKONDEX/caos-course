# 0 "preprocess_example.c"
# 0 "<built-in>"
# 0 "<command-line>"
# 1 "/usr/include/stdc-predef.h" 1 3 4
# 0 "<command-line>" 2
# 1 "preprocess_example.c"
# 1 "preprocess_example.h" 1



int convert_euros_to_rubles(int* amount) {
    if (*amount > 0) {
        *amount *= 60;
        return 0;
    }
    return -1;
}
# 2 "preprocess_example.c" 2




int count() {
    int amount = 0;


        amount = 33;




    if (convert_euros_to_rubles(&amount) == 0) {
        return amount;
    }
    return -1;
}
