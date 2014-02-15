#ifndef _MTL_H_
#define _MTL_H_

#include "constant.h"
#include "main.h"
#include "thermo.h"

namespace MTL
{
    #define DO_LoadSubstances DO_load_substances 
    #define DO_Test DO_test
    #define DO_Init DO_init
    #define DO_AddBody DO_add_body
    ///
    void DO_Init(void);
	void DO_LoadSubstances(void);
	void DO_Test(void);
    int DO_AddBody(string new_name, double new_position_z, double new_position_y, double new_position_x,
	double new_size_x, double new_size_y, double new_size_z, string new_substance_name, double new_temperature,
	bool new_solid);
    void SET_environment_parameters(string new_substance, double new_temperature);
    void DO_body_interaction_with_environment(int body_number);
    void DO_body_interaction_inside(int body_number);
    int GET_count_bodies();
}

#endif