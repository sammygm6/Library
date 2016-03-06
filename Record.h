#pragma once 

# include <vector>
# include <string>
# include "Field.h"

using std::vector;
using std::string;

class Record{
public:
	Record(vector<Field>, vector<string>);	
	Record();
	void setCampos(vector<Field>);
	vector<Field> getFields()const;
	vector<string> getRecords()const;
	Field getFieldAt(int index)const;
	string getRecordAt(int index)const;
	void setField(Field);
	virtual string toString()const;

 	vector<Field> campos;
 	vector<string> records;
};
