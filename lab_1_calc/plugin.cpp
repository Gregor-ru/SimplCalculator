#include "plugin.h"
#include <iostream>

double evaluateFunction(const Plugin& plugin, std::vector<double>& args) {
    if (args.size() != plugin.argCount) {
        std::cerr << "Invalid number of arguments for function " << plugin.name << std::endl;
        return 0.0;
    }

    double* argArray = args.data();

    std::cout << "Calling a function " << plugin.name << " with arguments: ";
    for (auto arg : args) {
        std::cout << arg << " ";
    }
    std::cout << std::endl;

    double result = plugin.execute(argArray);

    std::cout << "Function execution result" << plugin.name << ": " << result << std::endl;

    return result;
}

// for PR