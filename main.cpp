#include "main.h"
#include "data.h"

#include <vector>
#include <string>

#define blmcbd Body_list_manipulator::c_body
#define blmcbx Body_list_manipulator::c_boxel

using std::vector;
using std::string;
using namespace MTL;

const double MIN_BOXEL_SIZE=		0.01;		//The minimal size of a boxel (m).

	//To set a new temperature.
	void  blmcbx::SET_energy(double new_energy) 
	{
		energy = new_energy;
	}

	//To set a state of a boxel.
	void blmcbx::SET_state(bool new_solid)
	{
		is_solid=new_solid;
	}


	bool blmcbx::GET_state(void)
	{
		return(is_solid);
	}

//The class of a physics body.
    //To set a name of a body.
	void blmcbd::SET_name(string new_name)
    {
        name=new_name;
    }

    //To set a position of a body (x, y and z coordinates).
    void blmcbd::SET_position(double new_position_x, double new_position_y, double new_position_z)
    {
        position_x=new_position_x;
        position_y=new_position_y;
        position_z=new_position_z;
    }

    //To set a size of a body (x, y and z sizes).
    void blmcbd::SET_size(double new_size_x, double new_size_y, double new_size_z)
    {
        size_x=new_size_x;
        size_y=new_size_y;
        size_z=new_size_z;
    }

    //To set a substance.
    void blmcbd::SET_substance(string new_substance_name)
    {
		substance=GET_substance_number(new_substance_name);
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

		mass=size_x*size_y*size_z*GET_substance_density_solid(substance);
		number_boxels_x = (int) (size_x/MIN_BOXEL_SIZE);
		number_boxels_y = (int) (size_y/MIN_BOXEL_SIZE);
		number_boxels_z = (int) (size_z/MIN_BOXEL_SIZE);
		boxel_size_x=size_x/number_boxels_x;
		boxel_size_y=size_y/number_boxels_y;
		boxel_size_z=size_z/number_boxels_z;
		boxel_mass=boxel_size_x*boxel_size_y*boxel_size_z*GET_substance_density_solid(substance);
		c_boxel temp_boxel;
		temp_boxel.SET_energy(new_temperature);
		temp_boxel.SET_state(new_solid);
		for(int i=0; i<number_boxels_x; i++)
			for(int j=0; j<number_boxels_y; j++)
				for(int g=0; g<number_boxels_z; g++)
					boxel[i][j].push_back(temp_boxel);
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
//		return(boxel[boxel_number_x][boxel_number_y][boxel_number_z].GET_energy());
		//TODO: make new get_energy
    }

    double blmcbd::GET_boxel_area_environment(int boxel_number_x, int boxel_number_y, int boxel_number_z)
	{
		double temp_area=0.0;
		if(boxel[boxel_number_x][boxel_number_y][boxel_number_z].GET_state())
		{
			if(boxel_number_x==0 || !boxel[boxel_number_x-1][boxel_number_y][boxel_number_z].GET_state())
				temp_area+=boxel_size_y*boxel_size_z;
			if(boxel_number_y==0 || !boxel[boxel_number_x][boxel_number_y-1][boxel_number_z].GET_state())
				temp_area+=boxel_size_x*boxel_size_z;
			if(boxel_number_z==0 || !boxel[boxel_number_x][boxel_number_y][boxel_number_z-1].GET_state())
				temp_area+=boxel_size_x*boxel_size_y;
			if(boxel_number_x==number_boxels_x-1 || !boxel[boxel_number_x+1][boxel_number_y][boxel_number_z].GET_state())
				temp_area+=boxel_size_y*boxel_size_z;
			if(boxel_number_y==number_boxels_y-1 || !boxel[boxel_number_x][boxel_number_y+1][boxel_number_z].GET_state())
				temp_area+=boxel_size_x*boxel_size_z;
			if(boxel_number_z==number_boxels_z-1 || !boxel[boxel_number_x][boxel_number_y][boxel_number_z+1].GET_state())
				temp_area+=boxel_size_x*boxel_size_y;
		}
		return(temp_area);
	}

//**************************************Body list manipulations********************************************************

//To add a body to the list of bodies.
void Body_list_manipulator::DO_add_body(string new_name, double new_position_z, double new_position_y, double new_position_x,
	double new_size_x, double new_size_y, double new_size_z, string new_substance_name, double new_temperature,
	bool new_solid)
{
	c_body temp_body;
	temp_body.SET_all(new_name, new_position_z, new_position_y, new_position_x, new_size_x, new_size_y,
		new_size_z, new_substance_name, new_temperature, new_solid);
	body.push_back(temp_body);
}

//*********************************************************************************************************************

//**************************************Environment manipulations******************************************************

		//To set all parametres of environment.
		void Environment_manipulator::c_environment::SET_all(string new_substance_name, double new_temperature)
		{
			substance=GET_substance_number(new_substance_name);
			temperature=new_temperature;
		}

		//To get the temperature of environment.
		double Environment_manipulator::c_environment::GET_temperature(void)
		{
			return(temperature);
		}



//To set all parametres of environment.
void Environment_manipulator::SET_environment_parametres(string new_substance, double new_temperature)
{
	environment.SET_all(new_substance, new_temperature);
}

//To get the temperature of environment.
double Environment_manipulator::GET_environment_temperature(void)
{
	return(environment.GET_temperature());
}

//*********************************************************************************************************************

//To get the number of boxels on the x axis of a body.
int Body_list_manipulator::GET_body_number_boxels_x(int body_number)
{
	return(body[body_number].GET_number_boxels_x());
}

//To get the number of boxels on the y axis of a body.
int Body_list_manipulator::GET_body_number_boxels_y(int body_number)
{
	return(body[body_number].GET_number_boxels_y());
}

//To get the number of boxels on the z axis of a body.
int Body_list_manipulator::GET_body_number_boxels_z(int body_number)
{
	return(body[body_number].GET_number_boxels_z());
}

double Body_list_manipulator::GET_body_boxel_temperature(int body_number, int boxel_number_x, int boxel_number_y, int boxel_number_z)
{
	return(body[body_number].GET_boxel_temperature(boxel_number_x, boxel_number_y, boxel_number_z));
}
