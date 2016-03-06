# include "Menu.h"

Menu::Menu(){

}
void Menu::main_menu(int item){	
	char mainMenu[] = "Registro de datos";
	char menu[MENUMAX][20] = {
		"Archivos",
		"Campos",
		"Registros",
		"Indices",
		"Utilidades",
		"Salir"
	};	
	mvaddstr(0, 30, mainMenu);
	for (int i = 0; i < MENUMAX; i++){
		if(i == item)
			attron(A_REVERSE);
		mvaddstr(3+(i*2), 32, menu[i]);
		attroff(A_REVERSE);
	}
	mvaddstr(17, 30, "Hit Enter");
	refresh();
}
void Menu::files_menu(int item){	
	char mainMenu[] = "Panel de Archivos";
	char menu[MFILEMAX][20] = {
		"Nuevo Archivo",
		"Guardar Archivo",
		"Cerrar Archivo",
		"Cargar registros"
	};	
	mvaddstr(0, 30, mainMenu);
	for (int i = 0; i < MFILEMAX; i++){
		if(i == item)
			attron(A_REVERSE);
		mvaddstr(3+(i*2), 32, menu[i]);
		attroff(A_REVERSE);
	}
	mvaddstr(12, 30, "Hit Enter");
	refresh();
}
void Menu::field_menu(int item){
	char mainMenu[] = "Panel de Campos";
	char menu[MFIELDMAX][20] = {
		"Crear Campos",
		"Listar Campos",
		"Modificar Campos",
		"Borrar Campos", 
		"Atras .."
	};
	mvaddstr(0, 30, mainMenu);
	for (int i = 0; i < MFIELDMAX; i++){
		if(i == item)
			attron(A_REVERSE);
		mvaddstr(3+(i*2), 32, menu[i]);
		attroff(A_REVERSE);
	}
	mvaddstr(13, 30, "Hit Enter");
	refresh();
}
void Menu::record_menu(int item){
	char mainMenu[] = "Panel de Registros";
	char menu[MRECORDMAX][32] = {
		"Introducir Registros",
		"Modificar Registros",
		"Borrar Registros",
		"Buscar Registros",
		"Listar Registros",
		"Atras .."
	};	
	mvaddstr(0, 30, mainMenu);
	for (int i = 0; i < MRECORDMAX; i++){
		if(i == item)
			attron(A_REVERSE);
		mvaddstr(3+(i*2), 32, menu[i]);
		attroff(A_REVERSE);
	}
	mvaddstr(15, 30, "Hit Enter");
	refresh();
}
void Menu::index_menu(int item){
	char mainMenu[] = "Panel de Indices";
	char menu[MINDEXMAX][20] = {
		"Crear Indices",
		"Re Indexar Archivos",		
		"Atras .."
	};	
	mvaddstr(0, 30, mainMenu);
	for (int i = 0; i < MINDEXMAX; i++){
		if(i == item)
			attron(A_REVERSE);
		mvaddstr(3+(i*2), 32, menu[i]);
		attroff(A_REVERSE);
	}
	mvaddstr(10, 30, "Hit Enter");
	refresh();
}
void Menu::utilities_menu(int item){
	/*char mainMenu[] = "Panel de Utilidades";
	char menu[MUTILITIESMAX][20] = {
		"Exportar a Excel",
		"Exportar a XML",
		"Exportar a JSON",
		"Atras .."
	};	
	mvaddstr(0, 30, mainMenu);
	for (int i = 0; i < MUTILITIESMAX; i++){
		if(i == item)
			attron(A_REVERSE);
		mvaddstr(3+(i*2), 32, menu[i]);
		attroff(A_REVERSE);
	}
	mvaddstr(13, 30, "Hit Enter");
	refresh();*/
}