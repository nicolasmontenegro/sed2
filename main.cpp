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
#include "pajaro.h"

#define PI 3.14159265
#define EJEX 640
#define EJEY 640

using namespace std;



void uMain::main() 
{
	Mapa *cielo = new Mapa();
	Pajaro nuevo1 (*cielo);
	usleep(300);
	Pajaro nuevo2 (*cielo);
}