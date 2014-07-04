#include <iostream>
#include <vector>
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h> 
#include <pthread.h>
#include <math.h>       /* cos */
#include <unistd.h>

#define PI 3.14159265

using namespace std;

class Pajaro
{
public:
	int posX, posY, angulo;
	double punt; 
	Pajaro()
	{
		srand (time(NULL));
		posX = rand() % 100;
		posY = rand() % 100;
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
		double movX = cos ( this->posX * PI / 180.0 );
		double movY = sin ( this->posY * PI / 180.0 );

		if (movX >= 0.5)
		{
			if (this->angulo > 180 && this->angulo < 360)			
				this->posX++;
			else
				this->posX--;

			if (this->posX > 99)
				this->posX = 0;
			if (this->posX < 0)
				this->posX = 99;

		}
		if (movY >= 0.5)
		{
			if (this->angulo > 90 && this->angulo < 270)			
				this->posY++;
			else
				this->posY--;
			
			if (this->posY > 99)
				this->posY = 0;
			if (this->posY < 0)
				this->posY = 99;

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
		mapa.resize(100);
		for (int i = 0; i < 100; ++i)
		{
			vector < vector < Pajaro* > > ejeY (100);
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