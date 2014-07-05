#ifndef PAJARO_H
#define PAJARO_H

#include <uC++.h>
#include <iostream>
#include <vector>
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h> 
#include <pthread.h>
#include <math.h>       /* cos */
#include <unistd.h>


#include "mapa.h"

#define PI 3.14159265
#define EJEX 640
#define EJEY 640

using namespace std;

_Task Pajaro
{
private:
	Mapa & control;

protected:
	void main ();
	
public:	
	Pajaro (Mapa & control) : control(control) {}
	~Pajaro() {}
};

#endif