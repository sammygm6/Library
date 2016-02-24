#pragma once

class editorial
{
	int ID;
	char* nombre;
	char* direccion;
public:
	editorial();
	~editorial();
	int getID();
	char* getNombre();
	char* getDireccion();
	void setID(const int);
	void setNombre(const char*);
	void setDireccion(const char*);
};