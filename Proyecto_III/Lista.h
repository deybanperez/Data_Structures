#ifndef _Lista_H_
#define _Lista_H_
#include <iostream>
#include <stdlib.h>
using namespace std;

template <typename Tipo>

class Lista
{
	private:

		class Nodo
		{
			public:
			
				Tipo  Info;
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

		int NElem;

		Nodo *PriPtr;

	public:

		typedef Nodo *Posicion;

		Lista();

		~Lista();

		int NumElem();

		bool EsVacia();

		Tipo & Primero();

		Tipo & Ultimo();

		Tipo & Acceder(int Pos);

		void Insertar(int Posicion,Tipo Elemento);
		
		void InsertarPrimero(Tipo Elemento);
		
		void Imprimir();

};

template <typename Tipo>

Lista<Tipo>::Lista()
{
	NElem=0;

	PriPtr=NULL;
}

template <typename Tipo>

Lista<Tipo>::~Lista()
{
	Nodo *AuxPtr;

	while(PriPtr!=NULL)
	{
		AuxPtr=PriPtr;
		PriPtr=PriPtr->ProxPtr;
		delete(AuxPtr);
	}
	NElem=0;
}

template <typename Tipo>

int Lista <Tipo>::NumElem()
{
	return (NElem);
}

template <typename Tipo>

bool Lista <Tipo>::EsVacia()
{
	return(PriPtr==NULL);
}

template <typename Tipo>
 
Tipo& Lista<Tipo>::Primero()
{
return (PriPtr->Info);
} 

template <typename Tipo>

Tipo& Lista<Tipo>::Ultimo()
{
	Nodo *AuxPtr=PriPtr;
	
	while(AuxPtr->ProxPtr!=NULL)
	{
		AuxPtr=AuxPtr->ProxPtr;
	}
	
	return (AuxPtr->Info);
}

template <typename Tipo>

Tipo& Lista<Tipo>::Acceder(int Pos)
{
	if(Pos>=0 && Pos<=NElem && !EsVacia())
	{
		int Cont=0;
		
		Nodo *AuxPtr=PriPtr;
		
		while(Cont<Pos)
		{
			AuxPtr=AuxPtr->ProxPtr;

			Cont+=1;
		}
	
		return(AuxPtr->Info);
	}
}

template <typename Tipo>

void Lista<Tipo>::Insertar(int Pos,Tipo Elemento)
{
	if(!EsVacia())
	{
		if(Pos<=NElem && Pos>0)
		{	
			int Cont=0;
	
			Nodo *NuevoPtr=new Nodo(Elemento);
		
			Nodo *AuxPtr=PriPtr;
		
			while(Cont<Pos-1)
			{
				AuxPtr=AuxPtr->ProxPtr;

				Cont+=1;
			}
		
			NuevoPtr->ProxPtr=AuxPtr->ProxPtr;
		
			AuxPtr->ProxPtr=NuevoPtr;
		
			NElem+=1;
		}else if(Pos==0)
		{
			InsertarPrimero(Elemento);
		}
	}else 
	{
		if(Pos==0)
		{
		InsertarPrimero(Elemento);
		}
	}
}

template <typename Tipo>

void Lista<Tipo>::InsertarPrimero(Tipo Elemento)
{
	Nodo *NuevoPtr=new Nodo(Elemento);

	if(EsVacia())
		PriPtr=NuevoPtr;
	else
	{
		NuevoPtr->ProxPtr=PriPtr;
		
		PriPtr=NuevoPtr;
	}

	NElem+=1;
}

template <typename Tipo>

void Lista<Tipo>::Imprimir()
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