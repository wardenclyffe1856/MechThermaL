#include "mtl.h"

#include <iostream>

using std::cout;
using std::endl;

MTL::MainWorker* MW;

void MTL::DO_test(void)
{
	cout << "Test MTL." << endl;
}

void MTL::DO_init()
{
    MW = new MainWorker();
}

void MTL::DO_load_substances()
{
    MW->DO_load_substances();
}

int MTL::DO_add_body(string new_name, double new_position_x, double new_position_y, double new_position_z,
	double new_size_x, double new_size_y, double new_size_z, string new_substance_name, double new_temperature,
	bool new_solid)
{
    return MW->GET_body_list_manipulator()->DO_add_body(new_name, new_position_x, new_position_y,
        new_position_z, new_size_x, new_size_y, new_size_z, new_substance_name,
        new_temperature, new_solid);
} 

void MTL::SET_environment_parameters(string new_substance, double new_temperature)
{
    MW->GET_environment_manipulator()->SET_environment_parameters(new_substance, new_temperature);
}

void MTL::DO_body_interaction_with_environment(int body_number)
{
    MTL::Thermal_processor::DO_body_interaction_with_environment(body_number);
}

void MTL::DO_body_interaction_inside(int body_number)
{
    MTL::Thermal_processor::DO_body_interaction_inside(body_number);
}

int MTL::GET_count_bodies()
{
    MW->GET_body_list_manipulator()->GET_count_bodies();
}