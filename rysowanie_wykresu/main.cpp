#include <iostream>
#include "graph.h"
#include "Lampa.h"

int main(){
	std::unique_ptr<Graph> app = std::make_unique<Graph>();

	app->Run();

	//test functions - Lampa
	//function f1("y = x");
	//function f2("y = x + 1");
	//function f3("y = 5x - 3");
	//function f4("y = 8x^2 + 4");
	//function f5("y = 11x^2 + 4x - 5");
	//function f6("y = 10x^3 / 4 + (2 / 5x)/(7/9x) - 3x^2 / 4x");
	//function f7("y = (100x^5 - 2) - 8x * (5x * 3)");
	//function f8("y = (10x^2 - 4)12x");
	//function f9("y = (1/5)/[(56 + 7^x) * (8x/5)/3x^2] + 8");
	//function f10("y = 24[(1/x)[(56 + 7^x)13 - x^2 * (8x/5 + 3)(6 - 3x^2)] + 8]");
	//function f11("f(x) = -(-(-(x^2+6)(5x + (-12-2)) + 4))-5");
	//function f12("y = [1.5 / 2.25x[2^x^2 - 3x^2(13 - 3x) + 5] - x^3/(3/15)/9] + 0.01"); // ostatni znak mno¿enia w z³ym miejscu przy zwrocie ONP
	//function f13("f(x) = PI^e * 2x + 6");
	//function f14("y = fact(x)");
	//function f15("y = exp(x)/15x");
	//function f16("y = ln(ln(x))");
	//function f17("y = root(3, x)");
	function f18("y = root(x/2, 1024)");
	function f18a("y = log(2, x)");
	function f18b("y = scn(3, 4x)");
	/*function f19("y = scn(x, x)");
	function f20("f(x) = sin(root(abs(x), lg(scn(3, x))))");
	function f21("f(x) = 4.5x/2(sin(1.5x + x^2) - root(x^3, 6561)) / arctg(cos(5/x^(3-log(15, x/2))))");*/

	return 0;
}