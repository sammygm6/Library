# pragma once
# include <string>
# include <sstream>

using std::string;
using namespace std;
//dataTypes predefined

typedef char dataType;
const dataType INT_DATA = 'i';
const dataType DOUBLE_DATA = 'd';
const dataType STRING_DATA = 's';

//lengths
const int FIELD_LENGTH = 30;
const int DECIMAL_PLACES_LENGTH = 3;
const int DATA_TYPE_LENGTH = 1;
const int KEY_LENGTH = 1;
const int LENGTH_LENGTH = 3;

//default Values

const string D_INT_VAL = "0";
const string D_DOUBLE_VAL = "0.0";
const string D_STRING_VAL = "NULL";

class Field{
public:
	Field(string, dataType, int, int, bool);
	Field();
	void setName(string);
	void setDataType(dataType);
	void setSize(int);
	void setKey(bool);
	string getName()const;
	dataType getDataType()const;
	int getSize()const;
	int getDecimalSize()const;
	bool isKey()const;
	virtual string toString()const;
private:
	string name;
	dataType data_type;
	int size;
	int size_dec;
	bool key;
};