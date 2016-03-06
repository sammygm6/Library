# include "recordFile.h"
# include <sstream>
# include <cstdlib>
# include <ncurses.h>
# include "index.h"

using namespace std;

recordFile::recordFile(int rrn, int recordNumber, bool indexflag, int record_length){
	this->rrn = rrn;
	this->recordNumber = recordNumber;
	this->indexFlag = indexflag;
	this->record_length = record_length;
}
bool recordFile::close(){
	fs.flush();
	fs.close();
	return !fs.is_open();
}

bool recordFile::open(string path, ios_base::openmode flags){
	this->filename = path;
	this->flags = flags;
	fs.open(this->filename.c_str(), this->flags);

	return fs.is_open();
}

int recordFile::getField_Length(){
	return field_length;
}

recordFile::recordFile(){
	this->rrn = -1;
	this->recordNumber = 0;
	this->indexFlag = 0;
	this->record_length = 0;
	this->HeaderSize = sizeof(int)+sizeof(int)+sizeof(int)+sizeof(int)+field_length;
	this->flag_field = false;
	this->flag_record = false;
}
void recordFile::setFileName(string path){
	this->filename = path;
}

void recordFile::setRegistryName(string registryName){
	this->registryName = registryName;
}
recordFile::~recordFile(){}
vector<string> recordFile::getIndexRecordRRN()const{
	return this->indexRecordRRN;
}
vector<string> recordFile::getIndexRecordKey()const{
	return this->indexRecordKey;
}

void recordFile::setInputRecord(char* input){
	this->records.push_back(input);
}

void recordFile::listFields(){// A MEDIAS
	rrn = -1;
	recordNumber = 0;
	int recordLength = 0;
	indexFlag = 0;	
	ifstream readFile(registryName.c_str(), ios::binary);
	vector<Field*> fields;
	Field* read_field;	
	bool indexFlag;
	int size_field;	
	readFile.read(reinterpret_cast<char*>(&indexFlag), sizeof(bool));
	readFile.read(reinterpret_cast<char*>(&rrn), sizeof(int));
	readFile.read(reinterpret_cast<char*>(&recordNumber), sizeof(int));
	readFile.read(reinterpret_cast<char*>(&size_field), sizeof(int));
	
	if(flag_field == true){
		for (int i = 0; i < size_field; i++){		
			Field curr_f;
			readFile.read(reinterpret_cast<char*>(&curr_f), sizeof(Field));
			//record.setField(curr_f);
		}
	}
	readFile.close();
	printw("\n=============Campos ingresados===============");
	for (int i = 0; i < record.campos.size(); ++i){	
		printw("\n-> %s", record.campos.at(i).getName().c_str());
	}
	getch();	
	flag_field = false;	
}

void recordFile::listRecords(string registry){
	rrn = -1, recordNumber = 0;
	int endFile = 0;
	ifstream readFile(registry.c_str(), ios::binary);
	readFile.read(reinterpret_cast<char*>(&record_length), sizeof(int));
	readFile.read(reinterpret_cast<char*>(&rrn), sizeof(int));
	readFile.read(reinterpret_cast<char*>(&recordNumber), sizeof(int));	
	printw("Tellp para los records = %d ", readFile.tellg());	
	printw("Record Number = %d ", recordNumber);	
	printw("\n=============Registros Ingresados===============");	
	if(flatTTRecord == false){
		char* key_field;
		//while(endFile < recordNumber){
		for (int i = 0; i < records.size(); i++){
			char buffer[sizeof(records.at(i))];
			readFile.read((char*)buffer, sizeof(buffer));
			if(record.campos.at(i).isKey()){
				key_field = records.at(i);
			}
			/*if(key_field[0] != '*'){
				printw("\n-> %s: %s", record.campos.at(endFile).getName().c_str(), buffer);
			}*/
			printw("\n-> %s: ", record.campos.at(i).getName().c_str());
			printw("%s", buffer);
		}
		//char key_field[record.campos.at(endFile).getSize()];				
		//endFile++;
	}else{
		readFile.seekg(sizeof(int)+sizeof(int)+sizeof(int));
		char idPerson[10];
		char name[32];
		char age[4];
		char country[32];
		while(endFile < recordNumber){
			readFile.read((char*)idPerson, sizeof(idPerson));
			readFile.read((char*)name, sizeof(name));
			readFile.read((char*)age, sizeof(age));
			readFile.read((char*)country, sizeof(country));
			if(idPerson[0] != '*'){
				printw("\n==============================================\n");
				printw("\nID: %s", idPerson);
				printw("\nNombre: %s", name);
				printw("\nEdad: %s", age);
				printw("\nPais: %s", country);
			}
			endFile++;
		}
	}
	//}

	readFile.close();
	getch();
}

