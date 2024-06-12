#pragma once
#include "window.h"
#include "function.h"
#include "ortho_camera_controller.h"
#include "shader.h"



class Graph {
	Ortho_camera_controller Camera_controller;
	Shader* FunShader; // shader for drawing points (function)
public:
	glm::vec3 position{};
	Graph();
	void Run();
	bool running=true;
	float last_frame_time;
	double* zoom{};
	std::unique_ptr<Window> window;
	float mouse_last_posX, mouse_last_posY;
	void MouseDisplacement();

	std::vector <Function*> function;
	void AddNewFunction(std::string fun);
	void EditFunction(int ID);
	
};

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);