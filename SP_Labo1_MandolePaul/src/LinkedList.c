#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedList.h"


static Node* getNode(LinkedList* this, int nodeIndex);
static int addNode(LinkedList* this, int nodeIndex,void* pElement);

/** \brief Crea un nuevo LinkedList en memoria de manera dinamica
 *
 *  \param void
 *  \return LinkedList* Retorna (NULL) en el caso de no conseguir espacio en memoria
 *                      o el puntero al espacio reservado
 */
LinkedList* ll_newLinkedList(void)
{
    LinkedList* this = NULL; // declaro un puntero a linked list y lo pongo en null
    this = (LinkedList*) malloc (sizeof(LinkedList));// asigno memoria a ese puntero a linked list

    if(this != NULL)// pregunto si se pudo asignar memoria a this
    {
    	this->size = 0;// seteo en 0 el tamanio de el nuevo linked list
    	this->pFirstNode = NULL; //seteo en null donde apunta el primero nodo de la structura linked list
    }
    return this; //  retorno el puntero a la structura ll
}

/** \brief Retorna la cantidad de elementos de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna (-1) si el puntero es NULL o la cantidad de elementos de la lista
 *
 */
int ll_len(LinkedList* this)
{
    int len = -1;
    if(this != NULL)
    {
    	len = this->size;//a la variable len  le asigno el tamanio del ll que se encuentra guardado en la structura ll
    }
    return len; //retorno el len
}


/** \brief  Obtiene un nodo de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param index int Indice del nodo a obtener
 * \return Node* Retorna  (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        (pNode) Si funciono correctamente
 *
 */
static Node* getNode(LinkedList* this, int nodeIndex)
{

	int i;
	int len = ll_len(this); // le asigno a len el tamanio del ll
	Node* auxNode = NULL;
	if(this != NULL && nodeIndex > -1 && nodeIndex < len && len != -1) //  comparo que this != null y que el tamanio sea valido
	{
		auxNode = this->pFirstNode; //  a un auxiliar de un nodo le asigno el primer nodo al que apunta el ll
		for(i=0 ;i < nodeIndex; i++)
		{
			auxNode = auxNode->pNextNode;// al auxiliar del nodo le asigno el siguiente nodo
		}
	}
    return auxNode;// retorno el auxiliar nodo
}

/** \brief  Permite realizar el test de la funcion getNode la cual es privada
 *
 * \param this LinkedList* Puntero a la lista
 * \param index int Indice del nodo a obtener
 * \return Node* Retorna  (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        (pElement) Si funciono correctamente
 *
 */
Node* test_getNode(LinkedList* this, int nodeIndex)
{
    return getNode(this, nodeIndex);
}


