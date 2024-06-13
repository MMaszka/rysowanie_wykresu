#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>
#include <string>
#include <vector>

#include "shader.h"


class Function {
private:
	float vertices[6]
	{	-0.5f, -0.5f, 0.0f,		1.0f, 1.0f, 1.0f 
	
	};
	unsigned int indices[1]{ 0 };
	int vertices_size{6}, indices_size{1};

	unsigned int VAO{}, VBO{}, EBO{}, sizeEBO{}, sizeVAO{}, buffer{};

	int number_of_points = 10000; // number of points per function

public:
	
	std::vector <int*> function;
	double* zoom{};
	glm::mat4* pointMatrices = new glm::mat4[number_of_points];
	Function(std::string fun);
	void CreateBuffers();
	void ModifyInstances();
	bool CheckFunction(std::string fun);
	void BreakDownFunction(std::string fun);
	void CalculateFunction(int* fun);
	void Draw();


	~Function();
};