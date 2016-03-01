#include "libro.h"


libro::libro(string id,string nombre,string autor,int idEditorial){
	this->id = id;
	this->nombre = nombre;
	this->autor = autor;
	this->idEditorial = idEditorial;
}
libro::libro(){
//do nothingg
}
string libro::getID(){
	return this->id;
}
string libro::getNombre(){
	return this->nombre;
}
string libro::getAutor(){
	return this->autor;
}
int libro::getidEditorial(){
	return this->idEditorial;
}
void libro::setID(string id){

}
void libro::setNombre(string nombre){
	this->nombre = nombre;
}
void libro::setAutor(string autor){
	this->autor = autor;
}
void libro::setIDEditorial(int idEditorial){
	this->idEditorial = idEditorial;
}