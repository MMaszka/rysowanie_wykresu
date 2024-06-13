#include "graph.h"

double ZOOM = 1;
Graph::Graph() :Camera_controller(12.0f / 9.0f),window(std::make_unique<Window>()){
	FunShader = new Shader("function.vs", "function.fs");

	app_info = window->app_info;
	app_info.zoom = &ZOOM;

	glfwSetScrollCallback(window->window, scroll_callback);
	AddNewFunction("aa",app_info);

	FunShader->use();
	FunShader->setMat4("view", Camera_controller.Camera.view);
	FunShader->setMat4("projection", Camera_controller.Camera.projection);
	
}

void Graph::Run(){
	//glEnable(GL_DEPTH_TEST);
	glfwSwapInterval(1);

	while (!glfwWindowShouldClose(window->window)) {
		float time = (float)glfwGetTime();
		float timestep = time - last_frame_time;
		last_frame_time = time;

		glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		MouseDisplacement();

		axis.Draw();

		FunShader->use();
		function[0]->position = position;
		function[0]->CalculateFunction(function[0]->function[0]);
		function[0]->ModifyInstances();
		function[0]->Draw();

		

		


		
		glfwSwapBuffers(window->window);
		glfwPollEvents();
	};
	glfwTerminate();
}


void Graph::MouseDisplacement() {
	double xpos, ypos;
	int leftState = glfwGetMouseButton(window->window, GLFW_MOUSE_BUTTON_LEFT);
	glfwGetCursorPos(window->window, &xpos, &ypos);
	if (leftState == GLFW_PRESS) {
		position -= glm::vec3(((mouse_last_posX - xpos) / (*app_info.height/2)), ((ypos - mouse_last_posY)  / (*app_info.height/2)), 0.0f);
	}

	mouse_last_posX = xpos;
	mouse_last_posY = ypos;
}

void Graph::AddNewFunction(std::string fun,App_info info) {
	function.push_back(new Function(fun,info));
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
	ZOOM += yoffset;
}