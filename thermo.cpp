#include "mtl.h"

extern MTL::details::MainWorker* MW;

//Temporary.
double abs(double number)
{
	return number>=0 ? number : -number;
}


void MTL::details::Thermal_processor::DO_body_interaction_with_environment(int body_number)
{
    Body_list_manipulator* blm = MW->GET_body_list_manipulator();
    Environment_manipulator* em = MW->GET_environment_manipulator();
    Substance_manipulator* sm = MW->GET_substance_manipulator();
	double boxel_mass = blm->GET_body_boxel_mass(body_number);
	int substance = blm->GET_body_substance(body_number);
	double crystallization_temperature =
		sm->GET_substance_crystallization_temperature(substance);
	double specific_heat_solid =
		sm->GET_substance_specific_heat_solid(blm->GET_body_substance(body_number));
	double specific_crystallization_heat =
		sm->GET_substance_specific_crystallization_heat(blm->GET_body_substance(body_number));
	double environment_temperature = em->GET_environment_temperature();
	double specific_heat_liquid =
		sm->GET_substance_specific_heat_liquid(blm->GET_body_substance(body_number));
	double boxel_temperature;
	for(int i = 0; i < blm->GET_body_number_boxels_x(body_number); i++)
		for(int j = 0; j < blm->GET_body_number_boxels_y(body_number); j++)
			for(int g = 0; g < blm->GET_body_number_boxels_z(body_number); g++)
			{
				double d_energy;
				if(em->GET_environment_temperature() <=
                    sm->GET_substance_crystallization_temperature(blm->GET_body_substance(body_number)))
				{
					boxel_temperature = blm->GET_body_boxel_temperature(body_number, i, j, g);
					d_energy = (environment_temperature - boxel_temperature) *
						specific_heat_solid * boxel_mass;
				}
				else
				{
					boxel_temperature = blm->GET_body_boxel_temperature(body_number, i, j, g);
					d_energy = (environment_temperature - boxel_temperature) *
						specific_heat_solid * boxel_mass +
						boxel_mass * specific_crystallization_heat +
						(environment_temperature - crystallization_temperature) *
						boxel_mass * specific_heat_liquid;
				}
                d_energy *= Constants::thermal_coefficient_1 * blm->GET_body_boxel_area_environment(body_number, i, j, g);
				blm->DO_body_boxel_change_energy(body_number, i, j, g, d_energy);
			}
	for(int i = 0; i < blm->GET_body_number_boxels_x(body_number); i++)
		for(int j = 0; j < blm->GET_body_number_boxels_y(body_number); j++)
			for(int g = 0; g < blm->GET_body_number_boxels_z(body_number); g++)
			{
				double new_temperature;
				double temp_energy = blm->GET_body_boxel_energy(body_number, i, j, g);
				if(blm->GET_body_boxel_energy(body_number, i, j, g) <= 0.0)
				{
					new_temperature = temp_energy / (boxel_mass * specific_heat_solid);
				}
				else if(blm->GET_body_boxel_energy(body_number, i, j, g) <=
					sm->GET_substance_specific_crystallization_heat(blm->GET_body_substance(body_number)) *
						blm->GET_body_boxel_mass(body_number))
				{
					new_temperature = crystallization_temperature;
				}
				else
				{
					new_temperature = (temp_energy - specific_crystallization_heat * boxel_mass) /
						(boxel_mass * specific_heat_liquid);
				}
				blm->SET_body_boxel_temperature(body_number, i, j, g, new_temperature);
			}
}

void MTL::details::Thermal_processor::DO_body_interaction_inside(int body_number)
{
	Body_list_manipulator* blm = MW->GET_body_list_manipulator();
    Substance_manipulator* sm = MW->GET_substance_manipulator();
	double middle_energy = 0.0;
	for(int i = 0; i < blm->GET_body_number_boxels_x(body_number); i++)
		for(int j = 0; j < blm->GET_body_number_boxels_y(body_number); j++)
			for(int g = 0; g < blm->GET_body_number_boxels_z(body_number); g++)
			{
				middle_energy += blm->GET_body_boxel_energy(body_number, i, j, g);
			}
	middle_energy /= (blm->GET_body_number_boxels_x(body_number) * blm->GET_body_number_boxels_y(body_number) *
		blm->GET_body_number_boxels_z(body_number));
	for(int i = 0; i < blm->GET_body_number_boxels_x(body_number); i++)
		for(int j = 0; j < blm->GET_body_number_boxels_y(body_number); j++)
			for(int g = 0; g < blm->GET_body_number_boxels_z(body_number); g++)
			{
				double d_energy = (middle_energy - blm->GET_body_boxel_energy(body_number, i, j, g)) * Constants::thermal_coefficient_2;
				blm->DO_body_boxel_change_energy(body_number, i, j, g, d_energy);
			}
	for(int i = 0; i < blm->GET_body_number_boxels_x(body_number); i++)
		for(int j = 0; j < blm->GET_body_number_boxels_y(body_number); j++)
			for(int g = 0; g < blm->GET_body_number_boxels_z(body_number); g++)
			{
				double new_temperature;
				if(blm->GET_body_boxel_energy(body_number, i, j, g) <= 0.0)
				{
					new_temperature = blm->GET_body_boxel_energy(body_number, i, j, g) /
						(blm->GET_body_boxel_mass(body_number) *
						sm->GET_substance_specific_heat_solid(blm->GET_body_substance(body_number)));
				}
				else if(blm->GET_body_boxel_energy(body_number, i, j, g) <=
					sm->GET_substance_specific_crystallization_heat(blm->GET_body_substance(body_number)) *
						blm->GET_body_boxel_mass(body_number))
				{
					new_temperature = sm->GET_substance_crystallization_temperature(blm->GET_body_substance(body_number));
				}
				else
				{
					new_temperature = (blm->GET_body_boxel_energy(body_number, i, j, g) -
						sm->GET_substance_specific_crystallization_heat(blm->GET_body_substance(body_number)) *
						blm->GET_body_boxel_mass(body_number)) / (blm->GET_body_boxel_mass(body_number) *
						sm->GET_substance_specific_heat_liquid(blm->GET_body_substance(body_number)));
				}
				blm->SET_body_boxel_temperature(body_number, i, j, g, new_temperature);
			}
}

void MTL::details::Thermal_processor::DO_body_refresh_state(int body_number)
{
	Body_list_manipulator* blm = MW->GET_body_list_manipulator();
    Substance_manipulator* sm = MW->GET_substance_manipulator();
	for (int i = 0; i < blm->GET_body_number_boxels_x(body_number); i++)
		for (int j = 0; j < blm->GET_body_number_boxels_y(body_number); j++)
			for (int g = 0; g < blm->GET_body_number_boxels_z(body_number); g++)
			{
				double energy_point_1 = blm->GET_body_boxel_mass(body_number) *
					sm->GET_substance_specific_crystallization_heat(body_number);
				if (blm->GET_body_boxel_energy(body_number, i, j, g) < energy_point_1)
				{
					blm->SET_body_boxel_state(body_number, i, j, g, true);
				}
				else
				{
					blm->SET_body_boxel_state(body_number, i, j, g, false);
				}
			}
}