/** \brief Agrega y enlaza un nuevo nodo a la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion donde se agregara el nuevo nodo
 * \param pElement void* Puntero al elemento a ser contenido por el nuevo nodo
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
static int addNode(LinkedList* this, int nodeIndex,void* pElement)
{
	int returnAux = -1;
	int len;
	Node* pPreviousNode=NULL;//declaro dos auxiliares a nodo
	Node* pNewNode=NULL;

	pNewNode = (Node*) malloc(sizeof(Node));// a new nodo le asigno espacio en memoria

	len = ll_len(this);//pido el tamanio del array
	if(this != NULL && nodeIndex > -1 && nodeIndex < len + 1)
	{
		if(pNewNode != NULL)// me fijo si se pudo asignar espacio en memoria
		{
			pNewNode->pElement = pElement; //  al nuevo nodo que cree le asigno el elemento
			pNewNode->pNextNode = NULL;// al siguiente nodo del nuevo nodo le asigno NULL ya que no se donde lo pondre

			if(nodeIndex == 0)// me fijo si en la pocicion que va el nuevo nodo es la 0
			{
				pNewNode->pNextNode = this->pFirstNode;//lepongo al nuevo nodo el nodo al que apuntaba el primer nodo
				this->pFirstNode = pNewNode;// al primer nodo del ll le asigno el puntero al nodo que agregue
			}
			else if(nodeIndex<len)// aca comparo si el nodo que voy a a agregar esta entre el 1 y el ultimo nodo
			{
				pPreviousNode = getNode(this, nodeIndex-1);//optengo el nodo anterior al que quiero guardar y lo guardo en previo node
				pNewNode->pNextNode = pPreviousNode->pNextNode;//al nuevo nodo le asigno el puntero al siguiente nodo al que apuntaba el anterior
				pPreviousNode->pNextNode = pNewNode;// al nodo anterior le hago apuntar al nuevo nodo  que agregue
			}
			else// en este miro si esta en la ultima pocision
			{
				pPreviousNode = getNode(this, nodeIndex-1);//al previo nodo le asigno el nodo anterior al index
				pPreviousNode->pNextNode = pNewNode;//al donde apunta el previo nodo le asigno el nuevo nodo
				pNewNode->pNextNode = NULL;//a nuevo nodo que agregue lo hago q apunte a null
			}
		}
		this->size++;// aumento el tamanio del ll
		returnAux = 0;
	}
	return returnAux;

}

/** \brief Permite realizar el test de la funcion addNode la cual es privada
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion donde se agregara el nuevo nodo
 * \param pElement void* Puntero al elemento a ser contenido por el nuevo nodo
  * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int test_addNode(LinkedList* this, int nodeIndex,void* pElement)
{
    return addNode(this,nodeIndex,pElement);
}


/** \brief  Agrega un elemento a la lista
 * \param pList LinkedList* Puntero a la lista
 * \param pElement void* Puntero al elemento a ser agregado
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si funciono correctamente
 *
 */
int ll_add(LinkedList* this, void* pElement)
{
    int returnAux = -1;
    int len;
    if(this != NULL)
    {
    	len = ll_len(this);// pido el tamanio del ll
    	returnAux = addNode(this, len, pElement);//llamo a agregar nodo le paso el elemento a agregar el ultimo indice donde se guarda el nuevo elemento
    }

    return returnAux;//retorno si salio bine o no
}

/** \brief Permite traer un en si te decia
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento a obtener
 * \return void* Retorna    (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                            (pElement) Si funciono correctamente
 *
 */
void* ll_get(LinkedList* this, int index)
{
	void* returnAux = NULL;
	int len;
	Node* pNode = NULL;
	if(this != NULL)
	{
		len = ll_len(this);//pido el tamanio del ll
		if(index > -1  && index < len + 1)// me fijo q el inidice este entre el tam
		{
			pNode = getNode(this, index);// al aux que cree le asigno el nodo que quiero
			if(pNode != NULL)//me fijo si trajo el nodo bien
			{
				returnAux=pNode->pElement;// retorno el elemento
			}
		}
	}
	return returnAux;// retorno el elemento
}


/** \brief Modifica un elemento de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento a modificar
 * \param pElement void* Puntero al nuevo elemento
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int ll_set(LinkedList* this, int index,void* pElement)
{
    int len;
	int returnAux = -1;
	Node* auxNode=NULL;
    if(this != NULL)
    {
    	len=ll_len(this);// pido el tam
    	if(index > -1 && index < len + 1)// me fijo si el tamanio esta bien
    	{
    		auxNode = getNode(this, index);//al axiliar que declare le asigno el nodo que quiero modificar
    		if(auxNode != NULL)
    		{
    			auxNode->pElement = pElement;// asigno el elemento modificado al nodo
    			returnAux = 0;
    		}
    	}
    }
    return returnAux;
}


/** \brief Elimina un elemento de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento a eliminar
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int ll_remove(LinkedList* this,int index)
{
	int len;
	int returnAux = -1;
	Node* pPreviusNode = NULL;
	Node* auxNode = NULL;
	if(this != NULL)
	{
		len=ll_len(this);// pido el tam
		if(index > -1 && index < len +1)
		{
			auxNode = getNode(this, index);// le asigno el nodo del inidice al auxiliar
			if(auxNode != NULL)
			{
				if(index == 0)// me fijo si el indice es 0
				{
					this->pFirstNode = auxNode->pNextNode;// al primero n odo le asingo el siguiente nodo del aux
					free(auxNode);//libero y borro lo que tenia el auxiliar
					auxNode = NULL;// pongo en null el aux
				}
				else
				{
					pPreviusNode = getNode(this, index - 1);//le asigno el nodo previo al aux previo
					pPreviusNode->pNextNode = auxNode->pNextNode;// al previo nodo le asigno donde apunta el aux
					free(auxNode);//borro el nodo
					auxNode = NULL;//libero el puntero
				}

				this->size = len - 1;// le bajo el tam al ll
				returnAux = 0;
			}
		}
	}
	return returnAux;
}


/** \brief Elimina todos los elementos de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si funciono correctamente
 *
 */
