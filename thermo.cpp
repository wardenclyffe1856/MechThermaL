#include "main.h"
#include "data.h"
#include "constant.h"

#define blm Body_list_manipulator


using namespace MTL;


void DO_body_interaction_body_with_environment(int body_number)
{
	for(int i = 0; i < blm::GET_body_number_boxels_x(body_number); i++)
			for(int j = 0; j < blm::GET_body_number_boxels_y(body_number); j++)
			for(int g = 0; g < blm::GET_body_number_boxels_z(body_number); g++)
			{
				double d_energy;
				if(GET_environment_temperature() <=
					GET_substance_crystallization_temperature(GET_body_substance(body_number)))
				{
					d_energy = (GET_environment_temperature() -
						GET_body_boxel_temperature(body_number, i, j, g)) *
						GET_substance_specific_heat_solid(GET_body_substance(body_number)) *
						GET_body_boxel_mass(body_number);
				}
				else
				{
					double boxel_mass = GET_body_boxel_mass(body_number);
					int substance = GET_body_substance(body_number);
					double crystallization_temperature =
						GET_substance_crystallization_temperature(substance);
					double boxel_temperature = GET_body_boxel_temperature(body_number, i, j, g);
					double specific_heat_solid =
						GET_substance_specific_heat_solid(GET_body_substance(body_number));
					double specific_crystallization_heat =
						GET_substance_specific_crystallization_heat(GET_body_substance(body_number));
					double environment_temperature = GET_environment_temperature();
					double specific_heat_liquid =
						GET_substance_specific_heat_liquid(GET_body_substance(body_number));
					d_energy = (crystallization_temperature - boxel_temperature) *
						specific_heat_solid * boxel_mass +
						boxel_mass * specific_crystallization_heat +
						(environment_temperature - crystallization_temperature) *
						boxel_mass * specific_heat_liquid;
				}
				d_energy *= thermal_coefficient_1 * GET_body_boxel_area_environment(body_number, i, j, g);
				DO_body_boxel_change_energy(body_number, i, j, g, d_energy);
			}
}
