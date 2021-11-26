/*
 ============================================================================
 Name        : SP_Labo1_MandolePaul.c
 Author      : Paul Mandole
 Version     :
 Copyright   : 
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include "perritos.h"
#include "functions.h"
#include "LinkedList.h"
int main(void) {
	setbuf(stdout,NULL);
	int option;

	int flagLoadTxt = 0;
	int flagConComida = 0;
	int flagFiltrado = 0;


	LinkedList* listaPerritos = ll_newLinkedList();
	LinkedList* ListaPerritosFiltrado = NULL;
	do
	{
		requestNumber(&option,  		"**************************************\n"
										"MENU\n"
										"**************************************\n"
										"1. Cargar los datos de los perritos desde el archivo data.csv (modo texto)\n"
										"2. Listar perritos ordenados de manera ascendente por nombre\n"
										"3. calcular cantidad de comida racionada\n"
										"4. Listar los perritos con sus raciones de comida.\n"
										"5. listado con los perritos que sean de raza “Galgo”, tengan más de 10 años de edad y coman menos de 200 gramos de comida diaria.\n"
										"6. Guardar en un archivo llamado “galgosFlaquitos.csv” los resultados de la búsqueda anterior(formato texto).\n"
										"7. Salir\n"
										"**************************************\n"
										"Ingrese una opcion: ",

										"**************************************\n"
										"MENU\n"
										"**************************************\n"
										"1. Cargar los datos de los perritos desde el archivo data.csv (modo texto)\n"
										"2. Listar perritos ordenados de manera ascendente por nombre\n"
										"3. calcular cantidad de comida racionada\n"
										"4. Listar los perritos con sus raciones de comida.\n"
										"5. listado con los perritos que sean de raza “Galgo”, tengan más de 10 años de edad y coman menos de 200 gramos de comida diaria.\n"
										"6. Guardar en un archivo llamado “galgosFlaquitos.csv” los resultados de la búsqueda anterior(formato texto).\n"
										"7. Salir\n"
										"**************************************\n"
										"Opcion invalida, reingrese: ", 1, 7);
		switch(option)
		{
			case 1:
				if(!flagLoadTxt)
				{
					if(!perritos_cargarDesdeArchivosTxt("src\\perritos.csv", listaPerritos))
					{
						printf("\nEl archivo se cargo con exito.\n");
						flagLoadTxt=1;
					}
					else
					{
						printf("\nERROR al cargar el archivo\n");
						flagLoadTxt=0;
					}
				}
				else
				{
					printf("\nERROR.Ya se cargo el archivo.\n");
				}
				systemPause("\nToque cualquier tecla para continuar...");
				break;
			case 2:
				if(flagLoadTxt)
				{
					printf("ordenando ...\n\n");
					ll_sort(listaPerritos, perrito_ordenarPorNombre, 1);
					perritos_mostrarPerritos(listaPerritos);
				}
				else
				{
					printf("\nERROR.Debe cargar una lista desde el archivo antes de mostrar.\n");
				}
				systemPause("\nToque cualquier tecla para continuar...");
				break;
			case 3:
				if(flagLoadTxt)
				{
					ll_map(listaPerritos, ePerrito_laQueMapea);
					flagConComida = 1;
					printf("\nSe calculo la comida de los perros.\n");
				}
				else
				{
					printf("\nERROR.Debe cargar una lista desde el archivo antes de mostrar.\n");
				}
				systemPause("\nToque cualquier tecla para continuar...");
				break;
			case 4:
				if(flagLoadTxt)
				{
					if(flagConComida == 1)
					{
						perritos_mostrarPerritosConRacion(listaPerritos);
					}
					else
					{
						printf("\nDebe pasar por la opcion 3 antes de poder mostrar.\n");
					}
				}
				else
				{
					printf("\nERROR.Debe cargar una lista desde el archivo antes de mostrar.\n");
				}
				systemPause("\nToque cualquier tecla para continuar...");
				break;
			case 5:
				if(flagLoadTxt)
				{
					if(flagConComida == 1)
					{
						ListaPerritosFiltrado = ll_filter(listaPerritos, ePerrito_laQueFiltra);
						if(ListaPerritosFiltrado != NULL)
						{
							perritos_mostrarPerritosConRacion(ListaPerritosFiltrado);
							flagFiltrado = 1;
						}
						else
						{
							printf("No hay perritos con las descripciones solicitadas\n");
						}
					}
					else
					{
						printf("\nDebe pasar por la opcion 3 antes de poder filtrar.\n");
					}
				}
				else
				{
					printf("\nERROR.Debe cargar una lista desde el archivo antes de mostrar.\n");
				}
				systemPause("\nToque cualquier tecla para continuar...");
				break;
			case 6:
				if(flagLoadTxt)
				{
					if(flagConComida == 1 && flagFiltrado == 1)
					{
						perrito_guardarPerritosArchivoTxt("galgosFlaquitos.csv", ListaPerritosFiltrado);
						printf("\nSe guardo el archivo correctamente\n");
					}
					else
					{
						printf("\ndebe pasar por la opcion 3 y 5 antes de guardar\n");
					}
				}
				else
				{
					printf("\nERROR.Debe cargar una lista desde el archivo antes de mostrar.\n");
				}
				systemPause("\nToque cualquier tecla para continuar...");
				break;
			case 7:
				ll_deleteLinkedList(ListaPerritosFiltrado);
				ll_deleteLinkedList(listaPerritos);
				printf("Gracias por utilizar el programeitor 9000 \nEspero no pechearla hoy.\n");
				break;
		}

	}while(option!=7);

	return EXIT_SUCCESS;
}
