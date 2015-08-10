#ifndef _ListaD_H_
#define _ListaD_H_
#include <new>
#include <iostream>
using namespace std;

template <typename Tipo>
class ListaD {
	
	private:
	class Nodo {
	public:
	Tipo Dato;
	Nodo * Ant;
	Nodo * Prox;
	Nodo (Nodo * P=NULL,Nodo * A=NULL){
        Ant=A; 
        Prox=P; 
    }
         
	};	
 //////////////////////////////ATRIBUTOS DE LA CLASE LISTAD/////////////////////////////////////	
	int N;
	Nodo * Pri;
	public:
	typedef Nodo * Posicion;
////////////////////////////////////////////////////////////////////////////////////////////////
ListaD();           //Constructor de la Clase
////////////////////////////////////////////////////////////////////////////////////////////////
 ~ListaD();         //Destructor de la Clase
////////////////////////////////////////////////////////////////////////////////////////////////

int Tamano()const;          //Retorna el Tamaño de la Lista                    
//////////////////////////////////////////////////////////////////////////////////////////////

Posicion Fin() const; //Retorna el Fin de la Lista -> NULL
//////////////////////////////////////////////////////////////////////////////////////////////

Posicion Comienzo ()const; //Retorna el Principio de la Lista
//////////////////////////////////////////////////////////////////////////////////////////////

Posicion Ultimo () const; //Retorna el Ultimo Elemento de la Lista
//////////////////////////////////////////////////////////////////////////////////////////////

void Siguiente(Posicion &P)const;     //P Apunta al Siguiente Nodo    
////////////////////////////////////////////////////////////////////////////////////////////////

void Anterior (Posicion &P)const; //P Apunta al Nodo Anterior
//////////////////////////////////////////////////////////////////////////////////////////////// 
         
bool Vacia()const;           //Retorna true si la Lista Tiene Elementos                     
////////////////////////////////////////////////////////////////////////////////////////////////
       
Tipo & Acceder(const Posicion &P); //Retorna el Elemento Guardado en la Posicion P                 
////////////////////////////////////////////////////////////////////////////////////////////////

void Apilar (const Tipo &Dat);  //Inserta el Dato T al Final de la Lista
//////////////////////////////////////////////////////////////////////////////////////////////

void PostInsertar(Posicion P,const Tipo &Dato); //Insertar un Elemento despues del Elemento P   
////////////////////////////////////////////////////////////////////////////////////////////////
    
void Eliminar(Posicion P);     //Elimina el Elemento de la Posicion P             
////////////////////////////////////////////////////////////////////////////////////////////////

Posicion Find(Tipo T);  //Busca el dato T y Retorna una Posicion
////////////////////////////////////////////////////////////////////////////////////////////////
     
void Imprimir ()const;         // Imprime por Pantalla todos los Elementos de la Lista            
////////////////////////////////////////////////////////////////////////////////////////////////  
};

#include <stdio.h>
#include <iostream>
#include <new>
using namespace std; 

/////////////////////////////////////////////////////////////////////////////////////////////
template <typename Tipo>
ListaD<Tipo>::ListaD() : Pri(NULL), N(0)
{
}
/////////////////////////////////////////////////////////////////////////////////////////////
template <typename Tipo>
 ListaD<Tipo>::~ListaD() {
	      Nodo * P;
	
	       while (Pri != NULL){
		         P = Pri;
		         Pri= Pri->Prox;
		         delete (P); 
               }
               N=0;
} 
/////////////////////////////////////////////////////////////////////////////////////////////
template <typename Tipo>
typename ListaD<Tipo>::Posicion 
ListaD<Tipo>::Comienzo() const {
return Pri;
} 
/////////////////////////////////////////////////////////////////////////////////////////////
template <typename Tipo>
typename ListaD<Tipo>::Posicion 
ListaD<Tipo>::Ultimo() const {
return Pri->Ant;
} 
//////////////////////////////////////////////////////////////////////////////////////////////
template <typename Tipo>
typename ListaD<Tipo>::Posicion 
ListaD<Tipo>::Fin() const {
return NULL;
} 

//////////////////////////////////////////////////////////////////////////////////////////////
template <typename Tipo>

int ListaD<Tipo>::Tamano ()const{
 return(N);   
}
////////////////////////////////////////////////////////////////////////////////////////////////
template <typename Tipo>

void ListaD<Tipo>::Siguiente(Posicion &P)const{
     //cout<<"P era Igual a:"<<P<<endl;
  if(P!=NULL) P=P->Prox; 
  else P=Pri;
    //cout<<"P ahora es: " <<P<<endl;
}
////////////////////////////////////////////////////////////////////////////////////////////////
template <typename Tipo>

void ListaD<Tipo>::Anterior(Posicion &P)const{	
   if(P!=NULL) P=P->Ant; // Con el Apuntador Anterior la Lista es Infinita por eso no hay Precondicion
}
////////////////////////////////////////////////////////////////////////////////////////////////
template <typename Tipo>

bool ListaD<Tipo>::Vacia()const{
return(N==0);
}
////////////////////////////////////////////////////////////////////////////////////////////////
template <typename Tipo>

