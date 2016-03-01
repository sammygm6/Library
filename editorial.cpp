#include "editorial.h"
#include <string>

editorial::editorial(int id,string nombre,string direccion){
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
string editorial::getNombre(){
	return this->nombre;
}
string editorial::getDireccion(){
	return this->direccion;
}
void editorial::setID(int id){
	this-> id = id;
}
void editorial::setNombre(string nombre){
	this->nombre = nombre;
}
void editorial::setDireccion(string direccion){
	this->direccion = direccion;
}