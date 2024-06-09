#pragma once
#include "window.h"

class Graph {
public:
	Graph();
	void Run();
	bool running=true;
	float last_frame_time;
	std::unique_ptr<Window> window{};
};