Tipo& ListaD<Tipo>::Acceder(const Posicion &P){ 
      if(P!=NULL)return(P->Dato);
}
////////////////////////////////////////////////////////////////////////////////////////////////
template <typename Tipo>

void ListaD<Tipo>::Apilar(const Tipo &Dat){ 
 Nodo * Nn=new(nothrow) Nodo;
 Nn->Dato=Dat;
 Nn->Prox=NULL;

if((Pri==NULL) &&(N==0)){  // La Lista esta vacia
	Nn->Ant=Nn;
	Pri=Nn;
	}else{ // La Lista no esta vacia
             (Pri->Ant)->Prox=Nn;	// Al Ultimo -> Prox le Asigno el Nuevo Nodo 		     
	     Nn->Ant=Pri->Ant;          //Al Nuevo Nodo -> Ant le Asigno el Ultimo
	     Pri->Ant=Nn;               // Actualizo el Ultimo
	     }
++N;
} 
////////////////////////////////////////////////////////////////////////////////////////////////
  template <typename Tipo>

void ListaD<Tipo>::PostInsertar(Posicion P,const Tipo &Dat){
 Nodo * Nn=new(nothrow)Nodo;
 Nn->Dato=Dat;
 
	if((Pri!=NULL) &&(P==NULL) && (N>0)){ //Insertar de Primero con la Lista Llena
	//cout<<"Lista con Elementos pero Insertan al Principio"<<endl;
	Nn->Prox=Pri;
	Nn->Ant=Pri->Ant;
	Pri=Nn;
	++N;
	return;
	}


	if((Pri==NULL)&&(P==NULL)){ //La Lista esta Vacia
	//cout<<"Inserte,La Lista estaba Vacia"<<endl;
	Nn->Prox=NULL;
	Nn->Ant=Nn;
	Pri=Nn;
	//cout<<"Direccion de PRI ahora es: "<<Pri<<endl;
	}else{       //La Lista no esta Vacia

		if((P==Pri)&&(N==1)){ //Solo Hay un Elemento
		  //cout<<"Inserte, La Lista tenia un Solo Elemento"<<endl;
		  Nn->Ant=Pri;		
		  Nn-> Prox=NULL;
		  Pri->Prox=Nn;
		  Pri->Ant=Nn;
		  }else{ // No es el Primer Elemento

		       if(P->Prox==NULL){ // Inserto al Final de la Lista
		       //cout<<"Inserte, al final de la Lista"<<endl;			
		       Nn->Prox=NULL;
		       Nn->Ant=P;
		       P->Prox=Nn;			     
		       Pri->Ant=Nn;

		         }else{  //Voy a Insertar entre 2 Nodos
			  //cout<<"Inserte,entre 2 Nodos"<<endl;
			  Nn->Prox=P->Prox;
		          Nn->Ant=P;
			  P->Prox=Nn;
			  Nn->Prox->Ant=Nn;
			 }	
		}
       }
++N;
}
/////////////////////////////////////////////////////////////////////////////////////////////////
template <typename Tipo>
void ListaD<Tipo>::Eliminar(Posicion P){
    
if((Pri==NULL)||(P==NULL))return; // La Lista esta Vacia

if((P==Pri)&&(Pri->Prox==NULL)){ //Elimino el Unico Elemento de la Lista
Pri=NULL;
}else{
 	if((P==Pri) && (Pri->Prox!=NULL)){ //Elimino el Primer Elemento de una Lista con varios Elementos
	Pri=Pri->Prox;
	Pri->Ant=P->Ant;
	}else{
		if(P->Prox==NULL){ // Elimino el Ultimo Nodo de la Lista
		(P->Ant)->Prox=NULL;
		Pri->Ant=P->Ant;
		}else{             //Elimino entre 2 Nodos
		      P->Prox->Ant=P->Ant;	
		      P->Ant->Prox=P->Prox;
		      }
              }
}
--N;
delete P;
}
/////////////////////////////////////////////////////////////////////////////////////////////////
template <typename Tipo>

void ListaD<Tipo>::Imprimir()const{
     Nodo * Aux;
     Aux=Pri;
     
     while(Aux!=NULL){
     cout<<Aux->Dato<<endl;
     Aux=Aux->Prox;                     
     }  
     }
/////////////////////////////////////////////////////////////////////////////////////////////////
template <typename Tipo>
typename ListaD<Tipo>::Posicion
ListaD<Tipo>::Find(Tipo T)  {

//////////////////////////////////////////////
//Precondicion la Lista no Puede estar Vacia//
//////////////////////////////////////////////

Nodo * Inicio=NULL;

if(T<(Inicio->Dato)) return Inicio;

Inicio=Pri;

while(Inicio!=NULL){
	if(T<(Inicio->Dato)){ 
	return Inicio;
	}else{
	Inicio=Inicio->Prox;
	}
} 
return (Pri->Ant); // El Dato T es Mayor que cualquier Elemento de la Lista -> Mando el Ultimo ELemento de la Lista
}
///////////////////////////////////////////////////////////////////////////////////////////////
#endif

