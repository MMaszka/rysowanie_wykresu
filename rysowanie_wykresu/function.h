#pragma once
#define _USE_MATH_DEFINES

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>
#include <string>
#include <vector>

#include "shader.h"
#include "window.h"

#include <thread>
#include <chrono>
#include <numeric>
#include <math.h>
#include <iostream>
#include <string>
#include <regex>
#include <algorithm>

struct Operators {
	std::string allowed = ("|sqrt|sin|cos|tan|cot|arcsin|arccos|arctan|arccot|lg|ln|;|+|-|*|/|^|"); // if operator is longer than max allowed operator length it wont be checked
	int maxAllowedLength = 6;
	int semicolonPosition = allowed.find(";");
};

class Function {
private:
	float vertices[6]{	-0.5f, -0.5f, 0.0f,	1.0f, 1.0f, 1.0f };// should be 0.0f,0.0f,0.0f --- to changed... in future
	unsigned int indices[1]{ 0 };
	int vertices_size{6}, indices_size{1};
	unsigned int VAO{}, VBO{}, EBO{}, sizeEBO{}, sizeVAO{}, buffer{};

	int number_of_points = 20000; // number of points per function - can't be less than 10
	int precisionDigits = static_cast<int>(std::log10(number_of_points)) + 1; // number of digits in nuber_of_points
	int precision = number_of_points / static_cast<int>(std::pow(10, precisionDigits - 1)); // first digit in number_of_points

	// RNP
	int* SimplifiedType;// stores simplified version of function
	float* SimplifiedValue;
	int* RPNType;// stores Reverse Polish Notation of function
	float* RPNValue;
	int* RPNTypeCopy;// stores Reverse Polish Notation of function
	float* RPNValueCopy;

	std::string functionString;
	int RPNLength;
	int SimplifiedLength{};

public:
	bool is_special = false;
	App_info app_info;
	glm::vec3 position{};// cam position
	bool IsCorrect = false;
	std::vector <std::string> functions;// stores sub functions --- do we need this anymore?
	// sub functions would store equations like "y^2=x" or mre complex like "y^3 + y^2 = x^3-x^2+3x"

	float xPlaneSpacing{}; // distance between x's
	float xPlaneShift{}; // shift block of x's - relative to point (0.0,0.0,0.0)
	int point_number = 0;
	glm::mat4* pointMatrices = new glm::mat4[number_of_points];// stores function points
	glm::vec3 color = glm::vec3(0.5f, 0.5f, 0.5f);

	Function(std::string fun,App_info info);
	void CreateBuffers();
	void ModifyInstances();
	bool CheckFunction();
	void CalculateFunction();
	void Draw();
	void ChangeColor(glm::vec3 color);

	//RNP
	void SimplifyFunction();
	void ToRPN();
	float CalculateRPN(float x);
	float solve(int Type[], float Value[], int size);

	~Function();
};

extern bool IsSpecial;
extern bool Remove;
void GetFunctionString(GLFWwindow* window, std::string* function, bool* finished);

// General
#define NUMBER 1
#define VARIABLE 2
#define OPERATOR 3

// (group one) RPN - one variale operators 
#define SQRT 101
#define SIN 102
#define COS 103
#define TAN 104
#define COT 105
#define ARCSIN 106
#define ARCCOS 107
#define ARCTAN 108
#define ARCCOT 109

#define ABS 130 // not implemented 
#define FACT 131 // not implemented 


#define LG 110
#define LN 111

//(group two) RPN - two variable operators

#define ADDITION 201
#define SUBSTRACTION 202
#define MULTIPLICATION 203
#define DIVISION 204
#define EXPONENTIATION 205

#define LOG 230 // not implemented

// Basic "string to numbers" characters
#define BRACKET_OPEN 10
#define BRACKET_CLOSE 11