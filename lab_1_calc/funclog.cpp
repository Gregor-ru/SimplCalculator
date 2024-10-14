#define EXPORT extern "C" __declspec(dllexport)

#include <cmath>
#include <stdexcept>

// Ёкспортируема€ функци€ log
EXPORT double func(double x) {
    if (x <= 0) {
        throw std::domain_error("Ћогарифм от неположительного числа");
    }
    return std::log(x);
}