void recordFile::setRecord(Record r){
	this->record = r;
}

void recordFile::recordToBinary(){		
	ifstream personRecord("Personas.txt");		
	ofstream outputFile(registryName.c_str());
	vector<Field> fields = this->record.campos;
	int size_field = 0;
	outputFile.seekp(0);	
	outputFile.write(reinterpret_cast<char*>(&indexFlag), sizeof(bool));	
	outputFile.write(reinterpret_cast<char*>(&rrn), sizeof(int));	
	outputFile.write(reinterpret_cast<char*>(&recordNumber), sizeof(int));
	outputFile.write(reinterpret_cast<char*>(&size_field), sizeof(int));
	char EndOfFile;
	if(flatTTRecord == true){
		Field campo1("ID", INT_DATA, 10, 255, true);
		Field campo2("Nombre", STRING_DATA, 40, 255, false);
		Field campo3("Edad", INT_DATA, 4, 255, false);
		Field campo4("Pais", STRING_DATA, 32, 255, false);
		record.campos.push_back(campo1);
		record.campos.push_back(campo2);
		record.campos.push_back(campo3);
		record.campos.push_back(campo4);
		for (int i = 0; i < record.campos.size(); i++){
			outputFile.write(reinterpret_cast<char*>(&record.campos.at(i)), sizeof(Field));
			size_field++;
		}
		outputFile.seekp(0);
		outputFile.seekp(sizeof(bool)+sizeof(int)+sizeof(int));
		outputFile.write(reinterpret_cast<char*>(&size_field), sizeof(int));
		while(personRecord>>EndOfFile){
			char name[40];		
			char idPerson[10];		
			char age[4];		
			char country[32];
			string temp_name = "", temp_id = "" , temp_age = "", temp_country = "";
			getline(personRecord, temp_name, ',');			
			getline(personRecord, temp_id, ',');				
			getline(personRecord, temp_age, ',');			
			getline(personRecord, temp_country, ',');			
			for (int i = 0; i < sizeof(name); i++){
				name[i] = temp_name[i];
			}
			for (int i = 0; i < sizeof(idPerson); i++){
				idPerson[i] = temp_id[i];
			}		
			for (int i = 0; i < sizeof(age); i++){
				age[i] = temp_age[i];
			}
			for (int i = 0; i < sizeof(country); i++){
				country[i] = temp_country[i];
			}
			bool cadenaVacia = true;
			for (int i = 0; i < sizeof(name); i++){
				if(name[i] != '\0' && name[i] != ' ')
					cadenaVacia = false;
			}			
			if(!cadenaVacia){				
				outputFile.write((char*)idPerson, sizeof(idPerson));
				outputFile.write((char*)name, sizeof(name));			
				outputFile.write((char*)age, sizeof(age));
				outputFile.write((char*)country, sizeof(country));
				recordNumber++;
				outputFile.seekp(0);
		  		outputFile.seekp (sizeof(bool)+sizeof(int));
		  		outputFile.write(reinterpret_cast<char*>(&recordNumber), sizeof(recordNumber));
		  		//outputFile.seekp(sizeof(int)*2 +1 +(recordNumber*86));
			}			
		}		

	}
	personRecord.close();
	outputFile.close();	
}
void recordFile::indexRecord(){ //funcion para los indices del registro
	indexRecordKey.clear();
	ifstream readFile(registryName.c_str(), ios::binary);
	vector<Field> fields = this->record.getFields();
	readFile.seekg(sizeof(bool)+sizeof(int)+sizeof(int)+sizeof(int)+record.campos.size());
	int cont = 0;
	if(flatTTRecord == false){
		while(true){
			stringstream rrn;
			if(readFile.eof())
				break;

			for (int i = 0; i < fields.size(); i++){
				char buffer[fields.at(i).getSize()];
				readFile.read((char*)buffer, sizeof(buffer));
				if(fields.at(i).isKey()){
					bool iguales = false;
					for (int i = 0; i < sizeof(buffer)-1; i++){
						if(buffer[i] == '*'){
							iguales = true;
							break;
						}
					}
					if(!iguales){
						stringstream ss;
						for (int i = 0; i < sizeof(buffer); i++){
							ss << buffer[i];
						}
						rrn << cont;
						unsigned long key = atol(ss.str().c_str());
						int posicion = getCurrPosition(indexRecordKey, key);
						if(posicion == -1){
							indexRecordKey.push_back(ss.str());
							indexRecordRRN.push_back(rrn.str());
						}else{
							indexRecordKey.insert(indexRecordKey.begin() + posicion, ss.str());
							indexRecordRRN.insert(indexRecordRRN.begin() + posicion, rrn.str());
						}
					}
				}
			}		
			cont++;
		}
	}else{
		indexRecordKey.clear();
		indexRecordKey.clear();
		ifstream readFile(registryName.c_str(),ios::binary);
		readFile.seekg(sizeof(bool)+sizeof(int)+sizeof(int)+sizeof(int)+record.campos.size());
		int cont = 0;
	 	while(true){
			stringstream rrn ;
			if(readFile.eof())
				break;
			char idPerson[10];
			char name[32];
			char age[4];
			char country[32];
			readFile.read((char*)idPerson, sizeof(idPerson));
			readFile.read((char*)name, sizeof(name));
			readFile.read((char*)age, sizeof(age));
			readFile.read((char*)country, sizeof(country));
			bool iguales = false;
			for (int i = 0; i < sizeof(idPerson)-1; i++)
			{
				if(idPerson[i] == '*'){
					iguales = true;	
					break;			
				}
			}
			if(!iguales){
				stringstream ss;
				for (int i = 0; i < sizeof(idPerson); i++)
				{							
					ss<< idPerson[i];	
					cout << "ss = " << ss.str() << endl;
				}			
				rrn<< cont;
				unsigned long key = atol(ss.str().c_str());
				cout << "key = " << key << endl;
				int position = getCurrPosition(indexRecordKey, key);
				if (position == -1){
					indexRecordKey.push_back(ss.str());
					indexRecordRRN.push_back( rrn.str());
				}else{
					indexRecordKey.insert(indexRecordKey.begin() + position, ss.str());
					indexRecordRRN.insert(indexRecordRRN.begin() + position, rrn.str());
				}

			}
			cont++;

		}/*
		for (int i = 0; i < indexClientKey.size(); i++)
		{
			cout << "Key: " << indexClientKey.at(i) << " RRN: " << indexClientRRN.at(i)<< endl;
		}	*/		
	}
	readFile.close();
}

