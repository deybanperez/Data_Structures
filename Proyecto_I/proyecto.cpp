#include <iostream>

using namespace std;
//Declaracion de un registro global para poder usarlo dentro de la clase Daryl
struct Datos
{
	string NombreCalle;
	int LugarInicio;
	int LugarFin;
	int NumZombies; 
};

class Daryl
//Declaracion de la clase Daryl
{
	private:
		//Atributos
		bool Lugares[25];						//Arreglo de booleanos para marcar si un lugar ya fue visitado
		Datos Coleccion[400];					//Arreglo de tipo Dato(registro declarado previamente) para almacenar los datos de las calles
		int SitiosVisitar;						//Variable entera que toma valores que indican el numero de lugares a visitar
		int NumeroCalles;						//Variable entera que indica el numero de calles que existen	
		int globalzombies;						//Variable entera en la cual se almacenan la mejor solucion de zombies
		string globalcalles [25];				//Arreglo de strings en el cual se almacenan las calles por las que se tuvo que pasar para llegar a la solcuion

	public:
		//Metodos
		Daryl();
			//Constructor, inicializa los valores de los atributos arbitrariamente
		void Cargar_Datos(int g,int t);
			//Metodo que lee los datos suministrados por la consola
		void Busqueda(int Ubicacion, int SumaZombies, string Calles[],int iCalles);
			//Metodo Backtracking para hallar la mejor solucion al problema
		bool EsSolucion(int Sitios);
			//Metodo que verifica si se llego a la solucion final valida o no
		void Imprimir_Zombies();
			//Metodo que imprime el valor de la variable(globalzombies)
		void Imprimir_Calles(int a);
			//Metodo que imprime el nombre de las calles por las que se tuvo que pasar para alcanzar la solucion
};

//Implementacion de los metodos

Daryl::Daryl()
{
	SitiosVisitar=0;
	NumeroCalles=0;
	globalzombies=99999;
	
	int j;

	for(j=0;j<400;j++)
	{
		Coleccion[j].NombreCalle=" ";
		Coleccion[j].LugarInicio=0;
		Coleccion[j].LugarFin=0;
		Coleccion[j].NumZombies=0;
	}

	for(j=0;j<25;j++)
	{
		Lugares[j]=false;
		globalcalles[j]=" ";
	}
}

void Daryl::Cargar_Datos(int AVisitar, int NumCalles)
{
	int i=0;

	SitiosVisitar=AVisitar;
	NumeroCalles=NumCalles;
	globalzombies=99999;

	for(i=0;i<NumCalles;i++)
	{
		cin>>Coleccion[i].NombreCalle;
		cin>>Coleccion[i].LugarInicio;
		cin>>Coleccion[i].LugarFin;
		cin>>Coleccion[i].NumZombies;
	}

	for(i=0;i<AVisitar;i++)
	{
		Lugares[i]=false;
		globalcalles[i]=" ";
	}
}

bool Daryl::EsSolucion(int Sitios)
{
	int i;

	for(i=0;i<Sitios;i++)
	{
		if(Lugares[i]==false)
			return false;
	}

	return true;
}

void Daryl::Busqueda(int Ubicacion, int SumaZombies, string Calles[],int iCalles)
{
	int i=0;
	
	for(i=0;i<NumeroCalles;i++)
	{
		if(((Coleccion[i].LugarInicio==Ubicacion)||(Coleccion[i].LugarFin==Ubicacion)))
		{
			if(Lugares[Ubicacion-1]==false)
			{
				Calles[iCalles]=Coleccion[i].NombreCalle;
				int aux;
				if(Coleccion[i].LugarInicio==Ubicacion)
				{
					aux=Coleccion[i].LugarFin;
				}else
				{
					aux=Coleccion[i].LugarInicio;
				}
				Lugares[Ubicacion-1]=true;

				if(EsSolucion(SitiosVisitar))
				{
					if(globalzombies > SumaZombies)
					{
						globalzombies = SumaZombies;

						for(int k=0;k<SitiosVisitar;k++)
						{
							globalcalles[k]=Calles[k];

						}
			
						Lugares[Ubicacion-1]=false;						
						break;
					}
				}else
				{
					
					Busqueda(aux, SumaZombies +Coleccion[i].NumZombies, Calles,iCalles+1);						
				}
				Lugares[Ubicacion-1]=false;
			}
		}
	}
}

void Daryl::Imprimir_Zombies()
{
	cout<<globalzombies<<endl;
}

void Daryl::Imprimir_Calles(int a)
{
	for(int i=0;i<a-1;i++)
		{
			cout<<globalcalles[i]<<" ";
		}
	
}

//Funcion principal

int main ()
{
	Daryl * A = new Daryl();

	int a,b;

	cin>>a;
	cin>>b;

	string s[400];

	if(a==1)
	{
		cout<<"0"<<endl;
	}else
	{

		A->Cargar_Datos(a,b);

		A->Busqueda(1,0,s,0);

		A->Imprimir_Zombies();

		A->Imprimir_Calles(a);
		cout << endl;
	}
	return 0;
}
