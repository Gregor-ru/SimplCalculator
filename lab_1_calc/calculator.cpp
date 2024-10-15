#include "calculator.h"
#include "PluginLoader.h"
#include <iostream>

Calculator::Calculator() : evaluator(plugins) {
    loadPlugins(plugins);
}

void Calculator::run() {
    std::string expression;
    while (true) {
        std::cout << "Enter an expression: ";
        std::getline(std::cin, expression);

        if (expression == "exit") break;

        double result = evaluator.evaluate(expression);
        std::cout << "Result: " << result << std::endl;
    }
}

// for PR