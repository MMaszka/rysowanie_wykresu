#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>


#include <iostream>
class Window
{	
	unsigned int width=1200, height=900;
public:
	Window();
	void OnUpdate();
	void Init();
	GLFWwindow* window;

};