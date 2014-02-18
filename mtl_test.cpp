#include "mtl.h"

#include <iostream>

using std::cin;
using std::cout;

int main(void)
{
	MTL::DO_Init();
	MTL::DO_load_substances();
	MTL::DO_Test();
	cout << MTL::GET_count_bodies();
	MTL::SET_environment_parameters("air", 30.0);
	int body_number = MTL::DO_add_body("test_body", 0.0, 0.0, 0.0, 0.1, 0.1, 0.1, "water", -10.0, true);
	MTL::DO_body_interaction_with_environment(body_number);
	MTL::DO_body_interaction_inside(body_number);
	cout << MTL::GET_count_bodies();
	return 0;
}
