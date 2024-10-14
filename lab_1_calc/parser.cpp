#include "parser.h"
#include <stack>
#include <sstream>
#include <stdexcept>
#include <cmath>
#include <iostream>
#include <cctype>

Parser::Parser(const std::unordered_map<std::string, Function>& functions,
    const std::unordered_map<std::string, FunctionPow>& functions_pow)
    : functions(functions), functions_pow(functions_pow) {}

double Parser::parseAndEvaluate(const std::string& expression) {
    // Заменяем пробелы
    std::string expr = removeSpaces(expression);

    // Преобразуем выражение в обратную польскую нотацию (RPN)
    std::vector<std::string> tokens = infixToPostfix(expr);

    // Вычисляем результат выражения в RPN
    return evaluatePostfix(tokens);
}

std::string Parser::removeSpaces(const std::string& str) {
    std::string result;
    for (char ch : str) {
        if (!isspace(ch)) result += ch;
    }
    return result;
}

// Пример преобразования инфиксного выражения в постфиксное (RPN)
std::vector<std::string> Parser::infixToPostfix(const std::string& expr) {
    std::vector<std::string> output;
    std::stack<char> operators;

    for (size_t i = 0; i < expr.length(); ++i) {
        char ch = expr[i];

        if (isdigit(ch)) {
            std::string num;
            while (isdigit(ch) || ch == '.') {
                num += ch;
                ch = expr[++i];
            }
            --i;
            output.push_back(num);
        }
        else if (ch == '(') {
            operators.push(ch);
        }
        else if (ch == ')') {
            while (!operators.empty() && operators.top() != '(') {
                output.push_back(std::string(1, operators.top()));
                operators.pop();
            }
            operators.pop();
        }
        else if (ch == '+' || ch == '-' || ch == '*' || ch == '/') {
            while (!operators.empty() && precedence(operators.top()) >= precedence(ch)) {
                output.push_back(std::string(1, operators.top()));
                operators.pop();
            }
            operators.push(ch);
        }
        else if (isalpha(ch)) {
            std::string func;
            while (isalpha(ch)) {
                func += ch;
                ch = expr[++i];
            }
            --i;
            output.push_back(func);
        }
    }

    while (!operators.empty()) {
        output.push_back(std::string(1, operators.top()));
        operators.pop();
    }

    return output;
}

int Parser::precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

double Parser::evaluatePostfix(const std::vector<std::string>& tokens) {
    std::stack<double> stack;

    for (const auto& token : tokens) {
        if (isdigit(token[0])) {
            stack.push(std::stod(token));
        }
        else if (token == "+" || token == "-" || token == "*" || token == "/") {
            double b = stack.top(); stack.pop();
            double a = stack.top(); stack.pop();
            if (token == "+") stack.push(a + b);
            if (token == "-") stack.push(a - b);
            if (token == "*") stack.push(a * b);
            if (token == "/") stack.push(a / b);
        }
        else if (functions.find(token) != functions.end()) {
            int argCount = functions.at(token).target_type().hash_code();
            std::vector<double> args(argCount);
            for (int i = argCount - 1; i >= 0; --i) {
                args[i] = stack.top(); stack.pop();
            }
            stack.push(functions.at(token)(args));
        }
        else {
            throw std::runtime_error("Неизвестная функция: " + token);
        }
    }

    return stack.top();
}

