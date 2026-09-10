#ifndef MATH_FUNCS_H
#define MATH_FUNCS_H

#include <vector>

bool isPrime(int n);
int gcd(int a, int b);
int powMod(int a, int x, int p);
int ferma(int a, int x, int p);
int extendedGCD(int a, int b, int &x, int &y);
int modInverse(int c, int m);
int getRandomPrime();
int findPrimitiveRoot(int p);
std::vector<unsigned char> encryptDecryptData(const std::vector<unsigned char>& data, int key);

#endif
