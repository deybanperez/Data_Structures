#include <iostream>
#include <stdlib.h>
#include <iostream>
#include <stdlib.h>
#include "Cola.h"
#include "Pila.h"
#include "Lista.h"
#include "ListaD.h"
#include <string>
#include <stdio.h>
//Pasar por parametro al gobernador y comparar con la disponibilidad de medicinas
//Acomodar el getline
//De ser posible acomodar para que las listas de las medicinas de farmacias y personas queden ordenadas por orden de llegada


using namespace std;

class Medicinas
{
	public:

		string Nombre;

		int Cantidad;

		Medicinas()
		{
			Nombre=" ";

			Cantidad=0;
		}

		Medicinas(string Nom,int Cant)
		{
			Nombre=Nom;

			Cantidad=Cant;
		}

};

class Persona
{
	public:

		int TiempoVida;

		int PosActualx;

		int PosActualy;

		string Nombre;

		Lista<Medicinas> ListaMedicinas;

		Pila<string> BolsoMedicinas;

		Persona();

		Persona(int Tiempo,string NombreP,int NMedicinas);

		bool Completo();
};

Persona::Persona()
{
	TiempoVida=0;
	Nombre=" ";
	PosActualx=0;
	PosActualy=0;
}

Persona::Persona(int Tiempo,string NombreP,int NMedicinas)
{
	TiempoVida=Tiempo;
	Nombre=NombreP;
	
	string NombreMedicina;
	int NumeroMedicina;

	for(int i=0;i<NMedicinas;i++)
	{
		cin>>NombreMedicina;
		cin>>NumeroMedicina;

		Medicinas Aux(NombreMedicina,NumeroMedicina);

		ListaMedicinas.InsertarPrimero(Aux);
	}
}

bool Persona::Completo()
{
	for(int i=0;i<ListaMedicinas.NumElem();i++)
	{
		if(ListaMedicinas.Acceder(i).Cantidad!=0)
			return false;
	}

	return true;
}

Cola<Persona*> *Fallecidos= new Cola<Persona*>();

Cola<Persona*> *Sobrevivientes = new Cola<Persona*>();

Lista<Medicinas*> *Gobernador= new Lista<Medicinas*>();


class Farmacia
{	
	public:
		string Nombre;
		
		int Posx;

		int Posy;

		Lista<Medicinas> Almacen;

		Farmacia();

		Farmacia(string NombreF,int Coorx,int Coory,int NumMedicinas);
		
		int Busqueda(Lista<Farmacia*> *Mapa,Persona *Cualquiera,int Dimensionx,int Dimensiony);
};

Farmacia::Farmacia()
{
	Nombre=" ";
	Posx=1;
	Posy=1;
}

Farmacia::Farmacia(string NombreF,int Coorx,int Coory,int NumMedicinas)
{
	Nombre=NombreF;
	Posx=Coorx;
	Posy=Coory;

	string NombreMedicina;
	int NumeroMedicina=0;

	for(int i=0;i<NumMedicinas;i++)
	{
		cin>>NombreMedicina;
		cin>>NumeroMedicina;

		Medicinas Aux(NombreMedicina,NumeroMedicina);
		Almacen.Insertar(i,Aux);
	}
}

