#include "mtl.h"

#include <vector>
#include <string>
#include <iostream>

#define blmcbd details::Body_list_manipulator::c_body
#define blmcbx details::Body_list_manipulator::c_boxel

using std::vector;
using std::string;
using namespace MTL;

extern details::MainWorker* MW;

const double MIN_BOXEL_SIZE =		0.001;		//The minimal size of a boxel (m).

	//To set a new temperature.
	void  blmcbx::SET_energy(double new_energy)
	{
		energy = new_energy;
	}

    double blmcbx::GET_temperature(void)
	{
		return(temperature);
	}

    void blmcbx::SET_temperature(double new_temperature)
	{
		temperature=new_temperature;
	}

    double blmcbx::GET_energy(void)
    {
        return(energy);
    }

	//To set a state of a boxel.
	void blmcbx::SET_state(bool new_solid)
	{
		is_solid = new_solid;
	}


	bool blmcbx::GET_state(void)
	{
		return(is_solid);
	}

//The class of a physics body.
    //To set a name of a body.
	void blmcbd::SET_name(string new_name)
    {
        name = new_name;
    }

    //To set a position of a body (x, y and z coordinates).
    void blmcbd::SET_position(double new_position_x, double new_position_y, double new_position_z)
    {
        position_x = new_position_x;
        position_y = new_position_y;
        position_z = new_position_z;
    }

    //To set a size of a body (x, y and z sizes).
    void blmcbd::SET_size(double new_size_x, double new_size_y, double new_size_z)
    {
        size_x = new_size_x;
        size_y = new_size_y;
        size_z = new_size_z;
    }

    void blmcbd::SET_boxel_state(int boxel_number_x, int boxel_number_y, int boxel_number_z, bool new_is_solid)
    {
		boxel[boxel_number_x][boxel_number_y][boxel_number_z].SET_state(new_is_solid);
    }


    //To set a substance.
    void blmcbd::SET_substance(string new_substance_name)
    {
        substance = MW->GET_substance_manipulator()->GET_substance_number(new_substance_name);
    }

	//To set all parameters of a body.
    void blmcbd::SET_all(string new_name, double new_position_x, double new_position_y, double new_position_z,
		double new_size_x, double new_size_y, double new_size_z, string new_substance_name, double new_temperature,
		bool new_solid)
    {
		SET_name(new_name);
		SET_position(new_position_x, new_position_y, new_position_z);
		SET_size(new_size_x, new_size_y, new_size_z);
		SET_substance(new_substance_name);

		mass = size_x * size_y * size_z *
			MW->GET_substance_manipulator()->GET_substance_density_solid(substance);
		number_boxels_x = (int) (size_x / MIN_BOXEL_SIZE);
		number_boxels_y = (int) (size_y / MIN_BOXEL_SIZE);
		number_boxels_z = (int) (size_z / MIN_BOXEL_SIZE);
		boxel_size_x = size_x / number_boxels_x;
		boxel_size_y = size_y / number_boxels_y;
		boxel_size_z = size_z / number_boxels_z;
		boxel_mass = boxel_size_x * boxel_size_y * boxel_size_z *
			MW->GET_substance_manipulator()->GET_substance_density_solid(substance);
		c_boxel temp_boxel;
		temp_boxel.SET_temperature(new_temperature);
		double new_energy;
		Substance_manipulator* sm = MW->GET_substance_manipulator();
		if(new_temperature <= sm->GET_substance_crystallization_temperature(substance))
		{
			new_energy = boxel_mass * sm->GET_substance_specific_heat_solid(substance) *
				new_temperature;

		}
		else
		{
			new_energy = boxel_mass * sm->GET_substance_specific_crystallization_heat(substance) +
				boxel_mass * sm->GET_substance_specific_heat_liquid(substance) * new_temperature;
		}
		temp_boxel.SET_energy(new_energy);
		temp_boxel.SET_state(new_solid);

		/*try {
		throw
		} catch () {}*/

        boxel.resize(number_boxels_x);
		for (int i = 0; i < number_boxels_x; i++)
		{
			boxel[i].resize(number_boxels_y);
			for(int j = 0; j < number_boxels_y; j++)
			{
			boxel[i][j].resize(number_boxels_z);

			    for(int g = 0; g < number_boxels_z; g++)
                    (boxel[i])[j][g] = (temp_boxel);
			}
		}
    }

    //To get the number of boxels on the x axis.
    int blmcbd::GET_number_boxels_x(void)
    {
		return(number_boxels_x);
    }

    //To get the number of boxels on the y axis.
    int blmcbd::GET_number_boxels_y(void)
    {
		return(number_boxels_y);
    }

    //To get the number of boxels on the z axis.
    int blmcbd::GET_number_boxels_z(void)
    {
		return(number_boxels_z);
    }

    double blmcbd::GET_boxel_temperature(int boxel_number_x, int boxel_number_y, int boxel_number_z)
    {
        return(boxel[boxel_number_x][boxel_number_y][boxel_number_z].GET_temperature());
    }

	bool blmcbd::GET_boxel_state(int boxel_number_x, int boxel_number_y, int boxel_number_z)
	{
		return(boxel[boxel_number_x][boxel_number_y][boxel_number_z].GET_state());
	}

    void blmcbd::SET_boxel_temperature(int boxel_number_x, int boxel_number_y, int boxel_number_z, double new_temperature)
    {
        boxel[boxel_number_x][boxel_number_y][boxel_number_z].SET_temperature(new_temperature);
    }


    double blmcbd::GET_boxel_area_environment(int boxel_number_x, int boxel_number_y, int boxel_number_z)
	{
		double temp_area = 0.0;
		if (boxel[boxel_number_x][boxel_number_y][boxel_number_z].GET_state())
		{
			if (boxel_number_x == 0 || !boxel[boxel_number_x - 1][boxel_number_y][boxel_number_z].GET_state())
				temp_area += boxel_size_y * boxel_size_z;

			if (boxel_number_y == 0 || !boxel[boxel_number_x][boxel_number_y - 1][boxel_number_z].GET_state())
				temp_area += boxel_size_x * boxel_size_z;

            if (boxel_number_z == 0 || !boxel[boxel_number_x][boxel_number_y][boxel_number_z - 1].GET_state())
				temp_area += boxel_size_x * boxel_size_y;

            if (boxel_number_x == number_boxels_x - 1 || !boxel[boxel_number_x + 1][boxel_number_y][boxel_number_z].GET_state())
				temp_area += boxel_size_y * boxel_size_z;

            if (boxel_number_y == number_boxels_y - 1 || !boxel[boxel_number_x][boxel_number_y + 1][boxel_number_z].GET_state())
				temp_area += boxel_size_x * boxel_size_z;

            if (boxel_number_z == number_boxels_z - 1 || !boxel[boxel_number_x][boxel_number_y][boxel_number_z + 1].GET_state())
				temp_area += boxel_size_x * boxel_size_y;
		}
		return(temp_area);
	}

	double blmcbd::GET_position_x(void)
	{
		return position_x;
	}

    double blmcbd::GET_position_y(void)
    {
		return position_y;
    }

    double blmcbd::GET_position_z(void)
    {
		return position_z;
    }

    double blmcbd::GET_boxel_size_x(void)
    {
		return boxel_size_x;
    }

    double blmcbd::GET_boxel_size_y(void)
    {
		return boxel_size_y;
    }

    double blmcbd::GET_boxel_size_z(void)
    {
		return boxel_size_z;
    }


