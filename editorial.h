#pragma once

class editorial
{
	int ID;
	char[10] nombre;
	char[10] direccion;
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