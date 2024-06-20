#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>
#include <string>
#include <vector>

#include "shader.h"
#include "window.h"
#include "input.h"
#include <thread>

class Function {
private:
	float vertices[6]{	-0.5f, -0.5f, 0.0f,	1.0f, 1.0f, 1.0f };// should be 0.0f,0.0f,0.0f --- to change... in future
	unsigned int indices[1]{ 0 };

	int vertices_size{6}, indices_size{1};
	unsigned int VAO{}, VBO{}, EBO{}, sizeEBO{}, sizeVAO{}, buffer{};
	int number_of_points = 20000; // number of points per function

public:
	App_info app_info;
	glm::vec3 position{};// cam position
	bool IsCorrect = false;

	std::vector <std::string> functions;// stores sub functions --- do we need this anymore?
	glm::mat4* pointMatrices = new glm::mat4[number_of_points];// stores function points

	std::string test{}; // for manual function testing

	Function(std::string fun,App_info info);
	void CreateBuffers();
	void ModifyInstances();
	bool CheckFunction(std::string fun);
	void CalculateFunction(std::string fun);
	void Draw();


	~Function();
};

void GetFunctionString(GLFWwindow* window, std::string* function, bool* finished);