void recordFile::buscarRecordArbol(int rrn){
	char idPerson[10];
	char name[32];
	char age[4];
	char country[32];
	ifstream readFile(registryName.c_str(),ios::binary);	
	readFile.seekg(HeaderSize + (sizeof(idPerson) + sizeof(name)+sizeof(age)+sizeof(country)) * rrn );
	readFile.read((char*)idPerson, sizeof(idPerson));
	readFile.read((char*)name, sizeof(name));
	readFile.read((char*)age, sizeof(age));
	readFile.read((char*)country, sizeof(country));
	printw("\n----------------------------------------------------------------------------\n");
	printw("Id Persona: %s\n",idPerson);
	printw("Nombre: %s\n: ", name);
	printw("Edad: %s\n: ", age);
	printw("Pais: %s\n: ", country);	
	readFile.close();
}
int recordFile::getCurrPosition(vector<string> indexKey, unsigned long key){
	int low = 0;
	int high = indexKey.size() -1;
	int mid;
	bool avoidInfiniteCicle = false;

	while(true){
		if(low > high)
			break;
		mid = (low + high)/2;
		if(key == atol((indexKey.at(mid)).c_str())){
			return mid;
		}

		if(key > atol((indexKey.at(mid)).c_str())){
			if(mid != indexKey.size() -1){
				if(key < atol((indexKey.at(mid+1)).c_str())){
					return -1;
				}else{ 
					if(avoidInfiniteCicle && mid == indexKey.size()-2){
						return -1;
					}
					low = mid;
					avoidInfiniteCicle = true;
				}
			}else{
				if(key < atol((indexKey.at(mid)).c_str())){
					return -1;
				}else{
					return -1;
				}
			}
		}else{
			if(mid != 0){
				if(key > atol((indexKey.at(mid-1)).c_str())){
					return -1;
				}else{
					high = mid;
				}
			}else{
				if(key < atol((indexKey.at(mid)).c_str())){
					return -1;
				}else{
					return -1;
				}
			}
		}
	}
	return -1;
}
void recordFile::addRecord(Record record){	
	ifstream readFile(registryName.c_str(), ios::binary);	
	int newRRNHeader = 0;
	int record_length, size_field = 0, cont = 0;
	bool indexFlag;		
	readFile.seekg(0);	
	readFile.read(reinterpret_cast<char*>(&indexFlag), sizeof(bool));
	readFile.read(reinterpret_cast<char*>(&rrn), sizeof(int));		
	readFile.read(reinterpret_cast<char*>(&recordNumber), sizeof(int));		
	readFile.read(reinterpret_cast<char*>(&size_field), sizeof(int));		
	Field curr_f;	
	for (int i = 0; i < size_field; i++){						
		readFile.read(reinterpret_cast<char*>(&curr_f), sizeof(Field));			
		record.campos.push_back(curr_f);		
	}	
	char buffer[sizeof(curr_f.getSize())];
	readFile.seekg(HeaderSize + rrn*(recordNumber));		
	if(flatTTRecord == true){		
		readFile.read(reinterpret_cast<char*>(&buffer), sizeof(buffer));
		stringstream streamNombre;
		for (int i = 0; i < sizeof(buffer); i++){
			streamNombre << buffer[i];
		}
		newRRNHeader = atoi(streamNombre.str().c_str());		
	}
	readFile.close();	
    nocbreak();
    echo();  
    vector<char*>  list_inputs;
	if(rrn != -1){
		stringstream ss;
		for (int i = 0; i < size_field; i++){			
			char input[record.campos.at(i).getSize()];
			printw("\nIngrese el %s ", record.campos.at(i).getName().c_str());
			getstr(input);
			list_inputs.push_back(input);
			setInputRecord(input);
			if(record.campos.at(i).isKey()){
				for (int i = 0; i < sizeof(record.campos.at(i).getSize()); i++){
					ss << input[i];
				}
			}
		}
		stringstream ssRRNHeader;
		ssRRNHeader << rrn;
		ofstream writeFile(registryName.c_str(), ofstream::in | ofstream::out);
		writeFile.seekp(HeaderSize + rrn*(recordNumber));
		for (int i = 0; i < list_inputs.size(); i++){
			char* buffer_output = list_inputs.at(i);
			writeFile.write(reinterpret_cast<char*>(&buffer_output), sizeof(buffer_output));			
		}		
		writeFile.seekp(sizeof(int));
		writeFile.write(reinterpret_cast<char*>(&newRRNHeader), sizeof(newRRNHeader));
		writeFile.close();
		int position = PosicionIngresoOrdenadoAlIndice( indexRecordKey  , atoi(ss.str().c_str()) );
		if(flatTTRecord == true){
			indexRecordKey.insert(indexRecordKey.begin()+ position, ss.str());
			indexRecordRRN.insert(indexRecordRRN.begin()+ position, ssRRNHeader.str());
		}
		//arbol.Agregar(index(atol(ss.str().c_str()) , rrn));
	}else{
		stringstream streamId;
		for (int i = 0; i < size_field; i++){			
			char input[record.campos.at(i).getSize()];
			printw("\nIngrese el %s ", record.campos.at(i).getName().c_str());
			getstr(input);
			list_inputs.push_back(input);
			setInputRecord(input);
			if(record.campos.at(i).isKey()){
				for (int i = 0; i < sizeof(record.campos.at(i).getSize()); i++){
					streamId << input[i];
				}
			}			
		}
		getch();
		ofstream writeFile(registryName.c_str(), ofstream::in | ofstream::out);
		if(rrn == -1){			
			writeFile.seekp(HeaderSize+(recordNumber-1)*(recordNumber));
		}else{			
			writeFile.seekp(HeaderSize+recordNumber*(recordNumber));
		}			
		stringstream ssRecordNumber;		
		ssRecordNumber << recordNumber;		
		int position = PosicionIngresoOrdenadoAlIndice( indexRecordKey  , atoi(streamId.str().c_str()) );		
		writeFile.seekp(HeaderSize + rrn*(recordNumber));		
		for (int i = 0; i < list_inputs.size(); i++){
			char* buffer_output = list_inputs.at(i);
			writeFile.write(reinterpret_cast<char*>(&buffer_output), sizeof(buffer_output));			
		}		
		recordNumber++;					
		writeFile.seekp(0);
		writeFile.seekp(sizeof(int)+sizeof(int));
		writeFile.write(reinterpret_cast<char*>(&recordNumber), sizeof(int));
		writeFile.close();
		if(flatTTRecord == true){					
			indexRecordKey.insert(indexRecordKey.begin()+ position, streamId.str());			
			indexRecordRRN.insert(indexRecordRRN.begin()+ position, ssRecordNumber.str());
		}
		//arbol.Agregar(index(atol(streamId.str().c_str()) , recordNumber-1));
	}
	list_inputs.clear();
	record.campos.clear();	
}

