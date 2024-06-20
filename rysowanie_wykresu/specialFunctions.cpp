#include "specialFunctions.h"

double applyOperator(double a, double b, const std::string& op) {
    if (op == "+") return a + b;
    if (op == "-") return a - b;
    if (op == "*") return a * b;
    if (op == "/") return a / b;
    if (op == "^") return std::pow(a, b);
    throw std::runtime_error("Niewlasciwy operator.");
}

double factorial(double a) {
    if (a < 0) return NAN;
    double result = 1;
    for (int i = 1; i <= static_cast<int>(a); ++i) {
        result *= i;
    }
    return result;
}

double root(double n, double a) {
    return std::pow(a, 1.0 / n);
}

double exponential(double a) {
    return std::exp(a);
}

double logarithm(double a, double b) {
    return std::log(b) / std::log(a);
}

double logarithmOf10(double a) {
    return std::log10(a);
}

double naturalLogarithm(double a) {
    return std::log(a);
}

double sinus(double a) {
    return std::sin(a);
}

double cosinus(double a) {
    return std::cos(a);
}

double tangent(double a) {
    return std::tan(a);
}

double cotangent(double a) {
    return std::cos(a) / std::sin(a);
}

double arcusSinus(double a) {
    return std::asin(a);
}

double arcusCosinus(double a) {
    return std::acos(a);
}

double arcusTangent(double a) {
    return std::atan(a);
}

double arcusCotangent(double a) {
    return M_PI / 2 - std::atan(a);
}

double absoluteValue(double a) {
    if (a >= 0) return a;
    else return -a;
}

double scientificNotation(double a, double n) {
    return a * std::pow(10, n);
}