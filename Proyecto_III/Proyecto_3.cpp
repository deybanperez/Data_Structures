#include <iostream>
#include <stdlib.h>
#include <iostream>
#include <stdlib.h>
#include "Cola.h"
#include "Pila.h"
#include "Lista.h"
#include <string>

using namespace std;

Lista<int>* Binary(long int number)	//Funcion que transforma un entero decimal a binario y guarada cada bit en una lista
{
	Lista<int> *A = new Lista<int>();

	if(number==0)
	{
		A->InsertarPrimero(0);
	}else
	{	while(number > 0)
		{
			A->InsertarPrimero(number%2);
		
			number=number/2;	
		}
	}
	
	return A;

}

template <typename type>

class treeNode	//Implementacion del nodo a usar
{
	public:
		type data;
	
		treeNode<type> *leftPtr;
	
		treeNode<type> *rigthPtr;
		
		treeNode()
		{
			leftPtr=NULL;
			rigthPtr=NULL;
		}
		
		treeNode(type value)
		{
			data=value;
			leftPtr=NULL;
			rigthPtr=NULL;
		}
};

template <typename type>
class tree
{
	public:
		treeNode<type> *root;
	
		tree();
		
		tree(type value);
		
		bool EsVacio(treeNode<type> *A);
		
		void createNode(treeNode<type> *&A,int Li,int Ls,Lista<type> *B);
		
		void postOrder(treeNode<type> *A);
		
		void Hojas(treeNode<type> *A,int &N);
		
		void insertTree(treeNode<type> *&A,Cola<tree<type>* > *&B,int &H,int &M);
};

template <typename type>

tree<type>::tree() 	//Constructor, inicializa la raiz en null
{
	root=NULL;
}

template <typename type>

tree<type>::tree(type value) //Constructor parametrizado que crea un nodo con un valor dado
{
	root= new treeNode<type>(value);	
}

template <typename type>

bool tree<type>::EsVacio(treeNode<type> *A) //Funcion que retorna si el arbol es vacio o no
{
	return (A==NULL);
}

template <typename type>

void tree<type>:: createNode(treeNode<type> *&A,int Li,int Ls,Lista<type> *B) //Accion que crea un arbol
{
	if(Li<Ls)
	{
		A= new treeNode<type>(B->Acceder((Li+Ls)/2));
		
		createNode(A->leftPtr,Li,((Li+Ls)/2),B);
		createNode(A->rigthPtr,((Li+Ls)/2)+1,Ls,B);
	}
}

template <typename type>

void tree<type>::postOrder(treeNode<type> *A) //Accion que recorre el arbol
{
	if(A!=NULL)
	{
		postOrder(A->leftPtr);
		postOrder(A->rigthPtr);
		cout<<A->data;
	}

}

template <typename type>

void tree<type>::Hojas(treeNode<type> *A,int &N) //Funcion que retorna el numero de hojas existentes en el arbol
{
	if(A!=NULL)
	{
		if(A->leftPtr==NULL && A->rigthPtr==NULL)
		{
			N+=1;
		
		}else
		{
			Hojas(A->leftPtr,N);
			Hojas(A->rigthPtr,N);
		}
	}
}

template <typename type>

void tree<type>::insertTree(treeNode<type> *&A,Cola<tree<type>* > *&B,int &H,int &M)//Accion que inserta los arboles secundarios en las hojas del arbol principal
{
	if(A!=NULL)
	{
		if(A->leftPtr==NULL && A->rigthPtr==NULL)
		{
			A->leftPtr= B->Primero()->root->leftPtr;
			A->rigthPtr= B->Primero()->root->rigthPtr;

			if((A->data==0) && (B->Primero()->root->data==1))
			{
				A->data=1;

				H+=1;
				
			}else if((A->data==1) && (B->Primero()->root->data==0))
			{
				A->data=0;
	
				M+=1;
			}
	
			B->Desencolar();
		}else
		{
			insertTree(A->leftPtr,B,H,M);
			insertTree(A->rigthPtr,B,H,M);
		}
	}
}

int Hombres=0;
int Mujeres=0;

int main()
{
	tree<int> *A= new tree<int>();
	tree<int> *D;
	Lista<int> *B= new Lista<int>();
	Cola<tree<int>* > *E= new Cola<tree<int>*>();
	
	long int n;
	
	int N=0;
	
	cin>>n;
	
	B=Binary(n);
	
	A->createNode(A->root,0,B->NumElem(),B);
	
	A->Hojas(A->root,N);
	
	B->~Lista();
	
	for(int i=0;i<N;i++)
	{
		D= new tree<int>();
		cin>>n;
		
		B=Binary(n);
		
		D->createNode(D->root,0,B->NumElem(),B);

		E->Encolar(D);
		
		B->~Lista();
		
	}
	
	A->insertTree(A->root,E,Hombres,Mujeres);	

	cout<<Hombres<<endl<<Mujeres<<endl;

	A->postOrder(A->root);

	cout<<endl;

	return 0;
}