#include "input.h"
#include <stack>
#include <iostream>
#include "specialFunctions.h"

// Funkcja pomocnicza do obliczania wyniku dla operacji wewn¹trz nawiasów
double evaluateTempRPN(std::vector<std::string>& tempExpression, double x) {
    std::vector<double> stack;
    std::vector<double> tempStack;
    std::vector<char> bracketStorage;
    std::string newToken;

    for (int i = 0; i < tempExpression.size(); i++) {
        newToken = tempExpression[i];

        if (newToken == "x") {
            stack.push_back(x);
        }
        else if (isdigit(newToken[0]) || (newToken[0] == '-' && newToken.size() > 1 && isdigit(newToken[1]))) {
            // Token jest liczb¹ lub ujemn¹ liczb¹
            stack.push_back(std::stold(newToken));
        }
        else if (newToken == "+") {
            if (stack.size() < 2) {
                std::cerr << "Blad: za malo operandow dla operatora '+'." << std::endl;
                return NAN;
            }
            long double b = stack.back(); stack.pop_back();
            long double a = stack.back(); stack.pop_back();
            stack.push_back(a + b);
        }
        else if (newToken == "-") {
            if (stack.size() < 1) {
                std::cerr << "Blad: za malo operandow dla operatora '-'." << std::endl;
                return NAN;
            }
            if (stack.size() == 1) {
                long double a = stack.back(); stack.pop_back();
                stack.push_back(-a);
            }
            else {
                long double b = stack.back(); stack.pop_back();
                long double a = stack.back(); stack.pop_back();
                stack.push_back(a - b);
            }
        }
        else if (newToken == "*") {
            if (stack.size() < 2) {
                std::cerr << "Blad: za malo operandow dla operatora '*'." << std::endl;
                return NAN;
            }
            long double b = stack.back(); stack.pop_back();
            long double a = stack.back(); stack.pop_back();
            stack.push_back(a * b);
        }
        else if (newToken == "/") {
            if (stack.size() < 2) {
                std::cerr << "Blad: za malo operandow dla operatora '/'." << std::endl;
                return NAN;
            }
            long double b = stack.back(); stack.pop_back();
            long double a = stack.back(); stack.pop_back();
            stack.push_back(a / b);
        }
        else if (newToken == "^") {
            if (stack.size() < 2) {
                std::cerr << "Blad: za malo operandow dla operatora '^'." << std::endl;
                return NAN;
            }
            long double b = stack.back(); stack.pop_back();
            long double a = stack.back(); stack.pop_back();
            stack.push_back(std::pow(a, b));
        }
        else if (newToken == "(") {
            bracketStorage.push_back('(');
            std::string tempToken = newToken;
            std::vector<std::string> tempExpression;
            int j = i + 1;

            for (j; j < tempExpression.capacity() - 1; j++) {
                if (tempExpression[j] == "(") continue;
                if (tempExpression[j] == ")") {
                    break;
                }
                tempExpression.push_back(tempExpression[j]);
            }
            long double result = evaluateTempRPN(tempExpression, x);
            stack.push_back(result);

            int n = j - i;
            i += n;
        }
        else if (newToken == "fact") {
            double a = stack.back(); stack.pop_back();
            stack.push_back(factorial(a));
        }
        else if (newToken == "root") {
            double a = stack.back(); stack.pop_back();
            double n = stack.back(); stack.pop_back();
            stack.push_back(root(n, a));
        }
        else if (newToken == "exp") {
            double a = stack.back(); stack.pop_back();
            stack.push_back(exponential(a));
        }
        else if (newToken == "log") {
            double b = stack.back(); stack.pop_back();
            double a = stack.back(); stack.pop_back();
            stack.push_back(logarithm(a, b));
        }
        else if (newToken == "lg") {
            double a = stack.back(); stack.pop_back();
            stack.push_back(logarithmOf10(a));
        }
        else if (newToken == "ln") {
            double a = stack.back(); stack.pop_back();
            stack.push_back(naturalLogarithm(a));
        }
        else if (newToken == "sin") {
            double a = stack.back(); stack.pop_back();
            stack.push_back(sinus(a));
        }
        else if (newToken == "cos") {
            double a = stack.back(); stack.pop_back();
            stack.push_back(cosinus(a));
        }
        else if (newToken == "tg") {
            double a = stack.back(); stack.pop_back();
            stack.push_back(tangent(a));
        }
        else if (newToken == "ctg") {
            double a = stack.back(); stack.pop_back();
            stack.push_back(cotangent(a));
        }
        else if (newToken == "arcsin") {
            double a = stack.back(); stack.pop_back();
            stack.push_back(arcusSinus(a));
        }
        else if (newToken == "arccos") {
            double a = stack.back(); stack.pop_back();
            stack.push_back(arcusCosinus(a));
        }
        else if (newToken == "arctg") {
            double a = stack.back(); stack.pop_back();
            stack.push_back(arcusTangent(a));
        }
        else if (newToken == "arcctg") {
            double a = stack.back(); stack.pop_back();
            stack.push_back(arcusCotangent(a));
        }
        else if (newToken == "abs") {
            double a = stack.back(); stack.pop_back();
            stack.push_back(absoluteValue(a));
        }
        else if (newToken == "scn") {
            double n = stack.back(); stack.pop_back();
            double a = stack.back(); stack.pop_back();
            stack.push_back(scientificNotation(a, n));
        }
        else {
            std::cerr << "Nieznany token: " << newToken << std::endl;
            return NAN;
        }
    }

    // Na koñcu powinna byæ tylko jedna wartoœæ na stosie tymczasowym
    if (stack.size() != 1) {
        std::cerr << "Blad: nieprawid³owa liczba operandow i operatorow w nawiasie." << std::endl;
        return NAN;
    }

    return stack.back();
}


