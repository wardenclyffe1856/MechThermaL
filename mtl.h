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
    #define DO_SetEnvironmentParameters SET_environment_parameters
    #define DO_BodyInteractionWithEnvironment DO_body_interaction_with_environment
    #define DO_BodyInteractionInside DO_body_interaction_inside
    #define GET_CountBodies GET_count_bodies
    #define GET_BodyState GET_body_state
    #define DO_BodyRefreshState DO_body_refresh_state
    #define GET_BodyStateSolid GET_body_state_solid
	#define GET_BodyPositionX GET_body_position_x
	#define GET_BodyPositionY GET_body_position_y
	#define GET_BodyPositionZ GET_body_position_z
	#define GET_BodyNumberBoxelsX GET_body_number_boxels_x
	#define GET_BodyNumberBoxelsY GET_body_number_boxels_y
	#define GET_BodyNumberBoxelsZ GET_body_number_boxels_z
	#define GET_BodyBoxelSizeX GET_body_boxel_size_x
    #define GET_BodyBoxelSizeY GET_body_boxel_size_y
    #define GET_BodyBoxelSizeZ GET_body_boxel_size_z


    void DO_Init(void);
	void DO_LoadSubstances(void);
	void DO_Test(void);
    int DO_AddBody(string new_name, double new_position_x, double new_position_y,
		double new_position_z, double new_size_x, double new_size_y,
		double new_size_z, string new_substance_name, double new_temperature,
		bool new_solid);
    void DO_SetEnvironmentParameters(string new_substance, double new_temperature);
    void DO_BodyInteractionWithEnvironment(int body_number);
    void DO_BodyInteractionInside(int body_number);
    int GET_CountBodies();
    vector<vector<vector<bool> > > GET_BodyState(int body_number);
    double GET_BodyStateSolid(int body_number);
    void DO_BodyRefreshState(int body_number);
    double GET_BodyPositionX(int body_number);
    double GET_BodyPositionY(int body_number);
    double GET_BodyPositionZ(int body_number);
    int GET_BodyNumberBoxelsX(int body_number);
    int GET_BodyNumberBoxelsY(int body_number);
    int GET_BodyNumberBoxelsZ(int body_number);
    double GET_BodyBoxelSizeX(int body_number);
    double GET_BodyBoxelSizeY(int body_number);
    double GET_BodyBoxelSizeZ(int body_number);

    int DO_AddBody(string new_name, double new_position_x, double new_position_y, double new_position_z,
	double new_size_x, double new_size_y, double new_size_z, string new_substance_name, double new_temperature,
	bool new_solid);
    void SET_environment_parameters(string new_substance, double new_temperature);
    void DO_body_interaction_with_environment(int body_number);
    void DO_body_interaction_inside(int body_number);
    int GET_count_bodies();
    vector<vector<vector<bool> > > GET_body_state(int body_number);
    void DO_body_refresh_state(int body_number);
}

#endif //_MTL_H_
