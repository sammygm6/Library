# include <ncurses.h>
# include <string>
# include <cstdlib>
# include <fstream>
# include "Menu.h"
# include "recordFile.h"
# include "Field.h"
# include "index.h"
# include <ctime>

using namespace std;
int interface_main(Menu, int);
string getstring();
string generarNombreLibro();
string generarIDLibro();
string generarIDEditorialLibro();
string generarAutorLibro();

int cont_registros = 1;
long int cont_ISBN = 999999999;
recordFile current_open_file;//referencia archivo abierto

int main(int argc, char const *argv[]){
	srand(time(0));
	Menu menu;	
	initscr();	
	move(0, 0);
	printw("Desea ejecutar el programa cargando mil registros?\n1.Si\n2.No\n");
	refresh();
	int opc = atoi(getstring().c_str());
	vector<Field> fields;
	vector<string> campos;	
	int orden = 7;
	//Arbol arbolRecord(orden);
	Record record;
	current_open_file.setRecord(record);
	bool TTRecord = false;	
	bool file_opened = false;	
	do{
		clear();
		cbreak();
		if(file_opened == true){
			move(0, 0);
			printw("Archivo: %s", current_open_file.filename.c_str());
			refresh();
		}
		if(opc == 1){
			ofstream myfile;
			myfile.open("Libros.txt");
			for (int i = 0; i < 1000; i++){
				myfile << generarIDLibro() << "," << generarNombreLibro() << "," << generarAutorLibro() << "," << generarIDEditorialLibro() << ",";
			}
			myfile.close();
			TTRecord = true;
			current_open_file.setFlagTTRecords(TTRecord);
			move(0, 55);
			printw("File loaded: Personas.txt");
			refresh();
			move(23, 0);
			printw("Debera de cargar el archivo para fabricar el binario....");
			refresh();			
			opc = 0;
		}			
		int opc_returned = interface_main(menu, 1); // main_menu
		if(opc_returned == 0){//file menu
			clear();
			opc_returned = interface_main(menu, 2);
			string file_name;
			switch(opc_returned){
				case 0:
					clear();
					move(0, 29);
					printw("...NUEVO ARCHIVO...");
					move(2, 0);
					if(current_open_file.fs.is_open()){
						current_open_file.fs.close();
					}
					printw("Nombre del archivo: ");	
					refresh();
					file_name = getstring();
					current_open_file.setFileName(file_name);
					current_open_file.setRegistryName(file_name);
					current_open_file.recordToBinary();
					file_opened = true;
					move(22, 0);
					printw("Archivo abierto con exito!!!");
					move(23, 0);
					printw("Presiones cualquier tecla para continuar");
					refresh();
					getch();					
				break;
				case 1:
					clear();
					move(10, 29);
					printw("...GUARDAR ARCHIVO...");
					refresh();
					if(current_open_file.fs.flush()){
						move(22, 0);
						printw("Archivo guardado con exito!!!");
						move(23, 0);;
						printw("Presione cualquie tecla para continuar");
						refresh();
						getch();
					}else{
						move(22, 0);
						printw("Error al guardar el archivo!!!");
						move(23, 0);;
						printw("Presione cualquie tecla para continuar");
						refresh();
						getch();
					}
					getch();
				break;
				case 2:
					clear();
					move(10, 29);
					printw("...CERRAR ARCHIVO...");
					refresh();
					if(current_open_file.close()){
						move(22, 0);
						printw("Archivo cerrado con exito!!!");
						move(23, 0);;
						printw("Presione cualquie tecla para continuar");
						refresh();
						getch();
					}else{
						move(22, 0);
						printw("Error al cerrar el archivo");
						move(23, 0);;
						printw("Presione cualquie tecla para continuar");
						refresh();
						getch();
					}					
				break;
				default:
					clear();
					move(0, 29);
					printw("...CARGAR 10 MIL REGISTROS...");
					move(2, 0);
					if(current_open_file.fs.is_open()){
						current_open_file.fs.close();
					}
					printw("Nombre del archivo a guardar: ");	
					refresh();
					file_name = getstring();
					current_open_file.setFileName(file_name);
					current_open_file.setRegistryName(file_name);
					current_open_file.recordToBinary();
					file_opened = true;
					move(22, 0);
					printw("Archivo guardado con exito!!!");
					move(23, 0);
					printw("Presiones cualquier tecla para continuar");
					refresh();
					getch();
				break;
			}
		}else if(opc_returned == 1){//field_menu
			clear();
			if(file_opened == true){
				move(0, 0);
				printw("Archivo: %s", current_open_file.filename.c_str());
				refresh();
			}
			clear();
			opc_returned = interface_main(menu, 3);
			
			//variables para campos
			string field_name;
			dataType dt;
			int size;
			bool key = false;
			int opc_type;
			int isKey;

			//success message
			int success = 0;
			int opc_cont = 0;
			switch(opc_returned){
				case 0:
				do{
					clear();
					move(0, 29);
					printw("...NUEVO CAMPO...");
					move(2, 0);
					printw("Nombre del campo: ");
					refresh();
					field_name = getstring();
					move(4, 0);
					printw("Tipo de dato:");
					move(5, 0);
					printw("1)Entero");
					move(6, 0);
					printw("2)Double");
					move(7,0);
					printw("3)String");
					refresh();
					opc_type = atoi(getstring().c_str());
					if(opc_type == 1)
						dt = INT_DATA;
					else if(opc_type == 2)
						dt = DOUBLE_DATA;
					else if(opc_type == 3)
						dt = STRING_DATA;
					move(9, 0);
					printw("Tamano del campo: ");
					refresh();
					size = atoi(getstring().c_str());
					move(11, 0);
					printw("Presione (1) si el campo es llave-> ");
					refresh();
					isKey = atoi(getstring().c_str());
					if(isKey == 1)
						key = true;
					Field campo(field_name, dt, size, 255, key);
					record.setField(campo);
					printw("Desea continuar agregando campos? (1)Si (2)No");
					opc_cont = atoi(getstring().c_str());
				}while(opc_cont != 2);
				cout << "Entro al success" << endl;
				success = current_open_file.addField(record);
				if(success == true){
					move(22, 0);
					printw("Exito, campo creado!!!");
					move(23, 0);
					printw("Presiones cualquier tecla para continuar");
					refresh();
					getch();
				}						
				break;
				case 1:
				current_open_file.listFields();

				break;
				case 2:

				break;
				default:

				break;
			}
		}else if(opc_returned == 2){//record_menu
			clear();
			string file_name;
			string id_search;
			string id_delete;
			long key;
			long id;
			int rrn;
			opc_returned = interface_main(menu, 4);			
			if(opc_returned == 0){				
					current_open_file.addRecord(record);
			}else if(opc_returned == 2){//borrar record
				clear();
				move(0, 29);
				printw("...PANEL DE ELIMINACION DE REGISTROS...");
				move(2, 0);
				printw("Ingrese el ID de la persona a eliminar: ");
				refresh();
				id_delete = getstring();
				id = atol(id_delete.c_str());
				current_open_file.borrarRecord(id);
			}else if(opc_returned == 3){//busqueda de record				
				clear();
				move(0, 29);
				printw("...BUSQUEDA DE REGISTROS CON ARBOL B...");
				move(2, 0);
				printw("Ingrese el ID de la persona a buscar: ");
				refresh();
				id_search = getstring();
				/*key = atol(id_search.c_str());
				rrn = arbolRecord.buscar((long)key);
				if(rrn != -1){
					current_open_file.buscarRecordArbol(arbolRecord.buscar((long)key));
				}else{
					move(22, 0);
					printw("No se encontro el registro!!!");
					move(23, 0);
					printw("Presiones cualquier tecla para continuar");
					refresh();
					getch();
				}*/
			}else if(opc_returned == 4){
				clear();
				move(0, 29);
				printw("...Listar registros...");
				move(2, 0);
				printw("Nombre del archivo: ");
				file_name = getstring();
				current_open_file.listRecords(file_name);
			}

		}else if(opc_returned == 3){//index_menu
			clear();
			opc_returned = interface_main(menu, 5);
			switch(opc_returned){
				case 1:
				clear();
				move(0, 29);
				printw("...REINDEXADO...");
				move(2, 0);
				current_open_file.indexRecord();
				move(22, 0);
				printw("Exito, archivo REINDEXADO!!!");
				move(23, 0);
				printw("Presiones cualquier tecla para continuar");
				refresh();
				getch();
				break;
			}
		}else if(opc_returned == 4){//utilities_menu
		}else if(opc_returned == 5){//salir			
			current_open_file.writeIndexRecord();
			if(current_open_file.fs.is_open()){
				current_open_file.fs.close();
			}
			clear();
			endwin();
		}
	}while(true);
	return 0;
}
int interface_main(Menu clase, int type){
	int menuItem = 0;
	int key = 0;
	int MENU_LENGTH;
	if(type == 1){
		clase.main_menu(menuItem);
		MENU_LENGTH = MENUMAX;
	}else if(type == 2){
		clase.files_menu(menuItem);
		MENU_LENGTH = MFILEMAX;
	}else if(type == 3){
		clase.field_menu(menuItem);
		MENU_LENGTH = MFIELDMAX;
	}else if(type == 4){
		clase.record_menu(menuItem);
		MENU_LENGTH = MRECORDMAX;
	}else if(type == 5){
		clase.index_menu(menuItem);
		MENU_LENGTH = MINDEXMAX;
	}else if(type == 6){
		clase.utilities_menu(menuItem);
		MENU_LENGTH = MUTILITIESMAX;
	}
	keypad(stdscr, true);
	noecho();
	do{
		key = getch();
		switch(key){
			case KEY_DOWN:
				menuItem++;
				if(menuItem > MENU_LENGTH - 1)
					menuItem = 0;
				break;
			case KEY_UP:
				menuItem--;
				if(menuItem < 0)
					menuItem = MENU_LENGTH - 1;
				break;
			default:
				break;
		}
		if(type == 1){
			clase.main_menu(menuItem);
		}else if(type == 2){
			clase.files_menu(menuItem);
		}else if(type == 3){
			clase.field_menu(menuItem);
		}else if(type == 4){
			clase.record_menu(menuItem);
		}else if(type == 5){
			clase.index_menu(menuItem);
		}else if(type == 6){
			clase.utilities_menu(menuItem);
		}
	} while (key != '\n');
	return menuItem;
}
string getstring(){
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

string generarNombreLibro(){
	string name;
	string nombres[11] = {"Cien Años de Soledad", "Harry Potter", "El Principito", 
	"El alquimista", "El Perfume", "El Señor de los anillos", "Angeles", "Demonios", "Danilo", "Iliada", 
	"El conde"};
//	srand(time(0));
	stringstream ss;
	ss << nombres[rand()%11];
	name = ss.str();

	return name;
}

string generarIDLibro(){//ISBN
	cont_ISBN++;
	string id;
	//srand(time(0));
	stringstream ss;
	ss << cont_ISBN;
	id  = ss.str();
	cont_registros++;
	return id;
}

string generarAutorLibro(){
	string name;
	string nombres[11] = {"Cien Años de Soledad", "Harry Potter", "El Principito", 
	"El alquimista", "El Perfume", "El Señor de los anillos", "Angeles", "Demonios", "Danilo", "Iliada", 
	"El conde"};
//	srand(time(0));
	stringstream ss;
	ss << nombres[rand()%11];
	name = ss.str();

	return name;
}

string generarIDEditorialLibro(){
	string name;
	string nombres[11] = {"Carlos", "Melvin", "Christian", 
	"Denzel", "Oswaldo", "Angelica", "Yefferson", "Brian", "Danilo", "Daniel", 
	"Samuel"};
	//srand(time(0));
	stringstream ss;
	ss << nombres[rand()%10];
	name = ss.str();

	return name;
}