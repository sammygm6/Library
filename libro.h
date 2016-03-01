#pragma once

class libro
{
	string id;
	string nombre;
	string autor;
	int idEditorial;
public:
	libro(string,string,string,int);
	libro();
	string getID();
	string getNombre();
	string getAutor();
	int getidEditorial();
	void setID(string);
	void setNombre(string);
	void setAutor(string);
	void setIDEditorial(int);
};