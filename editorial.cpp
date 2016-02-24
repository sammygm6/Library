#include "editorial.h"


editorial::editorial(int id,char* nombre,char* direccion){
	this->id = id;
	this->nombre = nombre;
	this->direccion = direccion;
}
editorial::editorial(){
 //do nothing
}
int editorial::getID(){
	return this->id;
}
char* editorial::getNombre(){
	return this->nombre;
}
char* editorial::getDireccion(){
	return this->direccion;
}
void editorial::setID(int id){
	this-> id = id;
}
void editorial::setNombre(char* nombre){
	this->nombre = nombre;
}
void editorial::setDireccion(char* direccion){
	this->direccion = direccion;
}