double function::evaluateRPN(const std::vector<std::string>& expression, double x) {
    std::vector<double> stack;
    std::vector<double> tempStack;
    std::vector<char> bracketStorage;
    std::string token;

    for (int i = 0; i < expression.size(); i++) {
        token = expression[i];
        if (token == "x") {
            stack.push_back(x);
        }
        else if (isdigit(token[0]) || (token[0] == '-' && token.size() > 1 && isdigit(token[1]))) {
            // Token jest liczb¹ lub ujemn¹ liczb¹
            stack.push_back(std::stold(token));
        }
        else if (token == "+") {
            if (stack.size() < 2) {
                std::cerr << "Blad: za malo operandow dla operatora '+'." << std::endl;
                return NAN;
            }
            long double b = stack.back(); stack.pop_back();
            long double a = stack.back(); stack.pop_back();
            stack.push_back(a + b);
        }
        else if (token == "-") {
            if (stack.size() < 1) {
                std::cerr << "Blad: za malo operandow dla operatora '-'." << std::endl;
                return NAN;
            }
            if (stack.size() == 1) {
                long double a = stack.back(); stack.pop_back();
                stack.push_back(-a);
            }
            else {
                long double b = stack.back(); stack.pop_back();
                long double a = stack.back(); stack.pop_back();
                stack.push_back(a - b);
            }
        }
        else if (token == "*") {
            if (stack.size() < 2) {
                std::cerr << "Blad: za malo operandow dla operatora '*'." << std::endl;
                return NAN;
            }
            long double b = stack.back(); stack.pop_back();
            long double a = stack.back(); stack.pop_back();
            stack.push_back(a * b);
        }
        else if (token == "/") {
            if (stack.size() < 2) {
                std::cerr << "Blad: za malo operandow dla operatora '/'." << std::endl;
                return NAN;
            }
            long double b = stack.back(); stack.pop_back();
            long double a = stack.back(); stack.pop_back();
            stack.push_back(a / b);
        }
        else if (token == "^") {
            if (stack.size() < 2) {
                std::cerr << "Blad: za malo operandow dla operatora '^'." << std::endl;
                return NAN;
            }
            long double b = stack.back(); stack.pop_back();
            long double a = stack.back(); stack.pop_back();
            stack.push_back(std::pow(a, b));
        }
        else if (token == "(") {
            bracketStorage.push_back('(');
            std::string tempToken = token;
            std::vector<std::string> tempExpression;
            int j = i+1;

            for (j; j < expression.capacity() - 1; j++) {
                if (expression[j] == "(") continue;
                if (expression[j] == ")") {
                    break;
                }
                tempExpression.push_back(expression[j]);
            }
            long double result = evaluateTempRPN(tempExpression, x);
            stack.push_back(result);

            int n = j - i;
            i += n;
        }
        else if (token == "fact") {
            double a = stack.back(); stack.pop_back();
            stack.push_back(factorial(a));
        }
        else if (token == "root") {
            double a = stack.back(); stack.pop_back();
            double n = stack.back(); stack.pop_back();
            stack.push_back(root(n, a));
        }
        else if (token == "exp") {
            double a = stack.back(); stack.pop_back();
            stack.push_back(exponential(a));
        }
        else if (token == "log") {
            double b = stack.back(); stack.pop_back();
            double a = stack.back(); stack.pop_back();
            stack.push_back(logarithm(a, b));
        }
        else if (token == "lg") {
            double a = stack.back(); stack.pop_back();
            stack.push_back(logarithmOf10(a));
        }
        else if (token == "ln") {
            double a = stack.back(); stack.pop_back();
            stack.push_back(naturalLogarithm(a));
        }
        else if (token == "sin") {
            double a = stack.back(); stack.pop_back();
            stack.push_back(sinus(a));
        }
        else if (token == "cos") {
            double a = stack.back(); stack.pop_back();
            stack.push_back(cosinus(a));
        }
        else if (token == "tg") {
            double a = stack.back(); stack.pop_back();
            stack.push_back(tangent(a));
        }
        else if (token == "ctg") {
            double a = stack.back(); stack.pop_back();
            stack.push_back(cotangent(a));
        }
        else if (token == "arcsin") {
            double a = stack.back(); stack.pop_back();
            stack.push_back(arcusSinus(a));
        }
        else if (token == "arccos") {
            double a = stack.back(); stack.pop_back();
            stack.push_back(arcusCosinus(a));
        }
        else if (token == "arctg") {
            double a = stack.back(); stack.pop_back();
            stack.push_back(arcusTangent(a));
        }
        else if (token == "arcctg") {
            double a = stack.back(); stack.pop_back();
            stack.push_back(arcusCotangent(a));
        }
        else if (token == "abs") {
            double a = stack.back(); stack.pop_back();
            stack.push_back(absoluteValue(a));
        }
        else if (token == "scn") {
            double n = stack.back(); stack.pop_back();
            double a = stack.back(); stack.pop_back();
            stack.push_back(scientificNotation(a, n));
        }
        else {
            std::cerr << "Nieznany token: " << token << std::endl;
            return NAN;
        }
    }

    if (stack.size() != 1) {
        std::cerr << "Blad: Stos nie jest jednoelementowy po przetworzeniu calego wyrazenia." << std::endl;
        return NAN;
    }

    double result = stack.back();
    return result;
}