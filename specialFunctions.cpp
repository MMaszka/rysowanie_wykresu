#include "specialFunctions.h"

long double factorial(long double a) {
    if (a < 0) return NAN;
    long double result = 1;
    for (int i = 1; i <= static_cast<int>(a); ++i) {
        result *= i;
    }
    return result;
}

long double root(long double n, long double a) {
    return std::pow(a, 1.0 / n);
}

long double exponential(long double a) {
    return std::exp(a);
}

long double logarithm(long double a, long double b) {
    return std::log(b) / std::log(a);
}

long double logarithmOf10(long double a) {
    return std::log10(a);
}

long double naturalLogarithm(long double a) {
    return std::log(a);
}

long double sinus(long double a) {
    return std::sin(a);
}

long double cosinus(long double a) {
    return std::cos(a);
}

long double tangent(long double a) {
    return std::tan(a);
}

long double cotangent(long double a) {
    return std::cos(a) / std::sin(a);
}

long double arcusSinus(long double a) {
    return std::asin(a);
}

long double arcusCosinus(long double a) {
    return std::acos(a);
}

long double arcusTangent(long double a) {
    return std::atan(a);
}

long double arcusCotangent(long double a) {
    return M_PI / 2 - std::atan(a);
}

long double absoluteValue(long double a) {
    return std::fabs(a);
}

long double scientificNotation(long double a, long double n) {
    return a * std::pow(10, n);
}