//**************************************Body list manipulations********************************************************

//To add a body to the list of bodies.
int details::Body_list_manipulator::DO_add_body(string new_name, double new_position_x, double new_position_y, double new_position_z,
	double new_size_x, double new_size_y, double new_size_z, string new_substance_name, double new_temperature,
	bool new_solid)
{
	c_body temp_body;
	temp_body.SET_all(new_name, new_position_x, new_position_y, new_position_z, new_size_x, new_size_y,
		new_size_z, new_substance_name, new_temperature, new_solid);
	body.push_back(temp_body);
    return (int)(body.size()) - 1;
}

//*********************************************************************************************************************

//**************************************Environment manipulations******************************************************

//To set all parameters of environment.
void details::Environment_manipulator::c_environment::SET_all(string new_substance_name, double new_temperature)
{
	substance = MW->GET_substance_manipulator()->GET_substance_number(new_substance_name);
	temperature = new_temperature;
}

//To get the temperature of environment.
double details::Environment_manipulator::c_environment::GET_temperature(void)
{
	return(temperature);
}



//To set all parameters of environment.
void details::Environment_manipulator::SET_environment_parameters(string new_substance, double new_temperature)
{
	environment.SET_all(new_substance, new_temperature);
}

//To get the temperature of environment.
double details::Environment_manipulator::GET_environment_temperature(void)
{
	return(environment.GET_temperature());
}

