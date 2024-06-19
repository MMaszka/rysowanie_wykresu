#include <iostream>
#include <stack>
#include <sstream>
#include <algorithm>
#include "input.h"
#include "specialFunctions.h"
#include "dataVerifiers.h"

long double function::evaluateRPN(const std::string& expression, long double x) {
    std::stack<long double> stack;
    std::istringstream tokens(expression);
    std::string token;

    while (tokens >> token) {
        if (token == "x") {
            stack.push(x);
        }
        else if (isdigit(token[0]) || (token[0] == '-' && isdigit(token[1]))) {
            stack.push(std::stold(token));
        }
        else if (token == "-" && (stack.empty() || isOperator(stack.top()) || isSpecialFunction(std::to_string(stack.top())))) {
            tokens >> token;
            if (token == "x") {
                stack.push(-x);
            }
            else if (isdigit(token[0]) || (token[0] == '-' && isdigit(token[1]))) {
                stack.push(-std::stold(token));
            }
            else if (isSpecialFunction(token)) {
                // Handle case like -abs(x)
                tokens.putback(' '); // putback space to re-parse function correctly
                tokens.str(token + tokens.str().substr(tokens.tellg()));
                tokens.clear();
                stack.push(0); // Add zero for the unary minus case
            }
        }
        else if (token == "*") {
            long double b = stack.top(); stack.pop();
            long double a = stack.top(); stack.pop();
            stack.push(a * b);
        }
        else if (token == "/") {
            long double b = stack.top(); stack.pop();
            long double a = stack.top(); stack.pop();
            stack.push(a / b);
        }
        else if (token == "^") {
            long double b = stack.top(); stack.pop();
            long double a = stack.top(); stack.pop();
            stack.push(std::pow(a, b));
        }
        else if (token == "fact") {
            long double a = stack.top(); stack.pop();
            stack.push(factorial(a));
        }
        else if (token == "root") {
            long double a = stack.top(); stack.pop();
            long double n = stack.top(); stack.pop();
            stack.push(root(n, a));
        }
        else if (token == "exp") {
            long double a = stack.top(); stack.pop();
            stack.push(exponential(a));
        }
        else if (token == "log") {
            long double b = stack.top(); stack.pop();
            long double a = stack.top(); stack.pop();
            stack.push(logarithm(a, b));
        }
        else if (token == "lg") {
            long double a = stack.top(); stack.pop();
            stack.push(logarithmOf10(a));
        }
        else if (token == "ln") {
            long double a = stack.top(); stack.pop();
            stack.push(naturalLogarithm(a));
        }
        else if (token == "sin") {
            long double a = stack.top(); stack.pop();
            stack.push(sinus(a));
        }
        else if (token == "cos") {
            long double a = stack.top(); stack.pop();
            stack.push(cosinus(a));
        }
        else if (token == "tg") {
            long double a = stack.top(); stack.pop();
            stack.push(tangent(a));
        }
        else if (token == "ctg") {
            long double a = stack.top(); stack.pop();
            stack.push(cotangent(a));
        }
        else if (token == "arcsin") {
            long double a = stack.top(); stack.pop();
            stack.push(arcusSinus(a));
        }
        else if (token == "arccos") {
            long double a = stack.top(); stack.pop();
            stack.push(arcusCosinus(a));
        }
        else if (token == "arctg") {
            long double a = stack.top(); stack.pop();
            stack.push(arcusTangent(a));
        }
        else if (token == "arcctg") {
            long double a = stack.top(); stack.pop();
            stack.push(arcusCotangent(a));
        }
        else if (token == "abs") {
            long double a = stack.top(); stack.pop();
            stack.push(absoluteValue(a));
        }
        else if (token == "scn") {
            long double n = stack.top(); stack.pop();
            long double a = stack.top(); stack.pop();
            stack.push(scientificNotation(a, n));
        }
        else {
            std::cerr << "Nieznany token: " << token << std::endl;
            return NAN;
        }
    }

    if (stack.size() != 1) {
        std::cerr << "B³¹d: Stos nie jest jednoelementowy po przetworzeniu ca³ego wyra¿enia." << std::endl;
        return NAN;
    }

    long double result = stack.top();
    std::cout << "Dla x = " << x << " wynik funkcji wynosi: " << result << std::endl;
    return result;
}