#include "function.h"
#include "graph.h"

Function::Function(std::string fun, App_info info):app_info(info){
	if (CheckFunction(fun)) {
		BreakDownFunction(fun);

	}
	else {
		std::cout << "Function did not pass check test";
	}
	glGenBuffers(1, &buffer);
	glPointSize(2.5f);
	CreateBuffers();
	CalculateFunction(function[0]);
	ModifyInstances();
}

bool Function::CheckFunction(std::string fun) {

	return true;
}

void Function::BreakDownFunction(std::string fun) {

	for (int i{}; i < 1; i++) {

		function.push_back(new int(10));

	}
}

void Function::CalculateFunction(int* fun) {
	double y{}, x{};
	int point_number = 0;
	double interval = 1.0 / number_of_points; // distance between points
	for (int i = 0; i < number_of_points; i++) {
		glm::mat4 point = glm::mat4(1.0f);
<<<<<<< HEAD
		x = (i*2*1.77-position.x*number_of_points-number_of_points)*interval; // caluculate x position - depends on camera position and zoom
		y = (x  * sin(1 /x )) ;
		//y = x*x*x;
		point = glm::translate(point, glm::vec3(x+position.x,y+position.y, 0.0f));
=======
		x = (i*(*app_info.width/ float(*app_info.height))*2 / app_info.GetZoom() - position.x * number_of_points) * interval; // caluculate x position - depends on camera position and zoom
		
		y = ((x) * sin(1 / (x)));

		//y = x*x*x;
		point = glm::translate(point, glm::vec3(
			(x  + position.x) * app_info.GetZoom()+0.5,
			(y  + position.y) * app_info.GetZoom(),
			0.0f));
>>>>>>> 38fda81def5fc158bd343a8363746b4e11f06388

		pointMatrices[point_number++] = point; // put y into instance matrix
	}

}


void Function::CreateBuffers() {

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices_size, &vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices_size, &indices, GL_STATIC_DRAW);



	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), 0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), reinterpret_cast<void*>(3 * sizeof(float)));


	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Function::ModifyInstances() {
	//modify mat4 in location 2

	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, number_of_points * sizeof(glm::mat4), pointMatrices, GL_STATIC_DRAW);
	glBindVertexArray(VAO);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), 0);
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), reinterpret_cast<void*>(sizeof(glm::vec4)));
	glEnableVertexAttribArray(4);
	glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), reinterpret_cast<void*>(2 * sizeof(glm::vec4)));
	glEnableVertexAttribArray(5);
	glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), reinterpret_cast<void*>(3 * sizeof(glm::vec4)));

	glVertexAttribDivisor(2, 1);
	glVertexAttribDivisor(3, 1);
	glVertexAttribDivisor(4, 1);
	glVertexAttribDivisor(5, 1);

	glBindVertexArray(0);
}

void Function::Draw() {

	glBindVertexArray(VAO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glDrawElementsInstanced(GL_POINTS, indices_size, GL_UNSIGNED_INT, 0, number_of_points);
}
Function::~Function() {
	for (int i{}; i < function.size(); i++) {
		delete function.at(i);
	}
	delete[] pointMatrices;
}
