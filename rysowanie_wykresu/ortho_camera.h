#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <iostream>

class Ortho_camera {
public:
	Ortho_camera(float left, float right, float top, float bottom);
	void SetProjection(float left, float right, float top, float bottom);
	void RecalculateViewMatrix();
	glm::vec3 position{0.0f,0.0f,0.0f};
	glm::mat4 projection;
	glm::mat4 view;
	glm::mat4 view_projection;


};