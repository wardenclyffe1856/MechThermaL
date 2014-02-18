#include "mtl.h"

#include <iostream>

using std::cout;
using std::endl;

MTL::details::MainWorker* MW;

void MTL::DO_test(void)
{
	if (MW)
		cout << "MTL loaded successfully!" << endl;
	else
		cout << "MTL is not ready now!" << endl;
}

void MTL::DO_init()
{
    MW = new details::MainWorker();
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
    MTL::details::Thermal_processor::DO_body_interaction_with_environment(body_number);
}

void MTL::DO_body_interaction_inside(int body_number)
{
    MTL::details::Thermal_processor::DO_body_interaction_inside(body_number);
}

int MTL::GET_count_bodies()
{
    return MW->GET_body_list_manipulator()->GET_count_bodies();
}

vector<vector<vector<bool> > > MTL::GET_body_state(int body_number)
{
	vector<vector<vector<bool> > > result;
	int body_number_boxels_x = MW->GET_body_list_manipulator()->GET_body_number_boxels_x(body_number);
	int body_number_boxels_y = MW->GET_body_list_manipulator()->GET_body_number_boxels_y(body_number);
	int body_number_boxels_z = MW->GET_body_list_manipulator()->GET_body_number_boxels_z(body_number);
	result.resize(body_number_boxels_x);
	for (int i = 0; i < body_number_boxels_x; i++)
	{
		result[i].resize(body_number_boxels_y);
		for (int j = 0; j < body_number_boxels_y; j++)
		{
			result[i][j].resize(body_number_boxels_z);
			for (int g = 0; g < body_number_boxels_z; g++)
			{
				result[i][j][g] = (MW->GET_body_list_manipulator()->GET_body_boxel_state(body_number, i, j, g));
			}
		}
	}
	return result;
}

double MTL::GET_body_state_solid(int body_number)
{
	double result;
	int number_boxel_solid = 0;
	int body_number_boxels_x = MW->GET_body_list_manipulator()->GET_body_number_boxels_x(body_number);
	int body_number_boxels_y = MW->GET_body_list_manipulator()->GET_body_number_boxels_y(body_number);
	int body_number_boxels_z = MW->GET_body_list_manipulator()->GET_body_number_boxels_z(body_number);
	for (int i = 0; i < body_number_boxels_x; i++)
	{
		for (int j = 0; j < body_number_boxels_y; j++)
		{
			for (int g = 0; g < body_number_boxels_z; g++)
			{
				if (MW->GET_body_list_manipulator()->GET_body_boxel_state(body_number, i, j, g))
					number_boxel_solid++;
			}
		}
	}
	result = number_boxel_solid / (body_number_boxels_x * body_number_boxels_y *
		body_number_boxels_z);
	return result;
}

 void MTL::DO_body_refresh_state(int body_number)
 {
	MTL::details::Thermal_processor::DO_body_refresh_state(body_number);
 }

double MTL::GET_BodyPositionX(int body_number)
{
	return MW->GET_body_list_manipulator()->GET_body_position_x(body_number);
}

double MTL::GET_BodyPositionY(int body_number)
{
	return MW->GET_body_list_manipulator()->GET_body_position_y(body_number);
}

double MTL::GET_BodyPositionZ(int body_number)
{
	return MW->GET_body_list_manipulator()->GET_body_position_z(body_number);
}

int MTL::GET_body_number_boxels_x(int body_number)
{
	return MW->GET_body_list_manipulator()->GET_body_number_boxels_x(body_number);
}

int MTL::GET_body_number_boxels_y(int body_number)
{
	return MW->GET_body_list_manipulator()->GET_body_number_boxels_y(body_number);
}

int MTL::GET_body_number_boxels_z(int body_number)
{
	return MW->GET_body_list_manipulator()->GET_body_number_boxels_z(body_number);
}

double GET_body_boxel_size_x(int body_number)
{
	return MW->GET_body_list_manipulator()->GET_body_boxel_size_x(body_number);
}

double GET_body_boxel_size_y(int body_number)
{
	return MW->GET_body_list_manipulator()->GET_body_boxel_size_y(body_number);
}

double GET_body_boxel_size_z(int body_number)
{
	return MW->GET_body_list_manipulator()->GET_body_boxel_size_z(body_number);
}

