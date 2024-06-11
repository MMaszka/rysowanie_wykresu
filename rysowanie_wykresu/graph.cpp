#include "graph.h"
double ZOOM = 1;
Graph::Graph():Camera_controller(16.0f/9.0f){
	window = std::make_unique<Window>();
	glfwSetScrollCallback(window->window, scroll_callback);
}

void Graph::Run(){
	glEnable(GL_DEPTH_TEST);
	while (!glfwWindowShouldClose(window->window)) {
		float time = (float)glfwGetTime();
		float timestep = time - last_frame_time;
		last_frame_time = time;
	
		glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

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
	std::cout << position.x<<"   " << position.y << "\n";

}
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
	ZOOM += yoffset;
	std::cout << ZOOM << "\n";
}