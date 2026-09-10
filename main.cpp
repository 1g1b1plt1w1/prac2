#include <iostream>
#include <string>
#include <unordered_map>
#include "tasks.h"

using namespace std;

enum alg {
    POWERMOD,
    EXTENDED_EUCLIDEAN,
    INVERSEMOD,
    DIFFIE_HELLMAN,
    EXIT,
    UNKNOWN
};

unordered_map<string, alg> processing = {
    {"powermod", POWERMOD},
    {"extended euclidean", EXTENDED_EUCLIDEAN},
    {"inversemod", INVERSEMOD},
    {"diffie hellman", DIFFIE_HELLMAN},
    {"exit", EXIT}
};

alg cmdToAlg(string str) {
    auto it = processing.find(str);
    if (it != processing.end()) {
        return it->second;
    }
    return UNKNOWN;
}

void start() {
    cout << "============================================================\n";
    cout << "Инструкция по работе с программой:\n";
    cout << "Введите одну из доступных команд в консоль:\n";
    cout << "  powermod           - вычисление a^x mod p через т.Ферма и двоичное разложение\n";
    cout << "  extended euclidean - обратный элемент c*d mod m = 1 через алгоритм Евклида\n";
    cout << "  inversemod         - обратный элемент c^-1 mod m = d\n";
    cout << "  diffie hellman     - протокол Диффи-Хеллмана и шифрование данных (текст/файл)\n";
    cout << "  exit               - завершение работы программы\n";
    cout << "============================================================\n\n";
}

void get_input(string& a) {
    cout << "Ввод команды: ";
    getline(cin >> ws, a);
}

int main() {
    start();
    string input;
    while (true) {
        get_input(input);
        switch (cmdToAlg(input)) {
            case POWERMOD:
                solvePowerMod();
                break;
            case EXTENDED_EUCLIDEAN:
                solveExtendedEuclidean();
                break;
            case INVERSEMOD:
                solveInverseMod();
                break;
            case DIFFIE_HELLMAN:
                solveDiffieHellman();
                break;
            case EXIT:
                return 0;
            default:
                cout << "Неизвестная команда\n";
                break;
        }
        cout << "\n";
    }
}