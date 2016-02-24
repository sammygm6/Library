#include "libro.h"


libro::libro(char* id,char* nombre,char* autor,int idEditorial){
	this->id = id;
	this->nombre = nombre;
	this->autor = autor;
	this->idEditorial = idEditorial;
}
libro::libro(){
//do nothingg
}
char* libro::getID(){
	return this->id;
}
char* libro::getNombre(){
	return this->nombre;
}
char* libro::getAutor(){
	return this->autor;
}
int libro::getidEditorial(){
	return this->idEditorial;
}
void libro::setID(char* id){

}
void libro::setNombre(char* nombre){
	this->nombre = nombre;
}
void libro::setAutor(char* autor){
	this->autor = autor;
}
void libro::setIDEditorial(int idEditorial){
	this->idEditorial = idEditorial;
}