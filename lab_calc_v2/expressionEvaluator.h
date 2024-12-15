#ifndef EXPRESSION_EVALUATOR_H
#define EXPRESSION_EVALUATOR_H

#include <string>
#include <map>
#include "plugin.h"

class ExpressionEvaluator {
public:
    ExpressionEvaluator(const std::map<std::string, Plugin>& plugins);
    double evaluate(const std::string& expression);

private:
    double evaluateExpression(const std::string& expression);
    double parseAndEvaluate(const std::string& expression);
    double performOperation(double left, char op, double right);
    const std::map<std::string, Plugin>& plugins;
};

#endif // EXPRESSION_EVALUATOR_H
