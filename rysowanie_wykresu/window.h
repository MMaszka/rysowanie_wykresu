#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>


#include <iostream>
class Window
{	
	
public:
	unsigned int width = 1200, height = 900;
	Window();
	void OnUpdate();
	void Init();
	GLFWwindow* window;

};