#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>
#include <string>
#include <vector>

#include "shader.h"
#include "window.h"


class Function {
private:
	float vertices[6]{	-0.5f, -0.5f, 0.0f,	1.0f, 1.0f, 1.0f };
	unsigned int indices[1]{ 0 };

	int vertices_size{6}, indices_size{1};
	unsigned int VAO{}, VBO{}, EBO{}, sizeEBO{}, sizeVAO{}, buffer{};
	int number_of_points = 1000000; // number of points per function

public:
	App_info app_info;
	glm::vec3 position{};
	std::vector <int*> function;
	glm::mat4* pointMatrices = new glm::mat4[number_of_points];

	Function(std::string fun,App_info info);
	void CreateBuffers();
	void ModifyInstances();
	bool CheckFunction(std::string fun);
	void BreakDownFunction(std::string fun);
	void CalculateFunction(int* fun);
	void Draw();


	~Function();
};