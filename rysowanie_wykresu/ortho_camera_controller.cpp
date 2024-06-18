#include "ortho_camera_controller.h"

Ortho_camera_controller::Ortho_camera_controller(float Aspect_ratio, App_info app_info)// asprct ratio, camera bounds, app info
	: aspect_ratio(Aspect_ratio), Camera_bounds({ -aspect_ratio * zoom, aspect_ratio * zoom, -zoom, zoom }), Camera(-aspect_ratio * zoom, aspect_ratio* zoom, -zoom, zoom), app_info(app_info)
{

}
void Ortho_camera_controller::OnUpdate() {// update camera
	aspect_ratio = *app_info.width / float(*app_info.height);
	Camera_bounds = Ortho_camera_bounds({ -aspect_ratio * zoom, aspect_ratio * zoom, -zoom, zoom });
	Camera = Ortho_camera({ -aspect_ratio * zoom, aspect_ratio * zoom, -zoom, zoom });
	Camera.SetProjection(Camera_bounds.left, Camera_bounds.right, Camera_bounds.bottom, Camera_bounds.top); // recalculate projection
}