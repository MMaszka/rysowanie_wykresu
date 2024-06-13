#include "ortho_camera.h"
#include <glm/gtc/matrix_transform.hpp>

Ortho_camera::Ortho_camera(float left, float right, float bottom, float top)
	: projection(glm::ortho(left, right, bottom, top, -10.0f, 10.0f)), view(1.0f)
{
	
	projection = glm::mat4(1.0f);
	projection = glm::ortho(left, right, bottom, top, -10.0f, 10.0f);
	view = glm::mat4(1.0f);
	view = glm::translate(view, glm::vec3(0.0f, 0.0f, -2.0f));
	view_projection = projection * view;
}

void Ortho_camera::SetProjection(float left, float right, float bottom, float top)
{
	projection = glm::ortho(left, right, bottom, top, -10.0f, 10.0f);
	view_projection = projection * view;
}
void Ortho_camera::RecalculateViewMatrix()
{
	glm::mat4 transform = glm::translate(glm::mat4(1.0f), position);
	view_projection = projection * view;
}