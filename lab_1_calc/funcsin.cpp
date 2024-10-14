#define EXPORT extern "C" __declspec(dllexport)

#include <cmath>

// Экспортируемая функция sin
EXPORT double func(double x) {
    return std::sin(x);
}