#include <iostream>
#include <vector>
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h> 
#include <pthread.h>
#include <math.h>       /* cos */
#include <unistd.h>
#include <uC++.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

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
		cout << "pio ctm!" << endl;
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
	Mapa *cielo;
	int posX, posY, angulo;

protected:
	
	void main ()
	{
		cielo->nacer(this);
		//cout << "Creada id: " << this << " X = " << posX << " Y = " << posY << " Ang = " << angulo  << endl;
		cielo->anadir(posX, posY, this);


		for(;;)
		{
			//int auxposX = posX, auxposY = posY;
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
			//control.eliminar(auxposX, auxposY, this);
			//control.anadir(posX, posY, this);

			cout << "P�jaro id: " << this << " X = " << posX << " Y = " << posY << " Ang = " << angulo  << endl;
			sleep(1);
		}
	};


public:	

	Pajaro(int posX, int posY, int angulo, Mapa *cielo) : posX(posX), posY(posY), angulo(angulo), cielo(cielo) {};
	~Pajaro(){}; 
};

void display(){
    while(1){
	    glClear(GL_COLOR_BUFFER_BIT);
	    glColor3f(1.0, 0.0, 0.0);

	    /*dibujarCuadrados();
	    dibujarLineasRojas();
    	draw();*/

	    
	    glFlush();
	    //sleepcp(1000);
	    //sleep(1);
    }
}

void setup(){
    glClearColor(0.0, 0.0, 0.0, 1.0); // Color de fondo (negro)
    gluOrtho2D(0, EJEX, 0, EJEY);
}

void uMain::main() 
{
	glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(300, 300); // Posicion de la ventana en pixeles
    glutInitWindowSize(EJEX, EJEY); // Tamano de la ventana en pixeles
    glutCreateWindow("Aves"); // Titulo de la ventana
    glutDisplayFunc(display); // display es la funcion que



	srand (time(NULL));
	Mapa *cielo = new Mapa();
	vector <Pajaro*> bandada;
	for(int i = 0; i <1; ++i)
		bandada.push_back(new Pajaro(rand() % EJEX, rand() % EJEY, rand() % 360, cielo));


	setup();

	glutMainLoop();
}
