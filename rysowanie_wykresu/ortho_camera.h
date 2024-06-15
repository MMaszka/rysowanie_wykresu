#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <iostream>

class Ortho_camera {
public:
	Ortho_camera(float left, float right, float bottom, float top);
	void SetProjection(float left, float right, float bottom, float top);
	glm::vec3 position{0.0f,0.0f,0.0f};
	glm::mat4 projection{1};
	glm::mat4 view{1};


};