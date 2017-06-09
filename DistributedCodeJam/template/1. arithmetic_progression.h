// Arithmetic progression [0, 1, 2, 3, 4, 5, ...]

#include <cassert>

const long long ___n = 20LL;
const long long ___a0 = 0LL;
const long long ___d = 1LL;

long long GetN() {
    return ___n;
}

long long Get(long long i) {
    return ___a0 + i * ___d;
}
