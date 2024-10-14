#define EXPORT extern "C" __declspec(dllexport)

#include <cmath>

// Ёкспортируема€ функци€ возведени€ в степень
// ѕервый аргумент Ч основание (base), второй Ч показатель (exponent)
EXPORT double func(double base, double exponent) {
    return std::pow(base, exponent);
}
