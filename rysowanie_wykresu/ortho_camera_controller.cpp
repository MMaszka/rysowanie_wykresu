#include "ortho_camera_controller.h"

Ortho_camera_controller::Ortho_camera_controller(float Aspect_ratio)
	: aspect_ratio(Aspect_ratio), Camera_bounds({ -aspect_ratio * zoom, aspect_ratio * zoom, -zoom, zoom }), Camera(-aspect_ratio * zoom, aspect_ratio* zoom, -zoom, zoom)
{

}
void Ortho_camera_controller::OnUpdate() {

}