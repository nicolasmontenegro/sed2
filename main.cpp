#include <iostream>
#include <vector>
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h> 
#include <pthread.h>
#include <math.h>       /* cos */
#include <unistd.h>

#define PI 3.14159265
#define EJEX 640
#define EJEY 640

using namespace std;

class Pajaro
{
public:
	int posX, posY, angulo;
	double punt; 
	Pajaro()
	{
		srand (time(NULL));
		posX = rand() % EJEX;
		posY = rand() % EJEY;
		angulo = rand() % 360;
		cout << "Pájaro id: " << this << " X = " << posX << " Y = " << posY << " Ang = " << angulo  << endl;
	};
	~Pajaro(){};

	void esto ()
	{
		cout << this << endl;
	};

	void volar ()
	{
		double movX = sin ( this->angulo * PI / 180.0 );
		double movY = cos ( this->angulo * PI / 180.0 );

		if (movX >= 0.5)
		{
			this->posX++;
			if (this->posX > 640)
				this->posX = 0;

		}
		else if (movX <= -0.5)
		{
			this->posX--;
			if (this->posX < 0)
				this->posX = 640;
		}

		if (movY >= 0.5)
		{
			this->posY--;			
			if (this->posY < 0)
				this->posY = 99;

		}
		else if (movY <= -0.5)
		{
			this->posY++;
			if (this->posY > 99)
				this->posY = 0;
		}
	};

	
};

class Monitor
{
public:

	vector < vector < vector < Pajaro* > > > mapa;
	vector < Pajaro* > lista;

	Monitor()
	{
		mapa.resize(EJEX);
		for (int i = 0; i < 100; ++i)
		{
			vector < vector < Pajaro* > > ejeY (EJEY);
			mapa[i]=ejeY;
		}

	};

	~Monitor(){};

	void nuevoPajaro ()
	{
		Pajaro *nuevo = new Pajaro(); 
		if (!this->mapa[nuevo->posX][nuevo->posY].size())
		{
			vector < Pajaro* > bandada; 
			this->mapa[nuevo->posX][nuevo->posY] = bandada;
		}
		this->mapa[nuevo->posX][nuevo->posY].push_back(nuevo);
		this->lista.push_back(nuevo);		
	};

	void update ()
	{
		for (int i = 0; i < this->lista.size(); ++i)
		{
			this->lista[i]->volar();
			cout <<  this->lista[i]->posX << " " << this->lista[i]->posY << endl;
		}

		sleep(1);
		this->update();
	};

	
};

int main(int argc, char const *argv[])
{

	Monitor cielo;
	cielo.nuevoPajaro();
	cielo.update();
	return 0;
}