
#include "mapa.h"
#include "pajaro.h"

using namespace std;

void Pajaro::main ()
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

