#pragma once
#include "window.h"
#include "ortho_camera_controller.h"

class Graph {
	Ortho_camera_controller Camera_controller;
public:
	glm::vec3 position{};
	Graph();
	void Run();
	bool running=true;
	float last_frame_time;

	std::unique_ptr<Window> window{};
	float mouse_last_posX, mouse_last_posY;
	void MouseDisplacement();
};

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);