int ll_clear(LinkedList* this)
{
	int len;
    int returnAux = -1;
    if(this != NULL)
    {
    	len=ll_len(this);// pido el tam del ll

    	for(int i=0; i<len ; i++) //si no anda probar el for inverso
    	{
    		ll_remove(this, i);//borro cada elemento del ll en la posicion de i
    	}
    	returnAux = 0;
    }
    return returnAux;
}


/** \brief Elimina todos los elementos de la lista y la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si funciono correctamente
 *
 */
int ll_deleteLinkedList(LinkedList* this)
{
    int returnAux = -1;
    if(this != NULL)
    {
    	ll_clear(this);//borra todos los elementos de la lista
    	free(this);//borra la lista
    	this = NULL;//pongo el puntero a la lista en null
    	returnAux = 0;
    }
    return returnAux;
}

/** \brief Busca el indice de la primer ocurrencia del elemento pasado como parametro
 *
 * \param this LinkedList* Puntero a la lista
 * \param pElement void* Puntero al elemento
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        (indice del elemento) Si funciono correctamente
 *
 */
int ll_indexOf(LinkedList* this, void* pElement)
{
    int returnAux = -1;
    int len;
    int i;
    void* auxElement = NULL;
    if(this != NULL)
    {
    	len = ll_len(this);// pido el tam
    	for(i=0 ; i<len ; i++)
    	{
    		auxElement = ll_get(this, i);// al auxiliar del elemento le asigno el elemento de i
    		if(pElement == auxElement)//comparo si el elemento que me pasaron es igual al que traje antes
    		{
    			returnAux = i;// si es igual retorno el indice
    			break;
    		}
    	}
    }

    return returnAux;
}

/** \brief Indica si la lista esta o no vacia
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si la lista NO esta vacia
                        ( 1) Si la lista esta vacia
 *
 */
int ll_isEmpty(LinkedList* this)
{
	int len;
    int returnAux = -1;
    if(this != NULL)
    {
    	len=ll_len(this);// pido el tam
    	if(len > 0)// me fijo si el tam de la lista es mayor a 0
    	{
    		returnAux = 0;// retorno 0 si la lista esta con elementos
    	}
    	else
    	{
    		returnAux = 1;// retorno -11 si la lista no tiene elementos
    	}
    }
    return returnAux;
}

/** \brief Inserta un nuevo elemento en la lista en la posicion indicada
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion donde se agregara el nuevo elemento
 * \param pElement void* Puntero al nuevo elemento
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int ll_push(LinkedList* this, int index, void* pElement)
{
    int returnAux = -1;
    int len = ll_len(this);// pido el tam de el ll
    if(this != NULL)
    {
    	if(index > -1 && index < len + 1)// compruevo que el indice sea valido
    	{
        	if(!addNode(this, index, pElement))//agrego el elemento
        	{
        		returnAux = 0;
        	}
    	}
    }
    return returnAux;
}


/** \brief Elimina el elemento de la posicion indicada y retorna su puntero
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento eliminar
 * \return void* Retorna    (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                            (pElement) Si funciono correctamente
 *
 */
