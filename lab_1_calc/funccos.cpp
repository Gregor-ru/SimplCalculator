#define EXPORT extern "C" __declspec(dllexport)

#include <cmath>

// Экспортируемая функция cos
EXPORT double func(double x) {
    return std::cos(x);
}
