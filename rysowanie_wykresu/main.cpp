#include <iostream>
#include "graph.h"


int main(){
	std::unique_ptr<Graph> app = std::make_unique<Graph>();

	app->Run();
}