#pragma once
#include "window.h"
#include "Shader.h"

class Axis {

	float vertices[12]{
		-1.0f, -1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		-1.0f, 1.0f, 0.0f
	};
	unsigned int indices[6]{
		0,1,2,
		0,3,2
	};

	int vertices_size{ 12 }, indices_size{ 6 };
	unsigned int VAO{}, VBO{}, EBO{};

public:
	App_info app_info = App_info{ 0,0,0 };
	Shader shader;
	glm::vec3 cam_pos{};
	Axis();
	void Draw();
	void CreateBuffers();
	void OnUpdate();

};