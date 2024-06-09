#include "ortho_camera.h"
#include <glm/gtc/matrix_transform.hpp>

Ortho_camera::Ortho_camera(float left, float right, float top, float bottom)
	: projection(glm::ortho(left, right, bottom, top, -1.0f, 1.0f)), view(1.0f)
{
	view_projection = projection * view;
}

void Ortho_camera::SetProjection(float left, float right, float top, float bottom)
{
	projection = glm::ortho(left, right, top, bottom, -1.0f, 1.0f);
	view_projection = projection * view;
}
void Ortho_camera::RecalculateViewMatrix()
{
	glm::mat4 transform = glm::translate(glm::mat4(1.0f), position);
	view_projection = projection * view;
}