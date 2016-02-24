#pragma once

class editorial
{
	int id;
	char* nombre;
	char* direccion;
public:
	editorial(int,char*,char*);
	editorial();
	int getID();
	char* getNombre();
	char* getDireccion();
	void setID(int);
	void setNombre(char*);
	void setDireccion(char*);
};