bool recordFile::addField(Record rec){	
	flag_field = true;
	this->record = rec;
	ofstream outputFile(registryName.c_str(), ofstream::in | ofstream::out);
	ifstream readFile(registryName.c_str(), ios::binary);		
	int record_length, cont = 0;
	bool indexFlag;
	readFile.read(reinterpret_cast<char*>(&indexFlag), sizeof(bool));
	readFile.read(reinterpret_cast<char*>(&rrn), sizeof(int));
	readFile.read(reinterpret_cast<char*>(&recordNumber), sizeof(int));
	outputFile.seekp(readFile.tellg());	
	int size_field = record.campos.size();		
	
	outputFile.write(reinterpret_cast<char*>(&size_field), sizeof(int));
	for (int i = 0; i < record.campos.size(); i++){
		Field curr_f = record.campos.at(i);
		outputFile.write(reinterpret_cast<char*>(&curr_f), sizeof(Field));
		field_length++;
	}
	readFile.close();
	outputFile.close();		
	return true;
}

int recordFile::PosicionIngresoOrdenadoAlIndice(vector<string> indexKey  , int key){
    int low = 0;
    int high = indexKey.size() - 1;
    int mid;
    bool avoidInfiniteCicle = false;
    
    while(true){
    	if(low > high)
    		break;    	
    	mid = (low + high)/2;
    	if(key == atoi((indexKey.at(mid)).c_str()) )
    		return mid;
    	if(key > atoi((indexKey.at(mid)).c_str())){
    		if(mid != indexKey.size() - 1){
    			if(key < atoi((indexKey.at(mid+1)).c_str())){
    				return mid+1;
    			}else{
    				if(avoidInfiniteCicle && mid == indexKey.size()-2)
    					return -1;
    				low = mid;
    				avoidInfiniteCicle = true;
    			}
    		}else{
    			if(key < atoi((indexKey.at(mid)).c_str())){
    				return mid;
    			}else{
    				return -1;
    			}

    		}
    	}else{
    		if(mid != 0){
    			if(key > atoi((indexKey.at(mid-1)).c_str())){

    				return mid;
    			}else{
    				high = mid;
    			}
    		}else{
    			if(key < atoi((indexKey.at(mid)).c_str())){
    				return mid;
    			}else{
    				return mid+1;
    			}

    		}
    	}
    }
    return -1;
}

