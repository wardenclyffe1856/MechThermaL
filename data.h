#ifndef _DATA_H_
#define _DATA_H_

#include <string>

using std::string;

int GET_substance_number(string);
double GET_substance_density_solid(int substance_number);

//Substance class.
class c_substance{
private:
    string name;								//A name of a substance.
    double density_solid;						//A density of a substance in the solid state.
    double specific_heat_solid;					//A specific heat of a substance in the solid state.
    double density_liquid;						//A density of a substance in the liquid state.
    double specific_heat_liquid;				//A specific heat of a substance in the liquid state.
    double density_gas;							//A density of a substance in the gas state.
    double specific_heat_gas;					//A specific heat of a substance in the gas state.
    double crystallization_temperature;			//A crystallization temperature of a substance.
    double vaporization_temperature;			//A vaporization temperature of a substance.
    double specific_crystallization_heat;		//A specific crystallization heat of a substance.
    double specific_vaporization_heat;			//A specific vaponization heat of a substance.
public:

	//To set all parameters of a substance.
    void SET_all(string new_name, double new_density_solid, double new_specific_heat_solid, double new_density_liquid,
        double new_specific_heat_liquid, double new_density_gas, double new_specific_heat_gas,
        double new_crystallization_temperature, double new_vaporization_temperature,
        double new_specific_crystallization_heat, double new_specific_vaporization_heat);

	//To get a name of a substance.
    string GET_name(void);

	//To get a density of a substance in the solid stante.
    double GET_density_solid(void);
};

#endif