#include "function.h"
#include "graph.h"
#include <iostream>
#include <string>
#include <regex>
#include <algorithm>

Operators operators;

Function::Function(std::string fun, App_info info):
	app_info(info),
	SimplifiedType(new int[fun.size()] {}),
	SimplifiedValue(new float[fun.size()] {}),
	RPNType(new int[fun.size()] {}),
	RPNValue(new float[fun.size()] {}),
	functionString(fun) 
{
	test = fun;
	
	if (1) {
		IsCorrect = true;
		functions.push_back(fun);
		glGenBuffers(1, &buffer);
		glPointSize(2.5f);
		CreateBuffers();

		SimplifyFunction();
		ToRPN();

		CalculateFunction();
		

		ModifyInstances();

	}
	else {
		std::cout << "Function did not pass check test\n";
	}
}

// --CHECK FUNCTION


// letters in the input
bool containsInvalidLetters(const std::string& str) {
	std::regex valid_chars(R"((\d+|[xyz]|\+|\-|\*|\/|\^|\(|\)|\s||sin|cos|tan|log|sqrt|[\d.]+)+)");
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

bool Function::CheckFunction() {

	

    std::string str=functionString;

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


void Function::CalculateFunction() {

	auto start = std::chrono::high_resolution_clock::now();
	auto stop = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds> (stop - start);
	double totalTime = duration.count();
	auto totalTime2 = duration.count();

	double y{}, x{};
	int point_number = 0;
	double interval = 1.0 / number_of_points; // distance between points

	std::vector<int> intarr(number_of_points);
	std::iota(intarr.begin(), intarr.end(), -number_of_points/2);

	glm::mat4 point = glm::mat4(1.0f);

	//--------------TESTING AREA 
	///*
	
	start = std::chrono::high_resolution_clock::now();
	for (auto& i : intarr) {
		auto start2 = std::chrono::high_resolution_clock::now();
		int a = i - number_of_points / 2;
		//point = glm::mat4(1.0f);
		auto stop2 = std::chrono::high_resolution_clock::now();
		auto duration2 = std::chrono::duration_cast<std::chrono::microseconds> (stop2 - start2);
		totalTime2 += duration2.count();
	};

	stop = std::chrono::high_resolution_clock::now();
	duration = std::chrono::duration_cast<std::chrono::microseconds> (stop - start);
	totalTime += duration.count();
	std::cout << "\nTIME-empty( ms ) :" << totalTime / 1000.0f;
	std::cout << "\nTIME-empty-inside( ms ) :" << totalTime2 / 1000.0f;

	totalTime2 = 0;
	//*/
	//----------------------
	
	start = std::chrono::high_resolution_clock::now();
	
	for (auto& i : intarr) {
		auto start2 = std::chrono::high_resolution_clock::now();

		point = glm::mat4(1.0f);
		x = (i * (*app_info.width / float(*app_info.height)) * 2 / app_info.GetZoom() - position.x * number_of_points) * interval; // caluculate x position - depends on camera position and zoom
		y = CalculateRPN(x);
		point = glm::translate(point, glm::vec3(
			(x  + position.x) * app_info.GetZoom()+0.5,
			(y  + position.y) * app_info.GetZoom(),
			0.0f));
		pointMatrices[point_number++] = point; // put y into instance matrix

		auto stop2 = std::chrono::high_resolution_clock::now();
		auto duration2 = std::chrono::duration_cast<std::chrono::microseconds> (stop2 - start2);
		totalTime2 += duration2.count();
	}

	stop = std::chrono::high_resolution_clock::now();
	
	duration = std::chrono::duration_cast<std::chrono::microseconds> (stop - start);
	
	totalTime += duration.count();
	

	
	

	system("cls");
	std::cout << "\nTIME( ms ) :" << totalTime / 1000.0f;
	std::cout << "\nTIME_inside( ms ) :" << totalTime2 / 1000.0f;
	
	

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
	delete[] SimplifiedType;
	delete[] SimplifiedValue;
	delete[] RPNType;
	delete[] RPNValue;
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


//-----------------------------------------
//---		RPN RELATED CODE			---
//-----------------------------------------




void Function::SimplifyFunction() {
	std::string function = functionString;

	// convert string to values
	bool isANumber = false;

	int j{};
	for (int i = 0; i < function.size(); i++, j++) {
		if (function[i] >= 48 && function[i] <= 57) { // check if char is a number
			int numberLength = {};
			do {
				numberLength++;
			} while (function[i + numberLength] >= 48 && function[i + numberLength] <= 57); // find number length
			isANumber = true;
			SimplifiedValue[j] = std::stof(function.substr(i, i + numberLength)); // convert string to number
			SimplifiedType[j] = NUMBER;
			i += numberLength - 1;

			// -- for debugging ->
			//std::cout << "number at position "<<j+1<<" is "<<numberLength<<" digit long\n"; 
		}
		else if (function[i] == '(') {
			SimplifiedValue[j] = 0;
			SimplifiedType[j] = BRACKET_OPEN;
		}
		else if (function[i] == ')') {
			SimplifiedValue[j] = 0;
			SimplifiedType[j] = BRACKET_CLOSE;
		}
		else if (function[i] == 'x') {
			SimplifiedValue[j] = 0;
			SimplifiedType[j] = VARIABLE;
		}
		else {
			int length{}; // length of operator
			int maxLength{}; // length of the longest found operator -- can be optimalized
			int foundAt{};
			do {
				length++;
				std::string subStr = "|" + function.substr(i, length) + "|"; // get operator substring
				std::string::size_type n = operators.allowed.find(subStr); // find operator in allowed operators
				if (std::string::npos != n) { // if operator exists assign 
					foundAt = n;
					maxLength = length;
					break;
				}
			} while (length < operators.maxAllowedLength);
			int operatorID{};
			if (foundAt < operators.semicolonPosition) {//find group which operator belongs 
				for (char c : operators.allowed.substr(0, foundAt + 1)) {
					if (c == '|')operatorID++; // find operator ID - for more info check #define's in file : 
				}
				SimplifiedValue[j] = operatorID + 100; // group one 
			}
			else {
				for (char c : operators.allowed.substr(operators.semicolonPosition, foundAt + 1 - operators.semicolonPosition)) { // find in group two
					if (c == '|')operatorID++;
				}
				SimplifiedValue[j] = operatorID + 200; // group two
			}

			SimplifiedType[j] = OPERATOR;
			i += length - 1;

		}
	}
	RPNLength = j;
	for (int i = 0; i <= j; i++) { // remove excesive brackets
		if (SimplifiedType[i] == NUMBER || SimplifiedType[i] == VARIABLE) {
			if (SimplifiedType[i - 1] == BRACKET_OPEN && SimplifiedType[i + 1] == BRACKET_CLOSE) {
				SimplifiedType[i - 1] = 0;
				SimplifiedType[i + 1] = 0;
				//std::cout << "removing brackets\n";
				RPNLength--;
			}
		}
	}
	for (int i = 0, len{}; i <= j; i++) { // remove zeros
		if (SimplifiedType[i] != 0) {
			SimplifiedType[len] = SimplifiedType[i];
			SimplifiedValue[len] = SimplifiedValue[i];
			len++;
		}
	}

	for (int i = 0; i < j; i++) {
		if (SimplifiedType[i] == BRACKET_CLOSE || SimplifiedType[i] == BRACKET_OPEN)RPNLength--;
	}
	SimplifiedLength = j;
	//std::cout << "Function Length: " << RPNLength << "\n";
}

void Function::ToRPN() {


	int OperatorBufferSize = 1;
	for (int i{}, j = 1; i <= SimplifiedLength; i++) {//count max bracket count
		if (SimplifiedType[i] == BRACKET_OPEN)j++;
		else if (SimplifiedType[i] == BRACKET_CLOSE)j--;
		OperatorBufferSize = std::max(OperatorBufferSize, j);
	}

	int* OperatorBuffer[4]{};
	OperatorBuffer[0] = new int[OperatorBufferSize] {};
	OperatorBuffer[1] = new int[OperatorBufferSize] {};
	OperatorBuffer[2] = new int[OperatorBufferSize] {};
	OperatorBuffer[3] = new int[OperatorBufferSize] {};

	int* OperatorPosition[4]{};
	OperatorPosition[0] = new int[OperatorBufferSize] {};
	OperatorPosition[1] = new int[OperatorBufferSize] {};
	OperatorPosition[2] = new int[OperatorBufferSize] {};
	OperatorPosition[3] = new int[OperatorBufferSize] {};

	int bufferLevel{};
	int readyToOutput = 0; // how many operators from buffer has to be saved
	bool outputValue = false; // output value on open bracket
	bool stop = false;
	//-----------------------
	// --- function converter
	for (int i{}, RPNSize{}; i < SimplifiedLength + 1 && !stop; i++) {
		//std::cout << "\nloop number:" << i << "\n";



		// -------------------------------
		// --- Saving oberators to buffers 

		if (SimplifiedType[i] == OPERATOR) {

			for (int j = 0; j < 4; j++) { // check every buffer if is empty
				if (OperatorBuffer[j][bufferLevel] == 0) {
					OperatorPosition[j][bufferLevel] = i; // save operator position

					// group one starts at 201, so 199 has to be substracted.
					// it is also devided by two to convert it to priority -> (+,-):1, (*,/):2, (^):3
					if (SimplifiedValue[i] > 200) {
						OperatorBuffer[j][bufferLevel] = (SimplifiedValue[i] - 199) / 2;
						//std::cout << "save operator from group one\n";
					}
					//group two has highest priority, so it always has priority 4.
					else {
						OperatorBuffer[j][bufferLevel] = 4;
						//std::cout << "save operator from group two\n";
					}
					break;
				}
				else {
					//check if last operator in buffer has lower priority. (for group one)
					if (SimplifiedValue[i] > 200 && OperatorBuffer[j][bufferLevel] < (SimplifiedValue[i] - 199) / 2) {
						continue;
					}
					//check if last operator in buffer has lower priority. (for group two)
					else if (SimplifiedValue[i] < 200 && OperatorBuffer[j][bufferLevel] < 4) {
						continue;
					}

					// if last operator has the same priority or higher - check previous operator too
					// number of saved operators depends on previously stored operators and currently checked one
					else {

						//check if penultimate operator in buffer has lower priority. (for group two)
						if (j > 0 && SimplifiedValue[i] > 200 && OperatorBuffer[j - 1][bufferLevel] < (SimplifiedValue[i] - 199) / 2) {
							readyToOutput = 1;//save one operator
							//std::cout << "only one operator is ready to be saved\n";
						}
						//check if penultimate operator in buffer has lower priority. (for group two)
						else if (j > 0 && SimplifiedValue[i] < 200 && OperatorBuffer[j - 1][bufferLevel] < 4) {
							readyToOutput = 1;
							//std::cout << "only one operator is ready to be saved\n";
						}


						//check if befere the penultimate operator in buffer has lower priority. (for group two)
						else if (j > 1 && SimplifiedValue[i] > 200 && OperatorBuffer[j - 2][bufferLevel] < (SimplifiedValue[i] - 199) / 2) {
							readyToOutput = 2;//save two operators
							//std::cout << "two operator is ready to be saved\n";
						}
						//check if befere the penultimate operator in buffer has lower priority. (for group two)
						else if (j > 1 && SimplifiedValue[i] < 200 && OperatorBuffer[j - 2][bufferLevel] < 4) {
							readyToOutput = 2;
							//std::cout << "two operator is ready to be saved\n";
						}

						else {
							readyToOutput = 4;// save everything 
							//std::cout << "every operator is ready to be saved\n";
						}
						i--;
						//std::cout << "exit\n";
						break;
					}
				}
			}
		}
		else if (SimplifiedType[i] == BRACKET_OPEN) {
			if (RPNType[RPNSize] != 0)RPNSize++;
			outputValue = true;
		}
		else if (SimplifiedType[i] == BRACKET_CLOSE) {
			readyToOutput = 4;

		}



		// ----------------------------------
		// --- Saving values and types to RPN 
		if (i + 1 == SimplifiedLength) readyToOutput = 4;
		if (readyToOutput > 0 || outputValue == true) {
			int length{};
			for (int j = 0; j < 4; j++) { // save every buffered operator's arguments
				if (OperatorBuffer[j][bufferLevel] == 0)continue; // stop loop on empty buffer
				if (RPNType[RPNSize] == 0) { // save left algument
					if (SimplifiedType[OperatorPosition[j][bufferLevel] - 1] == NUMBER ||
						SimplifiedType[OperatorPosition[j][bufferLevel] - 1] == VARIABLE) { // check if Simplified function was cleard
						RPNType[RPNSize] = SimplifiedType[OperatorPosition[j][bufferLevel] - 1];
						RPNValue[RPNSize] = SimplifiedValue[OperatorPosition[j][bufferLevel] - 1];

						SimplifiedType[OperatorPosition[j][bufferLevel] - 1] = 0; // clear Simplified function
						SimplifiedValue[OperatorPosition[j][bufferLevel] - 1] = 0;
						//std::cout << "left  argument (" << RPNValue[RPNSize] << ") saved in:" << RPNSize << "\n";
						if (outputValue == true)RPNSize++;
					}

				}
				if (bufferLevel < 0)bufferLevel++; // for some raeson bufferLevel=-1 at the last iteration
				if (SimplifiedType[OperatorPosition[j][bufferLevel] + 1] == NUMBER ||
					SimplifiedType[OperatorPosition[j][bufferLevel] + 1] == VARIABLE) {// check if Simplified function was cleard 

					if (RPNType[RPNSize] != 0)RPNSize++;


					//save right argument
					RPNType[RPNSize] = SimplifiedType[OperatorPosition[j][bufferLevel] + 1];
					RPNValue[RPNSize] = SimplifiedValue[OperatorPosition[j][bufferLevel] + 1];

					SimplifiedType[OperatorPosition[j][bufferLevel] + 1] = 0; // clear Simplified function
					SimplifiedValue[OperatorPosition[j][bufferLevel] + 1] = 0;

					//std::cout << "right argument (" << RPNValue[RPNSize] << ") saved in:" << RPNSize << "\n";
					length++;
				}
			}

			// save buffered operator (depends on readyToOutput)
			for (int j = 3, zeroBuffers{}; j >= 4 - readyToOutput - zeroBuffers && j >= 0; j--) {
				if (OperatorBuffer[j][bufferLevel] == 0) { // skip empty buffers 
					zeroBuffers++; // add new loop
					continue;
				}
				RPNSize++;
				RPNType[RPNSize] = SimplifiedType[OperatorPosition[j][bufferLevel]];
				RPNValue[RPNSize] = SimplifiedValue[OperatorPosition[j][bufferLevel]];
				//std::cout << "opearator    (" << RPNValue[RPNSize] << ") saved in:" << RPNSize << "\n";
			}

			// zero buffers from this bracket level (depends on readyToOutput)
			for (int j = 3; readyToOutput > 0 && j >= 0; j--) {
				if (OperatorBuffer[j][bufferLevel] == 0)continue;
				//std::cout << "cleared " << OperatorBuffer[j][bufferLevel] << " from position " << OperatorPosition[j][bufferLevel] << '\n';
				OperatorBuffer[j][bufferLevel] = 0;
				OperatorPosition[j][bufferLevel] = 0;
				readyToOutput--;
			}
			readyToOutput = 0;
		}

		/*
		std::cout << "current buffer: " << bufferLevel << " stores : ";
		for (int j = 0; j < 4; j++) {
			if (OperatorBuffer[j][bufferLevel] != 0)std::cout << SimplifiedValue[OperatorPosition[j][bufferLevel]] << " ";
		}
		std::cout << '\n';
		*/

		if (SimplifiedType[i] == BRACKET_CLOSE) {
			SimplifiedType[i] = 0;
			bufferLevel--;
		}
		if (SimplifiedType[i] == BRACKET_OPEN) {
			SimplifiedType[i] = 0;
			bufferLevel++;
		}
		outputValue == false;

		//std::cout << std::string(10, '-') << '\n';
		if (i == SimplifiedLength) { // save every operator on  last loop
			while (bufferLevel >= 0) {
				for (int j = 3; j >= 0; j--) {
					if (OperatorBuffer[j][bufferLevel] == 0) continue;
					RPNSize++;
					RPNType[RPNSize] = SimplifiedType[OperatorPosition[j][bufferLevel]];
					RPNValue[RPNSize] = SimplifiedValue[OperatorPosition[j][bufferLevel]];
					//std::cout << "opearator    (" << RPNValue[RPNSize] << ") saved in:" << RPNSize << "\n";
				}
				bufferLevel--;
			}

		}

	}

}


float Function::CalculateRPN(float x) {
	int size = RPNLength - 1;
	float y{};
	int numbers{};
	int* Type = new int[RPNLength] {};
	float* Value = new float[RPNLength] {};

	memcpy(Type, RPNType, (RPNLength + 1) * sizeof(int));
	memcpy(Value, RPNValue, (RPNLength + 1) * sizeof(float));

	for (int i = 0; i < size; i++) { // substitute the given value for x
		if (Type[i] == VARIABLE) {
			Type[i] = NUMBER;
			Value[i] = x;
		}
	}
	
	y = solve(Type, Value, RPNLength - 1);
	

	delete[] Type;
	delete[] Value;

	return y;
}
float Function::solve(int Type[], float Value[], int size) {
	float LeftArgument{};
	float RightArgument{};
	if (Value[size] > 200 && Type[size - 1] == OPERATOR) { // check group two
		int stepsDone{};
		int operatorRange{};
		for (int steps = 1; steps > 0; steps--) { // subdivide operation
			operatorRange--;
			if (Type[size - stepsDone - 1] == OPERATOR) {
				if (Type[size - stepsDone - 1] == OPERATOR && Value[size - stepsDone - 1] > 200) {
					steps += 2;
					operatorRange = 2;
				}
				else if (Type[size - stepsDone - 1] == OPERATOR && Value[size - stepsDone - 1] < 200) {
					steps++;
					operatorRange = 1;
				}
			}
			stepsDone++;
			//std::cout << "steps done: " << stepsDone << " and: " << steps << " still remaining\n";
		}
		RightArgument = solve(Type + size - stepsDone, Value + size - stepsDone, stepsDone - 1);
		if (Type[size - stepsDone - 1] == OPERATOR) {
			LeftArgument = solve(Type, Value, size - stepsDone - 1);
		}
		else {
			LeftArgument = Value[size - stepsDone + 1];
		}
	}
	else if (Value[size] > 200 && size > 2) {
		RightArgument = Value[size - 1];
		LeftArgument = solve(Type, Value, size - 2);
	}
	else if (Value[size] > 200 && size <= 2) {
		RightArgument = Value[size - 1];
		LeftArgument = Value[size - 2];
	}
	else if (Value[size] < 200 && Type[size - 1] == OPERATOR) { // check group one
		LeftArgument = solve(Type, Value, size - 1);
	}
	else if (Value[size] < 200) {
		LeftArgument = Value[size - 1];
	}
	else {
		std::cout << "ERROR\n";
	}

	float y{};
	switch (int(Value[size]))
	{
	case(ADDITION):
		y = LeftArgument + RightArgument;
		break;
	case(SUBSTRACTION):
		y = LeftArgument - RightArgument;
		break;
	case(MULTIPLICATION):
		y = LeftArgument * RightArgument;
		break;
	case(DIVISION):
		y = LeftArgument / RightArgument;
		break;
	case(EXPONENTIATION):
		y = powf(LeftArgument, RightArgument);
		break;
	case(SIN):
		y = sin(LeftArgument);
		break;

	default:
		break;
	}

	/*
	std::cout << "current equation size: " << size << " with y = " << y << " ( f(x) = ";
	for (int i{}; i <= size; i++)std::cout << Value[i] << " ";
	std::cout << " )\n";
	*/

	return y;
}
