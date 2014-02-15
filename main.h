#ifndef _MAIN_H_
#define _MAIN_H_

#include <vector>
#include <string>

using std::vector;
using std::string;

namespace MTL {
class Body_list_manipulator
{
private:
	class c_body;
	class c_boxel;
	vector<c_body> body; //The list of bodies.
public:
	void DO_add_body(string new_name, double new_position_z, double new_position_y, double new_position_x,
	double new_size_x, double new_size_y, double new_size_z, string new_substance_name, double new_temperature,
	bool new_solid);
	void DO_delete_body(string body_name);
	static int GET_body_number_boxels_x(int body_number);
	int GET_body_number_boxels_y(int body_number);
	int GET_body_number_boxels_z(int body_number);
	double GET_body_boxel_temperature(int body_number, int boxel_number_x, int boxel_number_y, int boxel_number_z);
};


class Body_list_manipulator::c_boxel{
private:
    double energy;             //Temperature of a boxel (C).
    bool is_solid;						//State of a boxel (solid/liquid).
public:

	//To set a new temperature.
	void SET_energy(double new_temperature);

	//To set a state of a boxel.
	void SET_state(bool new_solid);

	//To get energy
	double GET_energy(void);

	bool GET_state(void);
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

    double GET_boxel_area_environment(int boxel_number_x, int boxel_number_y, int boxel_number_z);
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
	void SET_environment_parametres(string new_substance, double new_temperature);
	double GET_environment_temperature(void);
};
}
<<<<<<< HEAD
=======

#endif
>>>>>>> c028b56f126d7c54a81fa310e03070f71b40909a
