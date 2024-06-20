#include "function.h"
#include "graph.h"
#include <iostream>
#include <string>
#include <regex>
#include <algorithm>

Function::Function(std::string fun, App_info info):app_info(info){
	test = fun;
	
	if (!CheckFunction(fun)) {
		function funString(fun);
		IsCorrect = true;
		functions.push_back(fun);
		glGenBuffers(1, &buffer);
		glPointSize(2.5f);
		CreateBuffers();
		CalculateFunction(functions[0]);
		ModifyInstances();

	}
	else {
		std::cout << "Function did not pass check test\n";
	}
}

// --CHECK FUNCTION


// letters in the input
bool containsInvalidLetters(const std::string& str) {
	std::regex valid_chars(R"((\d+|[xyz]|\+|\-|\*|\/|\^|\(|\)|\s|=|sin|cos|tan|log|sqrt|[\d.]+)+)");
	return !std::regex_match(str, valid_chars);
}

// double symbols or multiple assignments
bool containsDoubleSymbolsOrMultipleAssignments(const std::string& str) {
	std::regex double_symbols_or_multiple_assignments(R"((\+\+|--|==|\*\*|//|\^\^|\(\()|(?:[xyz]=.*[xyz]=))");
	return std::regex_search(str, double_symbols_or_multiple_assignments);
}

// Check for invalid function calls
bool containsInvalidFunctionCalls(const std::string& str) {
	std::regex function_calls(R"((sin|cos|tan|log|sqrt)\([xyz\d\+\-\*\/\^\(\)]+\))");
	std::smatch match;
	std::string temp_str = str;
	while (std::regex_search(temp_str, match, function_calls)) {
		temp_str = match.suffix().str();
	}
	return temp_str.find("sin") != std::string::npos || temp_str.find("cos") != std::string::npos ||
		temp_str.find("tan") != std::string::npos || temp_str.find("log") != std::string::npos ||
		temp_str.find("sqrt") != std::string::npos;
}

// Check for invalid operator sequences
bool containsInvalidOperatorSequences(const std::string& str) {
	std::regex invalid_operator_sequences(R"((\*/|/\*|\*\*|//|\^\^|\+\*|\+\-|\+\^|\+\+|\*\+|\*/|\*^|-\*|-\+|-\/|-\^|\/\+|\/\*|\/\-|\/\^|\^\+|\^\*|\^\/|\^\-|\*\(|\/\(|\+\())");
	return std::regex_search(str, invalid_operator_sequences);
}

bool Function::CheckFunction(std::string fun) {

	

    std::string str=fun;

    // Check for letters
    if (containsInvalidLetters(str)) {
        std::cout << "Error." << std::endl;
        return 1;
    }

    // Check for double symbols or multiple assignments
    if (containsDoubleSymbolsOrMultipleAssignments(str)) {
        std::cout << "Error: Double symbols or multiple assignments." << std::endl;
        return 1;
    }

    // Check for invalid function calls
    if (containsInvalidFunctionCalls(str)) {
        std::cout << "Error: Invalid function call." << std::endl;
        return 1;
    }

    // Check for invalid operator sequences
    if (containsInvalidOperatorSequences(str)) {
        std::cout << "Error: Invalid operator sequence." << std::endl;
        return 1;
    }

    // Remove spaces
    str.erase(std::remove(str.begin(), str.end(), ' '), str.end());

    // Check for parentheses
    int parentheses_count = 0;
    for (char ch : str) {
        if (ch == '(') {
            parentheses_count++;
        } else if (ch == ')') {
            parentheses_count--;
        }
        if (parentheses_count < 0) {
            std::cout << "Error: Mismatched parentheses." << std::endl;
            return 1;
        }
    }
    if (parentheses_count > 0) {
        std::cout << "Error: Mismatched parentheses." << std::endl;
        return 1;
    }

    return 0;
}


void Function::CalculateFunction(std::string fun) {
	double y{}, x{};
	int point_number = 0;
	double interval = 1.0 / number_of_points; // distance between points
	for (int i = -number_of_points / 2; i < number_of_points / 2; i++) {
		glm::mat4 point = glm::mat4(1.0f);

		x = (i * (*app_info.width / float(*app_info.height)) * 2 / app_info.GetZoom() - position.x * number_of_points) * interval; // caluculate x position - depends on camera position and zoom
		if (test == "1") y = ((x)*sin(1 / (x)));
		else if (test == "2") y = x;
		else if (test == "3") y = x * x;
		else if (test == "4") y = x * x;
		else y = 0;

		point = glm::translate(point, glm::vec3(
			(x  + position.x) * app_info.GetZoom()+0.5,
			(y  + position.y) * app_info.GetZoom(),
			0.0f));
		pointMatrices[point_number++] = point; // put y into instance matrix
	}

}


void Function::CreateBuffers() {

	glGenVertexArrays(1, &VAO);// gen buffers
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);// buffer vertices
	glBufferData(GL_ARRAY_BUFFER, vertices_size, &vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);// buffer indices
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices_size, &indices, GL_STATIC_DRAW);



	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), 0);// set position in location 0

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), reinterpret_cast<void*>(3 * sizeof(float)));// set color in location 1


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
	delete[] pointMatrices;
}

void GetFunctionString(GLFWwindow* window, std::string* function, bool* finished) {
	while (!glfwWindowShouldClose(window)) {
		if (glfwGetKey(window, GLFW_KEY_SPACE)) {
			std::cout << "wprowadz funkcje:";
			std::cin >> *function;
			*finished = true;
		}
	}
};
