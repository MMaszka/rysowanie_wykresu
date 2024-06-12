#include "graph.h"

double ZOOM = 1;
Graph::Graph() :Camera_controller(16.0f / 9.0f){
	window = std::make_unique<Window>();
	FunShader = new Shader("function.vs", "function.fs");
	zoom = &ZOOM;
	glfwSetScrollCallback(window->window, scroll_callback);
	AddNewFunction("aa");

	function[0]->zoom = zoom;
	function[0]->CreateBuffers();
	function[0]->CalculateFunction(function[0]->function[0]);
	function[0]->ModifyInstances();

	FunShader->setMat4("view", Camera_controller.Camera.view);
	FunShader->setMat4("projection", Camera_controller.Camera.projection);
}

void Graph::Run(){
	glEnable(GL_DEPTH_TEST);
	while (!glfwWindowShouldClose(window->window)) {
		float time = (float)glfwGetTime();
		float timestep = time - last_frame_time;
		last_frame_time = time;
	
		glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		FunShader->use();
		function[0]->Draw();


		MouseDisplacement();

		glfwSwapInterval(1);
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
		position += glm::vec3(((mouse_last_posX - xpos) / ZOOM), ((ypos - mouse_last_posY)  / ZOOM), 0.0f);
	}

	mouse_last_posX = xpos;
	mouse_last_posY = ypos;
}

void Graph::AddNewFunction(std::string fun) {
	function.push_back(new Function(fun));
	function[0]->zoom = this->zoom;
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
	ZOOM += yoffset;
}