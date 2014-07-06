#ifndef MAPA_H
#define MAPA_H

#include <iostream>
#include <vector>
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h> 
#include <pthread.h>
#include <math.h>       /* cos */
#include <unistd.h>
#include <uC++.h>
#include "pajaro.h"

#define PI 3.14159265
#define EJEX 640
#define EJEY 640

using namespace std;

_Mutex Mapa
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

	void nacer (Pajaro *aux);
	bool anadir (int posX, int posY, Pajaro *aux);
	bool eliminar (int posX, int posY, Pajaro *aux);
};

#endif