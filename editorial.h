#pragma once
#import <string>

class editorial
{
	int id;
	string nombre;
	string direccion;
public:
	editorial(int,string,string);
	editorial();
	int getID();
	string getNombre();
	string getDireccion();
	void setID(int);
	void setNombre(string);
	void setDireccion(string);
};