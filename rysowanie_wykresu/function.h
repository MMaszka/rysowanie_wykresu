#pragma once
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

struct Operators {
	std::string allowed = ("|sin|cos|tan|cot|;|+|-|*|/|^|"); // if operator is longer than max allowed operator length it wont be checked
	int maxAllowedLength = 4;
	int semicolonPosition = allowed.find(";");
};

class Function {
private:
	float vertices[6]{	-0.5f, -0.5f, 0.0f,	1.0f, 1.0f, 1.0f };// should be 0.0f,0.0f,0.0f --- to change... in future
	unsigned int indices[1]{ 0 };

	int vertices_size{6}, indices_size{1};
	unsigned int VAO{}, VBO{}, EBO{}, sizeEBO{}, sizeVAO{}, buffer{};
	int number_of_points = 5000; // number of points per function

	// RNP
	int* SimplifiedType;// stores simplified version of function
	float* SimplifiedValue;
	int* RPNType;// stores Reverse Polish Notation of function
	float* RPNValue;
	std::string functionString;
	int RPNLength;
	int SimplifiedLength{};

public:
	App_info app_info;
	glm::vec3 position{};// cam position
	bool IsCorrect = false;

	std::vector <std::string> functions;// stores sub functions --- do we need this anymore?
	// sub functions would store equations like "y^2=x" or mre complex like "y^3 + y^2 = x^3-x^2+3x"

	glm::mat4* pointMatrices = new glm::mat4[number_of_points];// stores function points

	std::string test{}; // for manual function testing

	Function(std::string fun,App_info info);
	void CreateBuffers();
	void ModifyInstances();
	bool CheckFunction();
	void CalculateFunction();
	void Draw();

	//RNP
	void SimplifyFunction();
	void ToRPN();
	float CalculateRPN(float x);
	float solve(int Type[], float Value[], int size);


	~Function();
};


void GetFunctionString(GLFWwindow* window, std::string* function, bool* finished);

// General
#define NUMBER 1
#define VARIABLE 2
#define OPERATOR 3

// RPN - one variale operators
#define SIN 101
#define COS 102
#define TAN 103
#define COT 104

// RPN - two variable operators

#define ADDITION 201
#define SUBSTRACTION 202
#define MULTIPLICATION 203
#define DIVISION 204
#define EXPONENTIATION 205


// Basic string to number
#define BRACKET_OPEN 10
#define BRACKET_CLOSE 11