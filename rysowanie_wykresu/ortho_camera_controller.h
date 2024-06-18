#pragma once
#include "ortho_camera.h"
#include "window.h"

struct Ortho_camera_bounds {
	float left, right;
	float bottom, top;
};

class  Ortho_camera_controller {
	float aspect_ratio{1};
	float zoom=1;
	
public:
	App_info app_info;
	Ortho_camera Camera;
	Ortho_camera_bounds Camera_bounds;
	Ortho_camera_controller(float aspectRatio, App_info app_info);
	void OnUpdate();
	glm::vec3 camera_position{};
};