void* ll_pop(LinkedList* this,int index)
{
    void* returnAux = NULL;
    int len = ll_len(this);// pido el tam del ll
    if(this != NULL)
    {
        if(index > - 1 && index < len)// compruevo que el indice sea valido
        {
            returnAux = ll_get(this, index);// al aux le asigno el elemento que se encuentra en ese indice
            if(ll_remove(this, index))//remuevo el elemento
            {
                returnAux = NULL;// pongo el null el elemento
            }
        }
    }
    return returnAux;
}


/** \brief  Determina si la lista contiene o no el elemento pasado como parametro
 *
 * \param this LinkedList* Puntero a la lista
 * \param pElement void* Puntero del elemento a verificar
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 1) Si contiene el elemento
                        ( 0) si No contiene el elemento
*/
int ll_contains(LinkedList* this, void* pElement)
{
    int returnAux = -1;
    int i;
    int len = ll_len(this);// pido el tam
    Node* pNodeAux;
    if(this != NULL)
    {
        pNodeAux = NULL;
        returnAux = 0;
        for(i=0 ; i<len ; i++)
        {
            pNodeAux = ll_get(this, i);// pido el elemento en la posicion de i
            if(pNodeAux == pElement)// comparo si es igual al elemento que recivo
            {
                returnAux = 1;/// retorno 1 si lo contiene
                break;
            }
        }
    }
    return returnAux;
}

/** \brief  Determina si todos los elementos de la lista (this2)
            estan contenidos en la lista (this)
 *
 * \param this LinkedList* Puntero a la lista
 * \param this2 LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si alguno de los punteros a las listas son NULL
                        ( 1) Si los elementos de (this2) estan contenidos en la lista (this)
                        ( 0) si los elementos de (this2) NO estan contenidos en la lista (this)
*/
int ll_containsAll(LinkedList* this,LinkedList* this2)
{
    int returnAux = -1;
	int i;
	int len = ll_len(this2);// pido el tamanio de la lista2
	Node* pAuxNode;
	if(this != NULL && this2 != NULL)
	{
		returnAux = 1;
		pAuxNode = NULL;
		for(i=0 ; i<len ; i++)
		{
			pAuxNode = ll_get(this2, i);// guardo el elemento de la lista 2 en  la posicion de i
			if(!ll_contains(this, pAuxNode))//llamo a la funcion quye compara si esta el emento en la lista y si me devuelve 0 significa que no estaba
			{
				returnAux = 0;
				break;
			}
		}
	}
    return returnAux;
}

/** \brief Crea y retorna una nueva lista con los elementos indicados
 *
 * \param pList LinkedList* Puntero a la lista
 * \param from int Indice desde el cual se copian los elementos en la nueva lista
 * \param to int Indice hasta el cual se copian los elementos en la nueva lista (no incluido)
 * \return LinkedList* Retorna  (NULL) Error: si el puntero a la listas es NULL
                                o (si el indice from es menor a 0 o mayor al len de la lista)
                                o (si el indice to es menor o igual a from o mayor al len de la lista)
                         (puntero a la nueva lista) Si ok
*/
LinkedList* ll_subList(LinkedList* this,int from,int to)
{
    LinkedList* cloneArray = NULL;
    void* pNodeAux;
    int len = ll_len(this);
    int i;
    if(this != NULL && from > -1 && from < len+1 && to >= from && to < len +1)// comparo que la lista sea distinta de null que el form sea mayor que -1 y sea menos al tam el to tiene que ser mayor  igual al from to deve ser menor  al len
    {
        pNodeAux = NULL;
        cloneArray = ll_newLinkedList();// creo una nueva lista
        if(cloneArray != NULL)// me fijo si se creo bien
        {
            for(i=from ; i<to ; i++)
            {
                pNodeAux = ll_get(this, i);//pido el nodo
                addNode(cloneArray,i, pNodeAux);// agrego el nodo a la lista nueva para clonarla
            }
        }
    }

    return cloneArray;
}



