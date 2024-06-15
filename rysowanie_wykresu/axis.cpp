#include "axis.h"

Axis::Axis():shader("axis.vs", "axis.fs") {
	CreateBuffers();
}
void Axis::Draw() {
	shader.use();
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

}


void Axis::CreateBuffers() {

	shader.use();
	glGenVertexArrays(1, &VAO); // gen buffers
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO); // bind buffer

	glBindBuffer(GL_ARRAY_BUFFER, VBO); // buffer verteices
	glBufferData(GL_ARRAY_BUFFER, 12 * sizeof(float), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO); // buffer indces
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(float), indices, GL_STATIC_DRAW);



	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0); // uniform in location 0


}
void Axis::OnUpdate() { // update shaders
	shader.use();
	shader.setInt("width", *app_info.width);
	shader.setInt("height", *app_info.height);
	shader.setFloat("Zoom", (65536-*app_info.zoom));
	shader.setVec3("cam_pos", cam_pos);
}