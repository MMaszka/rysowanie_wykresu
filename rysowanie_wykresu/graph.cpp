#include "graph.h"

double ZOOM = -60;
Graph::Graph() :Camera_controller(12.0f / 9.0f,app_info),window(std::make_unique<Window>()){
	FunShader = new Shader("function.vs", "function.fs");

	app_info = window->app_info;// pass basic app information
	app_info.zoom = &ZOOM;
	Camera_controller.app_info = app_info;
	axis.app_info = app_info;

	glfwSetScrollCallback(window->window, scroll_callback);

	FunShader->use();
	FunShader->setMat4("view", Camera_controller.Camera.view);
	FunShader->setMat4("projection", Camera_controller.Camera.projection);

	
}

void Graph::Run(){

	glfwSwapInterval(1);// fps limit 
	bool typing = false;

	std::string StrFunction;
	std::thread th1(GetFunctionString, window->window, &StrFunction, &typing);

	//random
	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<std::mt19937::result_type> rand(1,64);

	while (!glfwWindowShouldClose(window->window)) { // main window loop
		float time = (float)glfwGetTime();
		float timestep = time - last_frame_time;
		last_frame_time = time;

		glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		MouseDisplacement();

		// creating new function
		if (typing == true) {
			typing = false;
			AddNewFunction(StrFunction, app_info);

			if (function[function.size() - 1]->IsCorrect == false)function.pop_back();

			if (function.size() != 0) {
				function[function.size() - 1]->position = position; // to optimalize!
				function[function.size() - 1]->CalculateFunction();
				function[function.size() - 1]->ModifyInstances();
				//random color from range 0.625 to 1
				if (IsSpecial == true) function[function.size() - 1]->is_special = true;
				float red = 0.75f + rand(rng) / 256.0f;
				float green = 0.75f + rand(rng) / 256.0f;
				float blue = 0.75f + rand(rng) / 256.0f;
				if (rand(rng) > 31)red -= 0.5;
				if (rand(rng) > 31)green -= 0.5;
				if (rand(rng) > 31)blue -= 0.5;

				function[function.size() - 1]->ChangeColor(glm::vec3(red, green, blue));

			}
		}
		if (Remove == true&& function.size()>0) {
			function.pop_back();
			Remove = false;
		}

		// - Axis
		axis.cam_pos = -position * float(app_info.GetZoom()); 
		axis.OnUpdate();
		axis.Draw();

		// - Functions
		FunShader->use();
		// multithreading can be implemented here
			if (last_position != position) { // position is also changed while zooming
				for (int i = 0; i < function.size(); i++) {
					
					function[i]->position = position;
					function[i]->CalculateFunction();
					function[i]->ModifyInstances();
					
				}
			}
		last_position = position;


		for (int i = 0; i < function.size(); i++) {
			if (function[i]->is_special == true) {
				function[i]->ChangeColor(glm::vec3(0.5f+cos(time*2+i/2.0f)/2, 0.5f + cos(time*2+2+i/2.0f) / 2, 0.5f + cos(time*2-2+i/2.0f) / 2));
			}
			FunShader->setVec3("color", function[i]->color);
			function[i]->Draw();
		}
		window->OnResize();
		Camera_controller.OnUpdate();
		FunShader->setMat4("projection", Camera_controller.Camera.projection);

		glfwSwapBuffers(window->window);
		glfwPollEvents();
	
	};

	th1.join();
	glfwTerminate();
}


void Graph::MouseDisplacement() {
	double xpos, ypos;
	int leftState = glfwGetMouseButton(window->window, GLFW_MOUSE_BUTTON_LEFT);
	glfwGetCursorPos(window->window, &xpos, &ypos);
	if (leftState == GLFW_PRESS) {
		position -= glm::vec3(
			((mouse_last_posX - xpos) / (*app_info.height / 2 * app_info.GetZoom())),
			((ypos - mouse_last_posY) / (*app_info.height / 2 * app_info.GetZoom())),
			0.0f);
	}

	mouse_last_posX = xpos;
	mouse_last_posY = ypos;

	// change camera position based on mouse position on mouse scroll
	OnZoomChange(glm::vec3(*app_info.width/2-xpos, ypos-*app_info.height/2, 0.0)); 
}

void Graph::AddNewFunction(std::string fun,App_info info) {
	function.push_back(new Function(fun,info));
}
void Graph::OnZoomChange(glm::vec3 mousePos) {

	if (lastZoom != *app_info.zoom)position += (mousePos / float(app_info.GetZoom()) / 10000.0f) * float(*app_info.zoom - lastZoom);
	lastZoom = *app_info.zoom;
}
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
	ZOOM += yoffset;
}