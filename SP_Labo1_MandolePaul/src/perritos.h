/*
 * perritos.h
 *
 *  Created on: 26 nov. 2021
 *      Author: Paul
 */

#ifndef PERRITOS_H_
#define PERRITOS_H_
#include "LinkedList.h"

typedef struct
{
	int id;
	char nombre[21];
	float peso;
	int edad;
	char raza[21];
	float cantidadComidaRacion;

}ePerrito;

ePerrito* perrito_new();
ePerrito* perrito_constParam(int id,int edad,char* nombre,float peso,char* raza);
int perrito_setId(ePerrito* this,int id);
int perrito_setEdad(ePerrito* this,int edad);
int perrito_setName(ePerrito* this,char* name);
int perrito_setRaza(ePerrito* this,char* raza);
int perrito_setPeso(ePerrito* this,float peso);
int perrito_setRacion(ePerrito* this,float racion);
int perrito_getId(ePerrito* this);
int perrito_getEdad(ePerrito* this);
char* perrito_getNombre(ePerrito* this);
char* perrito_getRaza(ePerrito* this);
float perrito_getPeso(ePerrito* this);
float perrito_getRacion(ePerrito* this);
int perritos_cargarDesdeArchivosTxt(char* path,LinkedList* pArrayPerritos);
int perritos_parcePerritosFormTxt(FILE* pFile,LinkedList* pArrayPerritos);
int perritos_mostrarPerritos(LinkedList* pArrayPerritos);
void perrito_mostrarPerrito(ePerrito* perrito);
int perrito_ordenarPorNombre(void* perritoI,void* perritoJ);
int ePerrito_laQueMapea(void* perrito);
int perritos_mostrarPerritosConRacion(LinkedList* pArrayPerritos);
void perrito_mostrarPerritoConRacion(ePerrito* perrito);
int ePerrito_laQueFiltra(void* perrito);
int perrito_guardarPerritosArchivoTxt(char* path, LinkedList* pArrayPerritos);

#endif /* PERRITOS_H_ */
