#include "libro.h"
#include "editorial.h"

using namespace std;

int main(int argc, char const *argv[])
{

	return 0;
}
int menu(){
	cout << "Ingrese su opcion\n
		1. Cargar Archivo\n
		2. Crear Archivo\n" << endl;

	return 0;
}
//                       hacer clase recordfile
/*void EscribirRegistro(registro){
	if (availlist esta vacio)
	{
		seek(EOF);
		ref = current pos;
		key = getKey(registro);
		write(file,registro,size of record);
		actualizar header dirty = true;
		index.add(key,ref)~~~~~>Agrega(key,ref)ordenado
	}else
	{
		if (siguiente posicion en availlist es adecuada)
		{
			pos = availlist.next(sizeofrec); actualiza AvailList
			hey = getKey(regitro);
			seek(pos);
			write(file,registro,size of record);
			actualizar header dirty = true;
			index.add(key,ref);
		}else
		{
			
		}
	}
}*/