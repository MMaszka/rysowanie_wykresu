#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

struct App_info{

public:
	App_info(unsigned int* width, unsigned int* height, double* zoom) 
		:width(width),height(height),zoom(zoom)
	{
	};
	double GetZoom() {
		return pow(2,*zoom);
	};
	unsigned int* width{}, * height{};
	double* zoom{};
};



class Window
{	
	
public:
	
	unsigned int width = 1200, height = 900;
	double zoom=1;
	App_info app_info = App_info(&width, &height, &zoom);
	Window();
	void OnUpdate();
	void Init();
	GLFWwindow* window;

};