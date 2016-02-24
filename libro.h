#pragma once

class libro
{
	char* id;
	char* nombre;
	char* autor;
	int idEditorial;
public:
	libro(char*,char*,char*,int);
	libro();
	char* getID();
	char* getNombre();
	char* getAutor();
	int getidEditorial();
	void setID(char*);
	void setNombre(char*);
	void setAutor(char*);
	void setIDEditorial(int);
};
int main()
{
	/* code */
	return 0;
}