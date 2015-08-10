#ifndef _Cola_H_
#define _Cola_H_
#include <iostream>
#include <stdlib.h>

using namespace std;

template <typename Tipo>

class Cola
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

		Nodo *PriPtr,*UltPtr;

		int NElem;

	public:

		Cola();

		~Cola();

		bool EsVacia();

		int NumElem();

		Tipo &Primero();

		void Encolar(Tipo Elemento);

		void Desencolar();

		void Imprimir();

};


template <typename Tipo>

Cola<Tipo>::Cola()
{
	PriPtr=NULL;
	UltPtr=NULL;
	NElem=0;
}

template <typename Tipo>

Cola<Tipo>::~Cola()
{
	while(NElem!=0)
	{
		Desencolar();
	}
}

template <typename Tipo>

bool Cola<Tipo>::EsVacia()
{
	return(PriPtr==NULL);

}

template <typename Tipo>

int Cola<Tipo>::NumElem()
{
	return NElem;
}

template <typename Tipo>

Tipo& Cola<Tipo>::Primero()
{
	if(PriPtr!=NULL)
	{
		return (PriPtr->Info);
	}
}

template <typename Tipo>

void Cola<Tipo>::Encolar(Tipo Elemento)
{
	Nodo *NuevoPtr=new Nodo(Elemento);

	if(PriPtr==NULL)
	{
		PriPtr=NuevoPtr;
		UltPtr=NuevoPtr;
	}else
	{
		UltPtr->ProxPtr=NuevoPtr;
		UltPtr=NuevoPtr;
	}

	NElem+=1;
}

template <typename Tipo>

void Cola<Tipo>::Desencolar()
{
	if(!EsVacia())
	{
		Nodo *AuxPtr=PriPtr;

		PriPtr=PriPtr->ProxPtr;

		delete(AuxPtr);

		if(PriPtr==NULL)
		{
			UltPtr=NULL;
		}

		NElem-=1;

		//cout<<"Desencolado"<<endl;
	}
}

template <typename Tipo>

void Cola<Tipo>::Imprimir()
{
	if(PriPtr!=NULL)
	{
		Nodo *AuxPtr;

		AuxPtr=PriPtr;
		
		while(AuxPtr!=NULL)
		{
			cout<<AuxPtr->Info<<endl;

			AuxPtr=AuxPtr->ProxPtr;
		}
	}
}
#endif