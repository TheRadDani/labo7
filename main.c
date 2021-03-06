#include<stdio.h>
#include<stdlib.h>
//src
#define NOMBRE "listaEnlazada.bin"
//#include "lista.h"



typedef struct node {
	int data; //**< data */
	struct node* next; //**< pointer to next element */
} node;



node* createList(int first_value)
{
    node *nuevo = NULL;

    nuevo = (node*)malloc(sizeof(node));
    if( nuevo != NULL)
    {
        nuevo->data = first_value;
        nuevo->next = NULL;
    }

    return nuevo;
}
int insertElement(node** phead, int pos, int new_value)
{
    node *reco = *phead;
    int cant = 0;
    while (reco != NULL)
    {
        cant++;
        reco = reco->next;
    }
    if (pos <= cant + 1)
    {
        node *nuevo=NULL;
        nuevo=createList(new_value);
        if (pos == 1)
        {
            nuevo->next = *phead;
            *phead = nuevo;
        }
        else
            if (pos == cant+ 1)
            {
                node *reco = *phead;
                while (reco->next != NULL)
                {
                    reco = reco->next;
                }
                reco->next = nuevo;
                nuevo->next = NULL;
            }
            else
            {
                node *reco = *phead;
                int f;
                for (f = 1; f <= pos - 2; f++)
                {
                    reco = reco->next;
                }
                node *siguiente = reco->next;
                reco->next = nuevo;
                nuevo->next = siguiente;
            }
    }

}
void printList(node* head)
{
    node *n = head;

    while( n != NULL)
    {
        printf("%d ", n->data);
        n = n->next;
    }
}
void freeList(node* head)
{
    node *reco = head;
    node *bor;
    while (reco != NULL)
    {
        bor = reco;
        reco = reco->next;
        free(bor);
    }
}




void sort(node* head, char dir)
{
    node *f=head;
	//struct nodo *f1=raiz;
	//f1=f1->sig;
	int *x;
	node *reco = head;
    int cant = 0;
    while (reco != NULL)
    {
        cant++;
        reco = reco->next;
    }
	x=(int *)malloc(cant*sizeof(int));
	for(int i=0;i<cant;i++)
	{
		x[i]=f->data;
		f=f->next;
	}
	if(dir =='a')
	{
	int aux;
	//Ordenamiento por metodo burbuja con punteros
	for(int i=0;i<cant;i++)
	{
		for(int j=0;j<cant-1;j++)
		{
			if(*(x+j+1) > *(x+j))
			{
				aux = *(x+j);
				*(x+j) = *(x+j+1);
				*(x+j+1) = aux;

			}
		}
	}
	}
	else if(dir=='b')
	{
	int aux;
	//Ordenamiento por metodo burbuja con punteros
	for(int i=0;i<cant;i++)
	{
		for(int j=0;j<cant-1;j++)
		{
			if(*(x+j+1) < *(x+j))
			{
				aux = *(x+j);
				*(x+j) = *(x+j+1);
				*(x+j+1) = aux;

			}
		}
	}
	}
	for(int i=0;i<cant;i++)
	{
		printf("%i ",x[i]);

	}
	free(x);
	x=NULL;
}


void writeList(node* head, const char* filePath)
{
    FILE *f;
    f=fopen(filePath,"wb");
    node *x=head;
    if(f==NULL)
    {
        exit(1);
    }
    node *reco = head;
    int cant = 0;
    while (reco != NULL)
    {
        cant++;
        reco = reco->next;
    }
    for(int i=0;i<cant;i++)
    {
    	int a=x->data;
        fwrite(&a,sizeof(int),1,f);
        x=x->next;
    }
    fflush(f);
    fclose(f);
}

int pop_front(node **phead)
{
    int informacion = (*phead)->data;
    node *bor = *phead;
    node *aux=(*phead)->next;
    free(*phead);
    *phead = aux;

    return informacion;


}

int pop_back(node* head)
{
    node *f=head;
    while(f->next != NULL)
    {
        f=f->next;
    }
    int informacion=f->data;
    node *c=f->data;
    free(c);
    c->next=NULL;
    return informacion;
}

int removeElement(node** phead, int pos)
{
    node *reco = *phead;
    int cant = 0;
    while (reco != NULL)
    {
        cant++;
        reco = reco->next;
    }
    if (pos <= cant)
    {
        int informacion;
        node *bor;
        if (pos == 1)
        {
            pop_front(phead);
        }
        else
        {
            node *reco;
            reco = *phead;
            int f;
            for (f = 1; f <= pos - 2; f++)
            {
                reco = reco->next;
            }
            node *prox = reco->next;
            reco->next = prox->next;
            informacion = prox->data;
            bor = prox;
            free(bor);
            return informacion;

        }

    }
    else
        return -1;
}

int getElement(node* head, int index, int* valid)
{
    node *nAux = head;
    int y;
    for(int i =0;i<index;i++)
    {
        y=nAux->data;
        nAux=nAux->next;
    }
    while( nAux != NULL )
    {
        if(nAux->data == y)
            *valid = 0;
        nAux = nAux->next;
    }
    *valid= 1;

    return y;
}



int main(int argc, char **argv,char const envp)
{
    int elemento=1;
    int valid;
	node *cabeza = NULL;
	insertElement(&cabeza, 1, 10);
	insertElement(&cabeza, 2, 7);
	insertElement(&cabeza,3,9);
	printList(cabeza);
    printf("\nEl elemento en la posicion %i es %i\n",elemento,getElement(cabeza, elemento, &valid));
	if(valid==0)
    {
        printf("Elemento no valido\n");
    }
    else if(valid==1)
    {
        printf("Elemento valido\n");
    }
    writeList(cabeza, NOMBRE);
    printf("\nLista luego de eliminar elemento\n");
	int a=removeElement(&cabeza, 3);
	printList(cabeza);
	printf("\nEl elemento eliminado fue: %i\n",a);
	printf("La lista ordenada de manera descendente es: \n");
	//fflush(stdout);
	sort(cabeza, 'a');
	printf("\nLa lista ordenada de manera ascendente es: \n");
	sort(cabeza, 'b');
	freeList(cabeza);
	return 0;
}