/** \brief Crea y retorna una nueva lista con los elementos de la lista pasada como parametro
 *
 * \param pList LinkedList* Puntero a la lista
 * \return LinkedList* Retorna  (NULL) Error: si el puntero a la listas es NULL
                                (puntero a la nueva lista) Si ok
*/
LinkedList* ll_clone(LinkedList* this)
{
	LinkedList* cloneArray = NULL;
	int len = ll_len(this);// pido el tam
	if(this != NULL)
	{
		cloneArray = ll_subList(this, 0, len);// creo una copia completa de la lista y la retorno  por eso es 0  a len
	}
	return cloneArray;
}


/** \brief Ordena los elementos de la lista utilizando la funcion criterio recibida como parametro
 * \param pList LinkedList* Puntero a la lista
 * \param pFunc (*pFunc) Puntero a la funcion criterio
 * \param order int  [1] Indica orden ascendente - [0] Indica orden descendente
 * \return int Retorna  (-1) Error: si el puntero a la listas es NULL
                                ( 0) Si ok
 */
int ll_sort(LinkedList* this, int (*pFunc)(void* ,void*), int order)
{
    int returnAux =-1;
    void* pElement1 = NULL;// aux del primer elemento
    void* pElement2 = NULL;// aux del segundo elemento
    int flagSwap=0;// un sawp
    void* pElmentAux = NULL;//aux para hacer los swaps
    int len=-1;
    int i;
    int j;
    if(this != NULL && pFunc != NULL && (order == 0 || order == 1))// compruevo que los datos que me envian sean correctos
    {

    	len=ll_len(this);// pido el tam del ll
    	for(i=0; i<len-1;i++)
    	{
    		pElement1 = ll_get(this, i);//pido el primer elemento
    		for(j=i;j<len;j++)
    		{
    			pElement2 = ll_get(this, j);//pido el segundo elemento
    			flagSwap=pFunc(pElement1,pElement2);//lo que devuelve la funcion de ordenar lo guardo en el flagsawp
    			if(order==1)//me fijo que orden es
    			{
    				if(flagSwap==-1)// me fijo la comparacion del swap con el orden y ahgo el cambio
    				{
    					pElmentAux=pElement1;
    					pElement1=pElement2;
    					pElement2=pElmentAux;
    				}

    			}
    			else
    			{
    				if(flagSwap==-1)
    				{
    					pElmentAux=pElement2;
    					pElement2=pElement1;
    					pElement1=pElmentAux;
    				}
    			}
        		ll_set(this, i, pElement1);//modifico los elementos
        		ll_set(this, j, pElement2);//modifico el orden de los elementos
    		}

    	}
    	returnAux = 0;
    }

    return returnAux;

}
LinkedList* ll_filter(LinkedList* this,int (*pFunc)(void*))
{
	int len;
	LinkedList* ListaNueva = NULL;
	void* pElement = NULL;
	int cont=0;
	if(this != NULL && pFunc != NULL)
	{
		len = ll_len(this);
		ListaNueva = ll_newLinkedList();
		if(ListaNueva != NULL)
		{
			for(int i=0;i<len;i++)
			{
				pElement = ll_get(this, i);
				if(!pFunc(pElement))
				{
					addNode(ListaNueva, cont, pElement);
					cont++;
				}
			}
		}
	}
	return ListaNueva;
}

int ll_map(LinkedList* this, int (*pFunc)(void*))
{
	int ret = 1;
	int len;
	void* pElement = NULL;
	if(this != NULL && pFunc != NULL)
	{
		len = ll_len(this);
		for(int i=0;i<len;i++)
		{
			pElement = ll_get(this, i);
			pFunc(pElement);
		}
	}
	return ret;
}
