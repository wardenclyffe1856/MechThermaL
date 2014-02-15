#ifndef _MAIN_H_
#define _MAIN_H_

#include <vector>
#include <string>

using std::vector;
using std::string;

namespace MTL {
class Body_list_manipulator {
private:
	class c_body;
	class c_boxel;
	vector<c_body> body; //The list of bodies.
public:
	int DO_add_body(string new_name, double new_position_x, double new_position_y, double new_position_z,
	double new_size_x, double new_size_y, double new_size_z, string new_substance_name, double new_temperature,
	bool new_solid);
	void DO_delete_body(string body_name); //TODO: add implementation of void DO_delete_body(string)
	int GET_body_number_boxels_x(int body_number);
	int GET_body_number_boxels_y(int body_number);
	int GET_body_number_boxels_z(int body_number);
	double GET_body_boxel_temperature(int body_number, int boxel_number_x, int boxel_number_y, int boxel_number_z);
    void SET_body_boxel_temperature(int body_number, int boxel_number_x, int boxel_number_y, int boxel_number_z, double new_temperature); 
    double GET_body_boxel_energy(int body_number, int boxel_number_x, int boxel_number_y, int boxel_number_z);
    int GET_body_substance(int body_number);
    double GET_body_boxel_area_environment(int body_number, int boxel_number_x, int boxel_number_y, int boxel_number_z);
    double GET_body_boxel_mass(int body_number);
    void DO_body_boxel_change_energy(int body_number, int boxel_number_x, int boxel_number_y, int boxel_number_z, double change_energy);
    int GET_count_bodies();
};


class Body_list_manipulator::c_boxel {
private:
    double energy;             
    double temperature;                 //Temperature of a boxel (C).
    bool is_solid;						//State of a boxel (solid/liquid).
public:

	//To set a new temperature.
	void SET_energy(double new_energy);

	//To set a state of a boxel.
	void SET_state(bool new_solid);

    void SET_temperature(double new_temperature);

	//To get energy
	double GET_energy(void);

    double GET_temperature(void);

	bool GET_state(void);

    void DO_change_energy(double change_energy);
};

class Body_list_manipulator::c_body {
private:
    string name;                //A name of a body.
    double position_x;          //A body position on the x axis.
    double position_y;          //A body position on the y axis.
    double position_z;          //A body position on the z axis.
    double size_x;              //A body size on the x axis.
    double size_y;              //A body size on the y axis.
    double size_z;              //A body size on the z axis.
    int substance;				//A number of a substance.

    double mass;                //A mass of a body.
    int number_boxels_x;		//The number of boxels on the x axis.
    int number_boxels_y;		//The number of boxels on the y axis.
    int number_boxels_z;		//The number of boxels on the z axis.
    double boxel_size_x;		//A boxel size on the x axis.
    double boxel_size_y;		//A boxel size on the y axis.
    double boxel_size_z;		//A boxel size on the z axis.
    double boxel_mass;			//A mass of a boxel.

	vector<vector<vector<c_boxel> > > boxel;    //Boxel matrix.
public:

    //To set a name of a body.
    void SET_name(string new_name);

    //To set a position of a body (x, y and z coordinates).
    void SET_position(double new_position_x, double new_position_y, double new_position_z);

    //To set a size of a body (x, y and z sizes).
    void SET_size(double new_size_x, double new_size_y, double new_size_z);

    //To set a substance.
    void SET_substance(string new_substance_name);

	//To set all parameters of a body.
    void SET_all(string new_name, double new_position_x, double new_position_y, double new_position_z,
		double new_size_x, double new_size_y, double new_size_z, string new_substance_name, double new_temperature,
		bool new_solid);

    //To get the number of boxels on the x axis.
    int GET_number_boxels_x(void);

    //To get the number of boxels on the y axis.
    int GET_number_boxels_y(void);

    //To get the number of boxels on the z axis.
    int GET_number_boxels_z(void);

    double GET_boxel_temperature(int boxel_number_x, int boxel_number_y, int boxel_number_z);
    void SET_boxel_temperature(int boxel_number_x, int boxel_number_y, int boxel_number_z, double new_temperature);

    double GET_boxel_area_environment(int boxel_number_x, int boxel_number_y, int boxel_number_z);

    double GET_boxel_energy(int boxel_number_x, int boxel_number_y, int boxel_number_z);
    double GET_boxel_mass(void);
    int GET_substance(void);
    void DO_boxel_change_energy(int boxel_number_x, int boxel_number_y, int boxel_number_z, double change_energy);

};


class Environment_manipulator
{
private:
class c_environment{
	private:
		int substance;
		double temperature;
	public:

		//To set all parametres of environment.
		void SET_all(string new_substance_name, double new_temperature);

		//To get the temperature of environment.
		double GET_temperature(void);
	};
	c_environment environment;
public:
	void SET_environment_parameters(string new_substance, double new_temperature);
	double GET_environment_temperature(void);
};

class Substance_manipulator {
private:
    class c_substance; //Substance class.
    vector<c_substance> substance;			//List of substances.
public:
    int GET_substance_number(string);
    double GET_substance_density_solid(int substance_number);
    double GET_substance_specific_heat_solid(int substance_number);
    void DO_load_substances(void);
    double GET_substance_crystallization_temperature(int substance_number);
    double GET_substance_specific_crystallization_heat(int substance_number);
    double GET_substance_vaporization_temperature(int substance_number);
    int GET_number_substances(void);
    double GET_substance_specific_heat_liquid(int substance_number);
};

class Substance_manipulator::c_substance {
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

    double GET_specific_heat_solid(void);
    double GET_crystallization_temperature(void);
    double GET_specific_crystallization_heat(void);
    double GET_vaporization_temperature(void);
    double GET_specific_heat_liquid(void);
};

class MainWorker {
private:
    Body_list_manipulator* BLM;
    Environment_manipulator* EM;
    Substance_manipulator* SM;
public:
    MainWorker();
    void DO_load_substances();
    Body_list_manipulator* GET_body_list_manipulator();
    Environment_manipulator* GET_environment_manipulator();
    Substance_manipulator* GET_substance_manipulator();
};

}


#endif

