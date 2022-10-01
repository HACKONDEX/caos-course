long long func(long long x, long long y) {
    if (x < y) {
        return y + 7;
    }
    if (x == y + 1) {
        return 21;
    }
    return x + y;
}