#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <map>
#include <string>
#include "plugin.h"
#include "expressionEvaluator.h"

class Calculator {
public:
    Calculator();
    void run();

private:
    std::map<std::string, Plugin> plugins;
    ExpressionEvaluator evaluator;
};

#endif // CALCULATOR_H
<<<<<<< Updated upstream
=======

>>>>>>> Stashed changes
