#pragma once
#include "ortho_camera.h"

struct Ortho_camera_bounds {
	float left{}, right{};
	float top{}, bottom{};
};

class  Ortho_camera_controller {
	float aspect_ratio{};
	float zoom=1;
	Ortho_camera Camera;
	
public:
	Ortho_camera_bounds Camera_bounds;
	Ortho_camera_controller(float aspectRatio);
	void OnUpdate();
	glm::vec3 camera_position{};
};