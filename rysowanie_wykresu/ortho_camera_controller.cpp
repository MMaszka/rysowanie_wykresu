#include "ortho_camera_controller.h"

Ortho_camera_controller::Ortho_camera_controller(float Aspect_ratio)
	: aspect_ratio(Aspect_ratio), Camera_bounds({ -aspect_ratio * zoom, aspect_ratio * zoom, -zoom, zoom }), Camera(Camera_bounds.left, Camera_bounds.right, Camera_bounds.top, Camera_bounds.bottom)
{
}
void Ortho_camera_controller::OnUpdate() {

}