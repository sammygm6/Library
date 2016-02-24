#pragma once
#include <string>

using std::string;

class libro
{
	char[10] id;
	char[10] nombre;
	char[10] autor;
	int idEditorial;
public:
	libro(string,string,string,int);
	libro();
	~libro();
	char[10] getID();
	char[10] getNombre();
	char[10] getAutor();
	int getidEditorial();
	void setID(const char[10]);
	void setNombre(const char[10]);
	void setAutor(const char[10]);
	void setIDEditorial(const int);
};