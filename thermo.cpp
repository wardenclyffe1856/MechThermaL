#include "main.h"

void DO_body_interaction_body_with_area(int body_number)
{
	for(int i=0; i<GET_body_number_boxels_x(body_number); i++)
		for(int j=0; j<GET_body_number_boxels_y(body_number); j++)
			for(int g=0; g<GET_body_number_boxels_z(body_number); g++)
			{
				if(GET_environment_temperature()>GET_body_boxel_temperature(body_number, i, j, g))
				{

				}
			}
}
