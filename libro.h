#pragma once
#include <string>

using std::string;

class libro
{
	string id;
	string nombre;
	string autor;
	int idEditorial;
public:
	libro(string,string,string,int);
	libro();
	~libro();
	string getID();
	string getNombre();
	string getAutor();
	int getidEditorial();
	void setID(const string);
	void setNombre(const string);
	void setAutor(const string);
	void setIDEditorial(const int);
};