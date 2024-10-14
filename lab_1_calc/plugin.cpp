#include "plugin.h"
#include <iostream>

double evaluateFunction(const Plugin& plugin, std::vector<double>& args) {
    if (args.size() != plugin.argCount) {
        std::cerr << "Неверное количество аргументов для функции " << plugin.name << std::endl;
        return 0.0;
    }

    double* argArray = args.data();

    std::cout << "Вызов функции " << plugin.name << " с аргументами: ";
    for (auto arg : args) {
        std::cout << arg << " ";
    }
    std::cout << std::endl;

    double result = plugin.execute(argArray);

    std::cout << "Результат выполнения функции " << plugin.name << ": " << result << std::endl;

    return result;
}
