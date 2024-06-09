#include "graph.h"

Graph::Graph(){
	window = std::make_unique<Window>();
}

void Graph::Run(){
	glEnable(GL_DEPTH_TEST);
	while (!glfwWindowShouldClose(window->window)) {
		float time = (float)glfwGetTime();
		float timestep = time - last_frame_time;
		last_frame_time = time;
	
		glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);



		glfwSwapInterval(1);
		glfwSwapBuffers(window->window);
		glfwPollEvents();
	};
	glfwTerminate();
}