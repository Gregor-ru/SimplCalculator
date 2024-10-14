#pragma once
#include <string>
#include <unordered_map>
#include <functional>
#include <vector>

using Function = std::function<double(double)>;
using FunctionPow = std::function<double(double, double)>;

class Parser {
public:
    Parser(const std::unordered_map<std::string, Function>& functions,
        const std::unordered_map<std::string, FunctionPow>& functions_pow);
    double parseAndEvaluate(const std::string& expression);

private:
    std::unordered_map<std::string, Function> functions;
    std::unordered_map<std::string, FunctionPow> functions_pow;

    std::string removeSpaces(const std::string& str);
    std::vector<std::string> infixToPostfix(const std::string& expr);
    double evaluatePostfix(const std::vector<std::string>& tokens);
    int precedence(char op);
};