string recordFile::getstring(){
    string input;
    nocbreak();
    echo();

    int ch = getch();

    while ( ch != '\n' ){
        input.push_back( ch );
        ch = getch();
    }    

    return input;
}

void recordFile::setFlagTTRecords(bool flagTTRecord){
	this->flatTTRecord = flagTTRecord;
}

/*void recordFile::crearArbol(Arbol tree){
	rrn = -1;
	int record_length = 0;
	recordNumber = 0;
	int endFile = 0;
	int size_field = 0;
	int cont = 0;	
	unsigned long agregado = 0;
	ifstream readFile(registryName.c_str(), ios::binary);	
	if(flatTTRecord == true){
		readFile.read(reinterpret_cast<char*>(&record_length), sizeof(int));
		readFile.read(reinterpret_cast<char*>(&rrn), sizeof(int));
		readFile.read(reinterpret_cast<char*>(&recordNumber), sizeof(int));
		readFile.read(reinterpret_cast<char*>(&size_field), sizeof(int));
		readFile.seekg(sizeof(int)+sizeof(int)+sizeof(int)+sizeof(int));		
		while(endFile < recordNumber){
			char name[32];
			char idPerson[10];
			char age[4];
			char country[32];

			readFile.read((char*)name, sizeof(name));
			readFile.read((char*)idPerson, sizeof(idPerson));
			readFile.read((char*)age, sizeof(age));
			readFile.read((char*)country, sizeof(country));
			stringstream ss;
			for (int i = 0; i < sizeof(idPerson); i++){
				ss << idPerson[i];
			}
			if(idPerson[0] != '*'){
				agregado = atol(ss.str().c_str());
				index ingresado(agregado, cont);
				tree.Agregar(ingresado);
			}
			endFile++;
			cont++;
		}
	}
}*/

