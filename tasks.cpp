#include "tasks.h"
#include "math_funcs.h"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <iomanip>
#include <random>

using namespace std;

void solvePowerMod() {
    int a, x, p;
    cout << "Введите a, x, p: ";
    cin >> a >> x >> p;

    int res_ferma = ferma(a, x, p);
    if (res_ferma == -1) {
        cout << "Ошибка: теорема Ферма неприменима (p не простое или НОД != 1)\n";
    } else {
        cout << "Результат (т.Ферма): " << res_ferma << "\n";
    }
    cout << "Результат (двоичное разложение): " << powMod(a, x, p) << "\n";
}

void solveExtendedEuclidean() {
    int c, m;
    cout << "Введите c и m: ";
    cin >> c >> m;

    int u, v;
    if (extendedGCD(c, m, u, v) != 1) {
        cout << "Обратного не существует (числа не взаимно просты)\n";
        return;
    }
    int d = (u % m + m) % m;
    cout << "u = " << u << ", v = " << v << "\n";
    cout << "d = " << d << "\n";
}

void solveInverseMod() {
    int c, m;
    cout << "Введите c и m: ";
    cin >> c >> m;

    int inv = modInverse(c, m);
    if (inv == -1) {
        cout << "Взаимно обратного не существует\n";
    } else {
        cout << "c^(-1) mod m = " << inv << "\n";
    }
}

void solveDiffieHellman() {
    int p = getRandomPrime();
    int g = findPrimitiveRoot(p);

    cout << "Параметры: p = " << p << ", g = " << g << "\n";

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dist(2, p - 2);

    int a = dist(gen);
    int A = powMod(g, a, p);
    cout << "Алиса: a = " << a << ", A = " << A << "\n";

    int b = dist(gen);
    int B = powMod(g, b, p);
    cout << "Боб:   b = " << b << ", B = " << B << "\n";

    int Ka = powMod(B, a, p);
    int Kb = powMod(A, b, p);

    if (Ka != Kb) {
        cout << "Ошибка согласования ключей\n";
        return;
    }
    cout << "Общий ключ K = " << Ka << "\n";

    cout << "Режим (1 - строка, 2 - файл): ";
    int choice = 1;
    cin >> choice;

    if (choice == 1) {
        cout << "Сообщение: ";
        string message;
        getline(cin >> ws, message);

        vector<unsigned char> data(message.begin(), message.end());
        vector<unsigned char> encrypted = encryptDecryptData(data, Ka);

        cout << "Зашифровано (hex): ";
        cout << hex << setfill('0');
        for (unsigned char byte_val : encrypted) {
            cout << setw(2) << static_cast<int>(byte_val) << " ";
        }
        cout << dec << "\n";

        vector<unsigned char> decrypted = encryptDecryptData(encrypted, Kb);
        cout << "Расшифровано: " << string(decrypted.begin(), decrypted.end()) << "\n";
    } else {
        string in_path, enc_path, dec_path;
        cout << "Пути (исходный, зашифрованный, расшифрованный): ";
        cin >> in_path >> enc_path >> dec_path;

        ifstream fin(in_path, ios::binary);
        if (!fin) {
            cout << "Ошибка чтения файла\n";
            return;
        }
        vector<unsigned char> file_data((istreambuf_iterator<char>(fin)), istreambuf_iterator<char>());
        fin.close();

        vector<unsigned char> encrypted = encryptDecryptData(file_data, Ka);
        ofstream fenc(enc_path, ios::binary);
        fenc.write(reinterpret_cast<const char*>(encrypted.data()), encrypted.size());
        fenc.close();

        vector<unsigned char> decrypted = encryptDecryptData(encrypted, Kb);
        ofstream fdec(dec_path, ios::binary);
        fdec.write(reinterpret_cast<const char*>(decrypted.data()), decrypted.size());
        fdec.close();

        cout << "Файл успешно обработан\n";
    }
}