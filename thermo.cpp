#include "main.h"
#include "constant.h"

extern MTL::MainWorker* MW;

using namespace MTL;


void DO_body_interaction_body_with_environment(int body_number)
{
    Body_list_manipulator* blm = MW->GET_body_list_manipulator();
    Environment_manipulator* em = MW->GET_environment_manipulator();
    Substance_manipulator* sm = MW->GET_substance_manipulator();
	for(int i = 0; i < blm->GET_body_number_boxels_x(body_number); i++)
			for(int j = 0; j < blm->GET_body_number_boxels_y(body_number); j++)
			for(int g = 0; g < blm->GET_body_number_boxels_z(body_number); g++)
			{
				double d_energy;
				if(em->GET_environment_temperature() <=
                    sm->GET_substance_crystallization_temperature(blm->GET_body_substance(body_number)))
				{
					d_energy = (em->GET_environment_temperature() -
						blm->GET_body_boxel_temperature(body_number, i, j, g)) *
						sm->GET_substance_specific_heat_solid(blm->GET_body_substance(body_number)) *
						blm->GET_body_boxel_mass(body_number);
				}
				else
				{
					double boxel_mass = blm -> GET_body_boxel_mass(body_number);
					int substance = blm -> GET_body_substance(body_number);
					double crystallization_temperature =
						sm->GET_substance_crystallization_temperature(substance);
					double boxel_temperature = blm->GET_body_boxel_temperature(body_number, i, j, g);
					double specific_heat_solid =
						sm->GET_substance_specific_heat_solid(blm->GET_body_substance(body_number));
					double specific_crystallization_heat =
						sm->GET_substance_specific_crystallization_heat(blm->GET_body_substance(body_number));
					double environment_temperature = em->GET_environment_temperature();
					double specific_heat_liquid =
						sm->GET_substance_specific_heat_liquid(blm->GET_body_substance(body_number));
					d_energy = (crystallization_temperature - boxel_temperature) *
						specific_heat_solid * boxel_mass +
						boxel_mass * specific_crystallization_heat +
						(environment_temperature - crystallization_temperature) *
						boxel_mass * specific_heat_liquid;
				}
                d_energy *= Constants::thermal_coefficient_1 * blm->GET_body_boxel_area_environment(body_number, i, j, g);
				blm->DO_body_boxel_change_energy(body_number, i, j, g, d_energy);
			}
}
