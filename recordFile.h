# ifndef RECORDFILE_H
# define RECORDFILE_H

# include <vector>
# include <string>
# include <iostream>
# include <fstream>
# include "Field.h"
# include "Record.h"
# include "index.h"
//# include "primaryindex.h"

using namespace std;

const char DELETED = '*';
const char EQUALS = '-';

class recordFile{
public:
	recordFile(int, int, bool, int);
	recordFile();
	~recordFile();
	vector<string> getIndexRecordRRN()const;
	vector<string> getIndexRecordKey()const;
	int getCurrPosition(vector<string>, unsigned long);
	void recordToBinary();
	void indexRecord();
	void setFileName(string);	
	void addRecord(Record);
	bool addField(Record);
	int getField_Length();
	void setRecord(Record);
	void listFields();
	void buscarRecordArbol(int rrn);
	void borrarRecord(long key/*, Arbol*/);
	//void crearArbol(Arbol);
	void listRecords(string);
	void setInputRecord(char*);
	bool open(string = "", ios_base::openmode = ios_base::in | ios_base::out);
	bool close();
	void setRegistryName(string);
	int PosicionIngresoOrdenadoAlIndice(vector<string>, int);
	string getstring();
	void setFlagTTRecords(bool);
	void writeIndexRecord();

	fstream fs;
	string filename;
	ios_base::openmode flags;//banderas para saber de que modo fue abierto el archivo
	int field_length;

private:	
	Record record;
	bool flatTTRecord;
	bool flag_field;
	bool flag_record;
	int HeaderSize;
	string registryName;
	vector<char*> records;
	vector<string> indexRecordRRN;
	vector<string> indexRecordKey;	
	int record_length;
	int rrn;
	int recordNumber;
	bool indexFlag;
};
#endif