//*********************************************************************************************************************

//To get the number of boxels on the x axis of a body.
int details::Body_list_manipulator::GET_body_number_boxels_x(int body_number)
{
	return(body[body_number].GET_number_boxels_x());
}

//To get the number of boxels on the y axis of a body.
int details::Body_list_manipulator::GET_body_number_boxels_y(int body_number)
{
	return(body[body_number].GET_number_boxels_y());
}

//To get the number of boxels on the z axis of a body.
int details::Body_list_manipulator::GET_body_number_boxels_z(int body_number)
{
	return(body[body_number].GET_number_boxels_z());
}

double details::Body_list_manipulator::GET_body_boxel_temperature(int body_number, int boxel_number_x, int boxel_number_y, int boxel_number_z)
{
	return(body[body_number].GET_boxel_temperature(boxel_number_x, boxel_number_y, boxel_number_z));
}

bool details::Body_list_manipulator::GET_body_boxel_state(int body_number, int boxel_number_x, int boxel_number_y, int boxel_number_z)
{
	return(body[body_number].GET_boxel_state(boxel_number_x, boxel_number_y, boxel_number_z));
}

void details::Body_list_manipulator::SET_body_boxel_state(int body_number, int boxel_number_x, int boxel_number_y, int boxel_number_z, bool new_is_solid)
{
	body[body_number].SET_boxel_state(boxel_number_x, boxel_number_y, boxel_number_z, new_is_solid);
}

void details::Body_list_manipulator::SET_body_boxel_temperature(int body_number, int boxel_number_x, int boxel_number_y, int boxel_number_z, double new_temperature)
{
    body[body_number].SET_boxel_temperature(boxel_number_x, boxel_number_y, boxel_number_z, new_temperature);
}

int details::Body_list_manipulator::GET_count_bodies()
{
    return (int)body.size();
}

double details::Body_list_manipulator::GET_body_position_x(int body_number)
{
	return body[body_number].GET_position_x();
}

double details::Body_list_manipulator::GET_body_position_y(int body_number)
{
	return body[body_number].GET_position_y();
}

double details::Body_list_manipulator::GET_body_position_z(int body_number)
{
	return body[body_number].GET_position_z();
}

double details::Body_list_manipulator::GET_body_boxel_size_x(int body_number)
{
	return body[body_number].GET_boxel_size_x();
}

double details::Body_list_manipulator::GET_body_boxel_size_y(int body_number)
{
	return body[body_number].GET_boxel_size_y();
}

double details::Body_list_manipulator::GET_body_boxel_size_z(int body_number)
{
	return body[body_number].GET_boxel_size_z();
}


details::MainWorker::MainWorker()
{
    this->BLM = new Body_list_manipulator();
    this->EM = new Environment_manipulator();
    this->SM = new Substance_manipulator();
}

