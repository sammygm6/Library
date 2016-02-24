#pragma once
#include <string>

using std::string;

class libro
{
	char* id;
	char* nombre;
	char* autor;
	int idEditorial;
public:
	libro(string,string,string,int);
	libro();
	char* getID();
	char* getNombre();
	char* getAutor();
	int getidEditorial();
	void setID(const char*);
	void setNombre(const char*);
	void setAutor(const char*);
	void setIDEditorial(const int);
};