#include "mtl.h"

#include "data.h"

#include <string>
#include <vector>
#include <fstream>

using std::string;
using std::vector;
using std::ifstream;

const string FILE_SUBSTANCES=           "data/substances.data";     //Substances data file.

	//To set all parameters of a substance.
    void c_substance::SET_all(string new_name, double new_density_solid, double new_specific_heat_solid, double new_density_liquid,
        double new_specific_heat_liquid, double new_density_gas, double new_specific_heat_gas,
        double new_crystallization_temperature, double new_vaporization_temperature,
        double new_specific_crystallization_heat, double new_specific_vaporization_heat)
    {
        name=new_name;
        density_solid=new_density_solid;
        specific_heat_solid=new_specific_heat_solid;
        density_liquid=new_density_liquid;
        specific_heat_liquid=new_specific_heat_liquid;
		density_gas=new_density_gas;
        specific_heat_gas=new_specific_heat_gas;
        crystallization_temperature=new_crystallization_temperature;
        vaporization_temperature=new_vaporization_temperature;
        specific_crystallization_heat=new_specific_crystallization_heat;
        specific_vaporization_heat=new_specific_vaporization_heat;
    }

	//To get a name of a substance.
    string c_substance::GET_name(void)
    {
        return(name);
    }

	//To get a density of a substance in the solid stante.
    double c_substance::GET_density_solid(void)
    {
        return(density_solid);
    }

vector<c_substance> substance;			//List of substances.

//To load parameters of all substances.
void MTL::DO_load_substances(void)
{
    ifstream f_substances(FILE_SUBSTANCES.c_str());

    string temp_name;
    double temp_density_solid;
    double temp_specific_heat_solid;
    double temp_density_liquid;
    double temp_specific_heat_liquid;
    double temp_density_gas;
    double temp_specific_heat_gas;
    double temp_crystallization_temperature;
    double temp_vaporization_temperature;
    double temp_specific_crystallization_heat;
    double temp_specific_vaporization_heat;
    c_substance temp_substance;
    while(f_substances>>temp_name>>temp_density_solid>>temp_specific_heat_solid>>temp_density_liquid
			>>temp_specific_heat_liquid>>temp_density_gas>>temp_specific_heat_gas>>temp_crystallization_temperature
			>>temp_vaporization_temperature>>temp_specific_crystallization_heat>>temp_specific_vaporization_heat)
    {
        temp_substance.SET_all(temp_name, temp_density_solid, temp_specific_heat_solid, temp_density_liquid,
            temp_specific_heat_liquid, temp_density_gas, temp_specific_heat_gas, temp_crystallization_temperature,
            temp_vaporization_temperature, temp_specific_crystallization_heat, temp_specific_vaporization_heat);
		substance.push_back(temp_substance);
    }
	f_substances.close();
}

//To get a number of a substance.
int GET_substance_number(string name)
{
	for(int i=0; i<(int)substance.size(); i++)
        if(name==substance[i].GET_name())   return(i);
    return 0;
}

//To get a density of a substance in the solid state.
double GET_substance_density_solid(int substance_number)
{
	return(substance[substance_number].GET_density_solid());
}
