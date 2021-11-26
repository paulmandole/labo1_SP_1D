/*
 * perritos.c
 *
 *  Created on: 26 nov. 2021
 *      Author: Paul
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "perritos.h"
#include "functions.h"

ePerrito* perrito_new()
{
	ePerrito* perritoRet=NULL;

	perritoRet = (ePerrito*)malloc(sizeof(ePerrito));

	return perritoRet;
}

ePerrito* perrito_constParam(int id,int edad,char* nombre,float peso,char* raza)
{
	ePerrito* perritoRet = NULL;
	perritoRet = perrito_new();

	if(perritoRet != NULL)
	{
		perrito_setId(perritoRet, id);
		perrito_setEdad(perritoRet, edad);
		perrito_setName(perritoRet, nombre);
		perrito_setRaza(perritoRet, raza);
		perrito_setPeso(perritoRet, peso);
	}
	return perritoRet;
}
int perrito_setPeso(ePerrito* this,float peso)
{
	int takeCare = 1;
	if(this != NULL)
	{
		this->peso = peso;
		takeCare = 0;
	}
	return takeCare;
}
int perrito_setId(ePerrito* this,int id)
{
	int takeCare=1;

	if(this != NULL)
	{
		this->id = id;
		takeCare = 0;
	}
	return takeCare;
}

int perrito_setEdad(ePerrito* this,int edad)
{
	int takeCare = 1;
	if(this != NULL)
	{
		this->edad = edad;
		takeCare = 0;
	}
	return takeCare;
}

int perrito_setName(ePerrito* this,char* name)
{
	int takeCare = 1;
	if(this != NULL && name != NULL)
	{
		strcpy(this->nombre,name);
		takeCare = 0;
	}
	return takeCare;
}

int perrito_setRaza(ePerrito* this,char* raza)
{
	int takeCare = 1;
	if(this != NULL && raza != NULL)
	{
		strcpy(this->raza,raza);
		takeCare = 0;
	}
	return takeCare;
}

int perrito_getId(ePerrito* this)
{
	int id;
	if(this != NULL)
	{
		id = this->id;
	}
	return id;
}

int perrito_getEdad(ePerrito* this)
{
	int edad;
	if(this != NULL)
	{
		edad = this->edad;
	}
	return edad;
}

char* perrito_getNombre(ePerrito* this)
{
	char* nombre = NULL;
	if(this != NULL)
	{
		nombre = this->nombre;
	}
	return nombre;
}

char* perrito_getRaza(ePerrito* this)
{
	char* raza = NULL;
	if(this != NULL)
	{
		raza = this->raza;
	}
	return raza;
}
float perrito_getPeso(ePerrito* this)
{
	float peso;
	if(this != NULL)
	{
		peso = this->peso;
	}
	return peso;
}
int perritos_cargarDesdeArchivosTxt(char* path,LinkedList* pArrayPerritos)
{
	int ret = 1;
	FILE* pFile = fopen(path,"r");
	if (pArrayPerritos != NULL && path != NULL)
	{

		perritos_parcePerritosFormTxt(pFile,pArrayPerritos);
		fclose(pFile);
		pFile = NULL;
		ret = 0;
	}
	return ret;
}

int perritos_parcePerritosFormTxt(FILE* pFile,LinkedList* pArrayPerritos)
{
	int ret;
	char id[10];
	char nombre[21];
	char raza[21];
	char peso[21];

	char edad[10];
	if(pFile != NULL && pArrayPerritos != NULL)
	{

		fscanf(pFile,"%[^,],%[^,],%[^,],%[^,],%[^\n]",id,nombre,peso,edad,raza);

		while(!feof(pFile))
		{
			fscanf(pFile,"%[^,],%[^,],%[^,],%[^,],%[^\n]",id,nombre,peso,edad,raza);
			ePerrito* perrito = perrito_constParam(atoi(id), atoi(edad), nombre, atof(peso), raza);
			ll_add(pArrayPerritos, perrito);
		}

		fclose(pFile);
		ret=0;
	}

	return ret;
}

int perritos_mostrarPerritos(LinkedList* pArrayPerritos)
{
	int ret = 1;
	int len = ll_len(pArrayPerritos);
	ePerrito* perrito = NULL;
	if(pArrayPerritos != NULL)
	{
		printf("\n%-5s %-20s %-20s %-10s %-10s\n\n","ID","NOMBRE","RAZA","EDAD","PESO");
		for(int i = 0; i<len; i++)
		{
			perrito = ll_get(pArrayPerritos, i);
			perrito_mostrarPerrito(perrito);
		}
	}
	return ret;
}

void perrito_mostrarPerrito(ePerrito* perrito)
{
	if(perrito != NULL)
	{
		printf("%-5d %-20s %-20s %-10d %-10.2f\n",perrito_getId(perrito),perrito_getNombre(perrito),perrito_getRaza(perrito),perrito_getEdad(perrito),perrito_getPeso(perrito));
	}
}

int perrito_ordenarPorNombre(void* perritoI,void* perritoJ)
{
	int ret = 1;
	ePerrito* auxPerritoI = NULL;
	ePerrito* auxPerritoJ = NULL;
	if(perritoI != NULL && perritoJ != NULL)
	{
		auxPerritoI = perritoI;
		auxPerritoJ = perritoJ;
		if(strcmp(auxPerritoI->nombre,auxPerritoJ->nombre) == 1)
		{
			ret = -1;
		}
		else if(strcmp(auxPerritoI->nombre,auxPerritoJ->nombre) == 0)
		{
			ret = 0;
		}
		auxPerritoI = NULL;
		auxPerritoJ = NULL;
	}
	return ret;
}

int ePerrito_laQueMapea(void* perrito)
{
	int ret = 1;
	float resultado;
	float peso;

	ePerrito* perritoAux = NULL;
	if(perrito != NULL)
	{
		perritoAux = (ePerrito*) perrito;
		peso = perrito_getPeso(perritoAux);
		resultado =  peso * 23;
		perrito_setRacion(perritoAux, resultado);
		ret = 0;
		perritoAux = NULL;
	}
	return ret;
}

int perritos_mostrarPerritosConRacion(LinkedList* pArrayPerritos)
{
	int ret = 1;
	int len = ll_len(pArrayPerritos);
	ePerrito* perrito = NULL;
	if(pArrayPerritos != NULL)
	{
		printf("\n%-5s %-20s %-20s %-10s %-10s %-10s\n\n","ID","NOMBRE","RAZA","EDAD","PESO","RACION");
		for(int i = 0; i<len; i++)
		{
			perrito = ll_get(pArrayPerritos, i);
			perrito_mostrarPerritoConRacion(perrito);
		}
	}
	return ret;
}

void perrito_mostrarPerritoConRacion(ePerrito* perrito)
{
	if(perrito != NULL)
	{
		printf("%-5d %-20s %-20s %-10d %-10.2f %-10.2f\n",perrito_getId(perrito),perrito_getNombre(perrito),perrito_getRaza(perrito),perrito_getEdad(perrito),perrito_getPeso(perrito),perrito_getRacion(perrito));
	}
}
float perrito_getRacion(ePerrito* this)
{
	float racion;
	if(this != NULL)
	{
		racion = this->cantidadComidaRacion;
	}
	return racion;
}
int ePerrito_laQueFiltra(void* perrito)
{
	int ret = -1;
	ePerrito* perritoComparar;
	if(perrito != NULL)
	{
		perritoComparar = (ePerrito*)perrito;
		if(strcmp(perritoComparar->raza,"Galgo") == 0 && perritoComparar->edad > 9 && perritoComparar->cantidadComidaRacion < 201)
		{
			ret = 0;
		}
		else
		{
			ret = 1;
		}
	}
	return ret;
}

int perrito_guardarPerritosArchivoTxt(char* path, LinkedList* pArrayPerritos)
{
	int ret=1;
	int len;
	FILE* pFile = fopen(path,"w");
	ePerrito* pPerrito = NULL;
	if(path != NULL && pArrayPerritos != NULL)
	{
		len = ll_len(pArrayPerritos);

		if(pFile != NULL)
		{
			fprintf(pFile, "%s", "id,nombre,peso,edad,raza,cantidadComidaRacion\n");
			for(int i=0; i<len;i++)
			{
				pPerrito = (ePerrito*)ll_get(pArrayPerritos, i);
				fprintf(pFile,"%d,%s,%.2f,%d,%s,%.2f\n",perrito_getId(pPerrito),perrito_getNombre(pPerrito),perrito_getPeso(pPerrito),perrito_getEdad(pPerrito),perrito_getRaza(pPerrito),perrito_getRacion(pPerrito));
			}
			fclose(pFile);
			pFile = NULL;
		}
		ret = 0;
	}
	return ret;
}
int perrito_setRacion(ePerrito* this,float racion)
{
	int takeCare = 1;
	if(this != NULL)
	{
		this->cantidadComidaRacion = racion;
		takeCare = 0;
	}
	return takeCare;
}

