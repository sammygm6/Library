# include "Field.h"
# include <string>
# include <iomanip>

using namespace std;

Field::Field(string name, dataType data_type, int size, 
	int size_dec, bool key){
	this->name = name.substr(0, 32);//catching the first 32 bytes
	this->data_type = data_type;
	this->size = size;
	this->size_dec = size_dec;
	this->key = key;
}
Field::Field(){}
void Field::setName(string name){
	this->name = name.substr(0, 32);//catching the first 32 bytes
}
void Field::setDataType(dataType dt){
	this->data_type = dt;
}
void Field::setSize(int size){
	this->size = size;
}
void Field::setKey(bool key){
	this->key = key;
}
string Field::getName()const{
	return this->name;
}
dataType Field::getDataType()const{
	return this->data_type;
}
int Field::getSize()const{
	return this->size;
}
int Field::getDecimalSize()const{
	return this->size_dec;
}
bool Field::isKey()const{
	return this->key;
}
string Field::toString()const{
	ostringstream ss;
	/*
	ss << setw(FIELD_LENGTH) << setfill('_') << this->getName()
	<< setw(DATA_TYPE_LENGTH) << this->getDataType()
	<< setw(LENGTH_LENGTH) << setfill('0') << this->getSize()
	<< setw(DECIMAL_PLACES_LENGTH) << setfill('0') << this->getDecimalSize()
	<< setw(KEY_LENGTH) << this->isKey() ? '1' : '0';
	*/
	return ss.str();
}
