#include "ortho_camera.h"
#include <glm/gtc/matrix_transform.hpp>

Ortho_camera::Ortho_camera(float left, float right, float bottom, float top)
	: projection(glm::ortho(left, right, bottom, top, -10.0f, 10.0f)), view(1.0f)
{
	
}

void Ortho_camera::SetProjection(float left, float right, float bottom, float top)// calculate projection
{
	projection = glm::ortho(left, right, bottom, top, -10.0f, 10.0f);
}