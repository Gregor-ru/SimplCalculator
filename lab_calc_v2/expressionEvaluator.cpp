#include "expressionEvaluator.h"
#include <stack>
#include <regex>
#include <iostream>

ExpressionEvaluator::ExpressionEvaluator(const std::map<std::string, Plugin>& plugins) : plugins(plugins) {}

double ExpressionEvaluator::performOperation(double left, char op, double right) {
    switch (op) {
    case '+': return left + right;
    case '-': return left - right;
    case '*': return left * right;
    case '/': return right != 0 ? left / right : 0;
    default: return 0;
    }
}

double ExpressionEvaluator::evaluateExpression(const std::string& expression) {
    std::stack<double> values;
    std::stack<char> ops;

    auto applyOperation = [&]() {
        double right = values.top(); values.pop();
        double left = values.top(); values.pop();
        char op = ops.top(); ops.pop();
        values.push(performOperation(left, op, right));
        };

    size_t i = 0;
    while (i < expression.size()) {
        if (isspace(expression[i])) {
            i++;
            continue;
        }

        if (isdigit(expression[i]) || expression[i] == '.') {
            std::string valueStr;
            while (i < expression.size() && (isdigit(expression[i]) || expression[i] == '.')) {
                valueStr += expression[i++];
            }
            values.push(std::stod(valueStr));
        }
        else if (expression[i] == '(') {
            ops.push(expression[i++]);
        }
        else if (expression[i] == ')') {
            while (!ops.empty() && ops.top() != '(') {
                applyOperation();
            }
            ops.pop(); // Убираем '('
            i++;
        }
        else if (strchr("+-*/", expression[i])) {
            while (!ops.empty() && ops.top() != '(' &&
                ((expression[i] == '+' || expression[i] == '-') ||
                    (expression[i] == '*' || expression[i] == '/'))) {
                applyOperation();
            }
            ops.push(expression[i++]);
        }
        else {
            i++;
        }
    }

    while (!ops.empty()) {
        applyOperation();
    }

    return values.top();
}

double ExpressionEvaluator::parseAndEvaluate(const std::string& expression) {
    std::string expr = expression;

    // Сначала обрабатываем функции
    std::regex funcRegex(R"((\w+)\(([\d\.\-\,\s\+\-\*\/\(\)]*)\))");
    std::smatch match;

    while (std::regex_search(expr, match, funcRegex)) {
        std::string funcName = match[1];
        std::string argsStr = match[2];

        // Поиск плагина по имени функции
        auto it = plugins.find(funcName);
        if (it != plugins.end()) {
            Plugin plugin = it->second;

            // Разбиваем строку аргументов на числа
            std::vector<double> args;

            size_t pos = 0;
            while ((pos = argsStr.find(',')) != std::string::npos) {
                std::string token = argsStr.substr(0, pos);
                args.push_back(parseAndEvaluate(token)); // Рекурсивный вызов для вложенных выражений
                argsStr.erase(0, pos + 1);
            }
            if (!argsStr.empty()) {
                args.push_back(parseAndEvaluate(argsStr)); // Рекурсивный вызов для последнего аргумента
            }

            // Оценим функцию и заменим в строке результатом
            double result = evaluateFunction(plugin, args);
            expr.replace(match.position(0), match.length(0), std::to_string(result));
        }
        else {
            std::cerr << "Функция " << funcName << " не найдена." << std::endl;
            return 0.0;
        }
    }

    // Обрабатываем оставшиеся арифметические выражения
    return evaluateExpression(expr);
}

double ExpressionEvaluator::evaluate(const std::string& expression) {
    return parseAndEvaluate(expression);
}
