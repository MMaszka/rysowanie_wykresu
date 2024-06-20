#pragma once
#include "window.h"
#include "function.h"
#include "axis.h"
#include "ortho_camera_controller.h"
#include "shader.h"


class Graph {
	Ortho_camera_controller Camera_controller;
	Shader* FunShader; // shader for drawing points (function)
public:
	glm::vec3 position{};
	glm::vec3 last_position{};

	Graph();
	void Run();
	bool running=true;
	float last_frame_time;

	App_info app_info=App_info(0,0,0);

	std::unique_ptr<Window> window;
	float mouse_last_posX, mouse_last_posY;
	void MouseDisplacement();
	double lastZoom{ 1 };
	void OnZoomChange(glm::vec3 mousePos);

	std::vector <Function*> function;
	void AddNewFunction(std::string fun,App_info info);

	void EditFunction(int ID);
	
	Axis axis;

};

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);