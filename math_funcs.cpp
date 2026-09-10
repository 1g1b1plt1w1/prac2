#include "math_funcs.h"
#include <iostream>
#include <cmath>
#include <random>
#include <vector>

using namespace std;

bool isPrime(int n) {
    if (n <= 1) return false;
    for (int i = 2; i * i <= n; ++i) {
        if (n % i == 0) return false;
    }
    return true;
}

int gcd(int a, int b) {
    a = std::abs(a);
    b = std::abs(b);
    while (b != 0) {
        int t = b;
        b = a % b;
        a = t;
    }
    return a;
}

int powMod(int a, int x, int p) {
    if (p <= 0) return -1;
    a = (a % p + p) % p;
    int res = 1;
    while (x > 0) {
        if (x & 1) {
            res = (1LL * res * a) % p;
        }
        a = (1LL * a * a) % p;
        x >>= 1;
    }
    return res;
}

int ferma(int a, int x, int p) {
    if (!isPrime(p)) {
        return -1;
    }
    if (gcd(a, p) != 1) {
        return -1;
    }
    if (x < 0) {
        return -1;
    }
    int reduced_x = x % (p - 1);
    return powMod(a, reduced_x, p);
}

int extendedGCD(int a, int b, int &x, int &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    int x1, y1;
    int d = extendedGCD(b, a % b, x1, y1);
    x = y1;
    y = x1 - (a / b) * y1;
    return d;
}

int modInverse(int c, int m) {
    int x, y;
    int g = extendedGCD(c, m, x, y);
    if (g != 1) return -1;
    return (x % m + m) % m;
}

int getRandomPrime() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dist(1000, 9999);
    int p;
    do {
        p = dist(gen);
    } while (!isPrime(p));
    return p;
}

int findPrimitiveRoot(int p) {
    if (p == 2) return 1;
    int phi = p - 1;
    int n = phi;
    vector<int> factors;
    for (int i = 2; i * i <= n; ++i) {
        if (n % i == 0) {
            factors.push_back(i);
            while (n % i == 0) {
                n /= i;
            }
        }
    }
    if (n > 1) {
        factors.push_back(n);
    }

    for (int res = 2; res <= p; ++res) {
        bool ok = true;
        for (int factor : factors) {
            if (powMod(res, phi / factor, p) == 1) {
                ok = false;
                break;
            }
        }
        if (ok) return res;
    }
    return -1;
}

vector<unsigned char> encryptDecryptData(const vector<unsigned char>& data, int key) {
    mt19937 rng(static_cast<unsigned int>(key));
    vector<unsigned char> result(data.size());
    for (size_t i = 0; i < data.size(); ++i) {
        result[i] = data[i] ^ static_cast<unsigned char>(rng() & 0xFF);
    }
    return result;
}
