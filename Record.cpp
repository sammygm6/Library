# include "Record.h"
# include <sstream>
# include <iomanip>

using std::stringstream;
using std::setw;
using std::setfill;

Record::Record(vector<Field> fields, vector<string> records){
	this->campos = fields;
	this->records = records;
}
Record::Record(){}
vector<Field> Record::getFields()const{
	return this->campos;
}
vector<string> Record::getRecords()const{
	return this->records;
}
Field Record::getFieldAt(int index)const{
	return this->campos.at(index);
}
string Record::getRecordAt(int index)const{
	return this->records.at(index);
}

void Record::setField(Field campo){
	this->campos.push_back(campo);
}
void Record::setCampos(vector<Field> campos){
	this->campos = campos;
}
/*Funcion toString para representar textualmente
 al objeto Record para ser escrito en un archivo*/
string Record::toString()const{
	stringstream ss;
	if(campos.size() != records.size()){
		ss << "Invalid record information\n";
	}else{
		for (int i = 0; i < campos.size(); i++){
			Field curr_f = campos[i];
			ss << "__________" + records[i];
		}
		return ss.str();

	}
}