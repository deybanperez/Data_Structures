#ifndef _Pila_H_
#define _Pila_H_
#include <iostream>
#include <stdlib.h>

using namespace std;

template <typename Tipo>

class Pila
{	
	private:

		class Nodo
		{
			public:

					Tipo Info;

					Nodo *ProxPtr;

					Nodo ()
					{
						ProxPtr=NULL;
					}

					Nodo(Tipo Elemento)
					{
						Info=Elemento;

						ProxPtr=NULL;
					}
		};

		Nodo *TopePtr;

		int NElem;

	public:

		Pila();

		~Pila();

		int NumElem();

		bool EsVacia();

		Tipo & Tope();

		void Apilar(Tipo Elemento);

		 void Desapilar();

		void Imprimir();
};

template <typename Tipo>

Pila<Tipo>::Pila()
{
	NElem=0;

	TopePtr=NULL;	
}

template <typename Tipo>

Pila<Tipo>::~Pila()
{
	while(TopePtr!=NULL)
	{
		Desapilar();
	}
}

template <typename Tipo>

int Pila<Tipo>::NumElem()
{
	return (NElem);
}

template <typename Tipo>

bool Pila<Tipo>::EsVacia()
{
	return (TopePtr==NULL);
}

template <typename Tipo>

Tipo& Pila<Tipo>::Tope()
{
	if(TopePtr!=NULL)
		return TopePtr->Info;
}

template <typename Tipo>

void Pila<Tipo>::Apilar(Tipo Elemento)
{
	Nodo *NuevoPtr=new Nodo(Elemento);

	NuevoPtr->ProxPtr=TopePtr;

	TopePtr=NuevoPtr;

	NElem+=1;
}

template <typename Tipo>


void Pila<Tipo>::Desapilar()
{
	if(!EsVacia())
	{
		Nodo *AuxPtr=TopePtr;

		TopePtr=TopePtr->ProxPtr;

		delete (AuxPtr);

		NElem-=1;
	}
}

template <typename Tipo>

void Pila<Tipo>::Imprimir()
{
	if(!EsVacia())
	{
		Nodo *AuxPtr=TopePtr;

		while(AuxPtr!=NULL)
		{
			cout<<AuxPtr->Info<<endl;

			AuxPtr=AuxPtr->ProxPtr;
		}
	}
}

#endif