void recordFile::borrarRecord(long key/*, Arbol tree*/){
	char name[32];
	char idPerson[10];
	char age[4];
	char country[32];
	int position = getCurrPosition(indexRecordKey, key);
	string rrn = indexRecordRRN.at(position);
	int rrnInteger = atoi(rrn.c_str());
	stringstream rrnToString;
	ifstream readFile(registryName.c_str(), ios::binary);
	readFile.seekg(0);
	int record_length, rrnHeader, recordNumber;
	readFile.read(reinterpret_cast<char*>(&record_length), sizeof(int));
	readFile.read(reinterpret_cast<char*>(&rrnHeader), sizeof(int));
	readFile.read(reinterpret_cast<char*>(&recordNumber), sizeof(int));
	readFile.close();
	ofstream writeFile(registryName.c_str(), ios::out | ios::in);
	if(position != -1){
		idPerson[0] = '*';
		rrnToString << rrnHeader;
		for (int i = 0; i < rrnToString.str().size(); i++){
			name[i] = rrnToString.str()[i];
		}
		if(atoi(rrn.c_str()) == recordNumber){
			writeFile.seekp(HeaderSize + (atoi((rrn).c_str()) -1)*(sizeof(idPerson) + sizeof(name) +sizeof(age) + sizeof(age) + sizeof(country)));
		}else{
			writeFile.seekp(HeaderSize + (atoi((rrn).c_str()))*(sizeof(idPerson) + sizeof(name) +sizeof(age) + sizeof(age) + sizeof(country)));
		}
		writeFile.write(reinterpret_cast<char*>(&idPerson), sizeof(idPerson));
		writeFile.write(reinterpret_cast<char*>(&name), sizeof(name));
		writeFile.seekp(0);
		writeFile.seekp(sizeof(int));
		writeFile.write(reinterpret_cast<char*>(&rrnInteger), sizeof(rrnInteger));
		indexRecordKey.erase(indexRecordKey.begin() + position);
		indexRecordRRN.erase(indexRecordRRN.begin()+position);
		//tree.Eliminar(index((unsigned long)key, atoi(rrn.c_str())));
		writeFile.close();
	}
}

void recordFile::writeIndexRecord(){
	ofstream markFile(registryName.c_str());
	bool indexFlag = true;
	markFile.write(reinterpret_cast<char*>(&indexFlag), sizeof(indexFlag));
	markFile.close();
	ofstream outputFile("indexRecord.bin");
	for (int i = 0; i < indexRecordRRN.size(); i++){
		outputFile.write(reinterpret_cast<char*>(&indexRecordKey[i]), sizeof(indexRecordKey[i]));
		outputFile.write(reinterpret_cast<char*>(&indexRecordRRN[i]), sizeof(indexRecordRRN[i]));
	}
	outputFile.close();
	ofstream remarkFile(registryName.c_str());
	indexFlag = false;
	remarkFile.write(reinterpret_cast<char*>(&indexFlag), sizeof(indexFlag));
	remarkFile.close();
}