int Farmacia::Busqueda(Lista<Farmacia*> *Mapa,Persona *Cualquiera,int Dimensionx,int Dimensiony)
{
	for (int j=1;j<=Dimensiony;j++)    //Recorrido por Columnas
	{
		Cualquiera->PosActualy=j;
		if(j%2!=0)//Si Columna es Impar
		{
			for(int i=1;i<=Dimensionx;i++) //Recorrido por Filas
			{
				Cualquiera->PosActualx=i;
				Cualquiera->TiempoVida-=1;//-1 T.V por cruzar la calle;

				if(Cualquiera->TiempoVida>0)
				{
					
					for(int k=0;k<Mapa->NumElem();k++)//Recorre Lista de Farmacias
					{
						if(Mapa->Acceder(k)->Posx==i && Mapa->Acceder(k)->Posy==j) //Revisa coordenadas i,j actuales y las compara con la lista de farmacias en la posicion (k)
						{
							//cout<<"Encontro Farmacia"<<i<<" , "<<j<<endl;
							for(int t=0;t<Mapa->Acceder(k)->Almacen.NumElem();t++)	//Compara medicinas de almacen contra medicinas de la lista de personas
							{
								for(int r=0;r<Cualquiera->ListaMedicinas.NumElem();r++)
								{
									if(Mapa->Acceder(k)->Almacen.Acceder(t).Nombre == Cualquiera->ListaMedicinas.Acceder(r).Nombre)
									{
										int w=0;

										while((Gobernador->Acceder(w)->Nombre != Cualquiera->ListaMedicinas.Acceder(r).Nombre) && (w<Gobernador->NumElem()))
										{
											w+=1;
										}
										if(Mapa->Acceder(k)->Almacen.Acceder(t).Cantidad==0 || Cualquiera->ListaMedicinas.Acceder(r).Cantidad==0 || Gobernador->Acceder(w)->Cantidad==0)
										{
										}else
										{
											int cont=1;
											while((Gobernador->Acceder(w)->Cantidad >= cont) && Cualquiera->ListaMedicinas.Acceder(r).Cantidad>0 && Mapa->Acceder(k)->Almacen.Acceder(t).Cantidad>0)   
											{
												if((Mapa->Acceder(k)->Almacen.Acceder(t).Cantidad>0) && (Cualquiera->ListaMedicinas.Acceder(r).Cantidad>0))
												{
													Mapa->Acceder(k)->Almacen.Acceder(t).Cantidad-=1;
													Cualquiera->ListaMedicinas.Acceder(r).Cantidad-=1;												
													//cout<<"Apile "<<Cualquiera->ListaMedicinas.Acceder(r).Nombre<<endl;	

													Cualquiera->BolsoMedicinas.Apilar(Cualquiera->ListaMedicinas.Acceder(r).Nombre);
												}
											}
										}
									}
								}
							}

							if(Cualquiera->Completo())
							{
								Sobrevivientes->Encolar(Cualquiera);

								return 0;
							}
						
							Cualquiera->TiempoVida-=1;
						}
				
					}
				}else
				{
					Fallecidos->Encolar(Cualquiera);
					
					return 0;
				}
			}
		
		}else
		{
			for(int i=Dimensionx;i>0;i--) //i=Filas
			{
				Cualquiera->PosActualx=i;
				
				Cualquiera->TiempoVida-=1;//-1 T.V por cruzar la calle;

				if(Cualquiera->TiempoVida>0)
				{	
					for(int k=0;k<Mapa->NumElem();k++)//Recorre Lista de Farmacias
					{
						if(Mapa->Acceder(k)->Posx==i && Mapa->Acceder(k)->Posy==j) //Revisa coordenadas i,j actuales y las compara con la lista de farmacias en la posicion (k)
						{
							//cout<<"EncontroFarmacia "<<i<<" "<<j<<endl;
							for(int t=0;t<Mapa->Acceder(k)->Almacen.NumElem();t++)	//Compara medicinas de almacen contra medicinas de la lista de personas
							{
								for(int r=0;r<Cualquiera->ListaMedicinas.NumElem();r++)
								{
									if(Mapa->Acceder(k)->Almacen.Acceder(t).Nombre == Cualquiera->ListaMedicinas.Acceder(r).Nombre)
									{
										int w=0;
	
										while((Gobernador->Acceder(w)->Nombre != Cualquiera->ListaMedicinas.Acceder(r).Nombre) && (w<Gobernador->NumElem()))
										{
											w+=1;
										}
										if(Mapa->Acceder(k)->Almacen.Acceder(t).Cantidad==0 || Cualquiera->ListaMedicinas.Acceder(r).Cantidad==0 || Gobernador->Acceder(w)->Cantidad==0)
										{
										}else
										{
											int cont=1;
											while((Gobernador->Acceder(w)->Cantidad >= cont) && Cualquiera->ListaMedicinas.Acceder(r).Cantidad>0 && Mapa->Acceder(k)->Almacen.Acceder(t).Cantidad>0)
											{
												
												if((Mapa->Acceder(k)->Almacen.Acceder(t).Cantidad>0) && (Cualquiera->ListaMedicinas.Acceder(r).Cantidad>0))
												{	
													Mapa->Acceder(k)->Almacen.Acceder(t).Cantidad-=1;
													Cualquiera->ListaMedicinas.Acceder(r).Cantidad-=1;
													//cout<<"Apile "<<Cualquiera->ListaMedicinas.Acceder(r).Nombre<<endl												;	

													Cualquiera->BolsoMedicinas.Apilar(Cualquiera->ListaMedicinas.Acceder(r).Nombre);

													cont+=1;
												}
											}
										}
									}
								}
							}

							if(Cualquiera->Completo())
							{
								Sobrevivientes->Encolar(Cualquiera);

								return 0;
							}
						
							Cualquiera->TiempoVida-=1;
						}
				
					}
				}else
				{
					Fallecidos->Encolar(Cualquiera);
					return 0;
				}
			}
		}
	
	}

	Fallecidos->Encolar(Cualquiera);

	return 0;

}
Lista<Farmacia*> *ListaFarmacias= new Lista<Farmacia*>();
Cola<Persona*> *ColaPersona= new Cola<Persona*>() ;
int main()
{
	int n;
	int Tiempo;
	int NM;
	string Nombre;
	string Nombre1;
	int Posix;
	int Posiy;
	int Dimensionx=0;
	int Dimensiony=0;

	cin>>n;

	for(int i=0;i<n;i++)
	{
		cin>>Nombre;
		cin>>Tiempo;
		cin>>NM;

		Persona * Deyban = new Persona(Tiempo,Nombre,NM);

		ColaPersona->Encolar(Deyban);
	}
	
	cin>>n;

	for(int i=0;i<n;i++)
	{
		cin>>Nombre;
		cin>>Posix;
		cin>>Posiy;
		cin>>NM;

		if(Posix>Dimensionx)
			Dimensionx=Posix;	

		if(Posiy>Dimensiony)
			Dimensiony=Posiy;

		Farmacia * Deyban = new Farmacia(Nombre,Posix,Posiy,NM);

		ListaFarmacias->Insertar(i,Deyban);
	}

	cin>>n;

	for(int i=0;i<n;i++)
	{
		cin>>Nombre;
		cin>>NM;

		Medicinas *Aux = new Medicinas(Nombre,NM);

		Gobernador->Insertar(i,Aux);
	}

	Farmacia *Diego = new Farmacia();

	while(!ColaPersona->EsVacia())
	{
		Diego->Busqueda(ListaFarmacias,ColaPersona->Primero(),Dimensionx,Dimensiony);

		ColaPersona->Desencolar();
	}
	
	cout<<Fallecidos->NumElem()<<endl;
	while(!Fallecidos->EsVacia())
	{
	cout<<Fallecidos->Primero()->Nombre<<" "<<Fallecidos->Primero()->PosActualx<<" "<<Fallecidos->Primero()->PosActualy<<endl;

	if(Fallecidos->Primero()->BolsoMedicinas.EsVacia())
	{
		cout<<"VACIO"<<endl;
	}else
	{

		while(!Fallecidos->Primero()->BolsoMedicinas.EsVacia())
		{
			cout<<Fallecidos->Primero()->BolsoMedicinas.Tope()<<endl;

			Fallecidos->Primero()->BolsoMedicinas.Desapilar();
		}
	}
		
		Fallecidos->Desencolar();

		
	}

	cout<<Sobrevivientes->NumElem()<<endl;
	while(!Sobrevivientes->EsVacia())
	{
		cout<<Sobrevivientes->Primero()->Nombre<<" "<<Sobrevivientes->Primero()->TiempoVida<<endl;

		if(Sobrevivientes->Primero()->BolsoMedicinas.EsVacia())
		{
			cout<<"VACIO"<<endl;
		}else
		{
			while(!Sobrevivientes->Primero()->BolsoMedicinas.EsVacia())
			{
				cout<<Sobrevivientes->Primero()->BolsoMedicinas.Tope()<<endl;

				Sobrevivientes->Primero()->BolsoMedicinas.Desapilar();

			}
		}

			Sobrevivientes->Desencolar();
	}
	
	return 0;
}