void details::MainWorker::DO_load_substances()
{
    this->SM->DO_load_substances();
}

details::Body_list_manipulator* details::MainWorker::GET_body_list_manipulator()
{
    return this->BLM;
}

details::Environment_manipulator* details::MainWorker::GET_environment_manipulator()
{
    return this->EM;
}

details::Substance_manipulator* details::MainWorker::GET_substance_manipulator()
{
    return this->SM;
}




double details::Body_list_manipulator::GET_body_boxel_energy(int body_number, int boxel_number_x, int boxel_number_y, int boxel_number_z)
{
	return(body[body_number].GET_boxel_energy(boxel_number_x, boxel_number_y, boxel_number_z));
}

int details::Body_list_manipulator::GET_body_substance(int body_number)
{
	return(body[body_number].GET_substance());
}

double details::Body_list_manipulator::GET_body_boxel_area_environment(int body_number, int boxel_number_x, int boxel_number_y, int boxel_number_z)
{
	return(body[body_number].GET_boxel_area_environment(boxel_number_x, boxel_number_y, boxel_number_z));
}

double details::Body_list_manipulator::GET_body_boxel_mass(int body_number)
{
	return(body[body_number].GET_boxel_mass());
}

void details::Body_list_manipulator::DO_body_boxel_change_energy(int body_number, int boxel_number_x, int boxel_number_y, int boxel_number_z, double change_energy)
{
	body[body_number].DO_boxel_change_energy(boxel_number_x, boxel_number_y, boxel_number_z, change_energy);
}



double details::Body_list_manipulator::c_body::GET_boxel_energy(int boxel_number_x, int boxel_number_y, int boxel_number_z)
{
	return(boxel[boxel_number_x][boxel_number_y][boxel_number_z].GET_energy());
}

double details::Body_list_manipulator::c_body::GET_boxel_mass(void)
{
	return(boxel_mass);
}

int details::Body_list_manipulator::c_body::GET_substance(void)
{
	return(substance);
}

void details::Body_list_manipulator::c_body::DO_boxel_change_energy(int boxel_number_x, int boxel_number_y, int boxel_number_z, double change_energy)
{
	boxel[boxel_number_x][boxel_number_y][boxel_number_z].DO_change_energy(change_energy);
}

void details::Body_list_manipulator::c_boxel::DO_change_energy(double change_energy)
{
	energy += change_energy;
}



double details::Substance_manipulator::GET_substance_specific_heat_solid(int substance_number)
{
	return(substance[substance_number].GET_specific_heat_solid());
}

double details::Substance_manipulator::GET_substance_crystallization_temperature(int substance_number)
{
	return(substance[substance_number].GET_crystallization_temperature());
}

double details::Substance_manipulator::GET_substance_specific_crystallization_heat(int substance_number)
{
	return(substance[substance_number].GET_specific_crystallization_heat());
}

double details::Substance_manipulator::GET_substance_vaporization_temperature(int substance_number)
{
	return(substance[substance_number].GET_vaporization_temperature());
}

int details::Substance_manipulator::GET_number_substances(void)
{
	return((int)substance.size());
}

double details::Substance_manipulator::GET_substance_specific_heat_liquid(int substance_number)
{
	return(substance[substance_number].GET_specific_heat_liquid());
}

double details::Substance_manipulator::c_substance::GET_specific_heat_solid(void)
{
	return specific_heat_solid;
}

double details::Substance_manipulator::c_substance::GET_specific_heat_liquid(void)
{
	return specific_heat_liquid;
}

double details::Substance_manipulator::c_substance::GET_crystallization_temperature(void)
{
	return(crystallization_temperature);
}

double details::Substance_manipulator::c_substance::GET_specific_crystallization_heat(void)
{
	return(specific_crystallization_heat);
}

double details::Substance_manipulator::c_substance::GET_vaporization_temperature(void)
{
	return(vaporization_temperature);
}
