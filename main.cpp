#include <iostream>
#include <vector>
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h> 
#include <pthread.h>
#include <math.h>       /* cos */
#include <unistd.h>
#include <uC++.h>

#define PI 3.14159265
#define EJEX 640
#define EJEY 640

using namespace std;

_Task Pajaro;


_Monitor Mapa
{
	vector < vector < Pajaro* > > mapa;
	vector < Pajaro* > lista;
	uCondition mapaTomado;

public:
	Mapa()
	{
		mapa.resize(EJEX);
		for (int i = 0; i < EJEX; ++i)
		{
			vector < Pajaro* > ejeY (EJEY);
			mapa[i]=ejeY;
		}

	};
	~Mapa(){};

	void nacer (Pajaro *aux)
	{
		this->lista.push_back(aux);	
	};

	bool anadir (int posX, int posY, Pajaro *aux)
	{
		if (!mapaTomado.empty())
			mapaTomado.wait();

		mapaTomado.signalBlock();

		if (mapa[posX][posY]!=NULL)
			return false;
		mapa[posX][posY]=aux;

		mapaTomado.signal();
		
		return true;
	};

	bool eliminar (int posX, int posY, Pajaro *aux)
	{
		if (!mapaTomado.empty())
			mapaTomado.wait();

		mapaTomado.signalBlock();

		if (mapa[posX][posY]==NULL || mapa[posX][posY]!=NULL)
			return false;
		mapa[posX][posY]=NULL;
		
		mapaTomado.signal();
		
		return true;
	};

};

_Task Pajaro
{
	Mapa & control;

protected:
	
	void main ()
	{
		control.nacer(this);

		int posX, posY, angulo;

		srand (time(NULL));
		posX = rand() % EJEX;
		posY = rand() % EJEY;
		angulo = rand() % 360;
		cout << "Creada id: " << this << " X = " << posX << " Y = " << posY << " Ang = " << angulo  << endl;
		control.anadir(posX, posY, this);


		for(;;)
		{
			int auxposX = posX, auxposY = posY;
			double movX = sin ( angulo * PI / 180.0 );
			double movY = cos ( angulo * PI / 180.0 );

			if (movX >= 0.5)
			{
				posX++;
				if (posX > EJEX-1)
					posX = 0;

			}
			else if (movX <= -0.5)
			{
				posX--;
				if (posX < 0)
					posX = EJEX-1;
			}

			if (movY >= 0.5)
			{
				posY--;			
				if (posY < 0)
					posY = EJEY-1;

			}
			else if (movY <= -0.5)
			{
				posY++;
				if (posY > EJEY-1)
					posY = 0;
			}
			control.eliminar(auxposX, auxposY, this);
			control.anadir(posX, posY, this);

			cout << "Pájaro id: " << this << " X = " << posX << " Y = " << posY << " Ang = " << angulo  << endl;
			sleep(rand()%6);
		}
	};


public:	

	Pajaro(Mapa & control) : control(control) {};
	~Pajaro(){}; 
};



void uMain::main() 
{
	Mapa cielo ();
	Pajaro nuevo1 (cielo);
	usleep(300);
	Pajaro nuevo2 (cielo);
}