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
#define CANTIDAD 10

using namespace std;


/*_Task Pajaro;


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

};*/



_Task Pajaro
{
	//Mapa *cielo;
	float posX, posY, angulo;

protected:
	
	void main ()
	{
		//cielo->nacer(this);
		cout << "Creada id: " << this << " X = " << posX << " Y = " << posY << " Ang = " << angulo  << endl;
		//cout << "rad " << ( angulo * PI / 180.0 ) << endl;
		//cielo->anadir(posX, posY, this);


		while(1)
		{
			auxposX = posX;
			auxposY = posY;
			auxAngulo = angulo;
			float movX = pow (sin ( angulo * PI / 180.0 ), 2);
			if (angulo < 360 && angulo > 180)
				movX *= -1.0;
			float movY = pow (cos ( angulo * PI / 180.0 ), 2);
			if (angulo > 90 && angulo < 270)
				movY *= -1.0;

			posX+=movX;
			if (posX >= EJEX-1.0)
				posX -= EJEX;
			else if (posX <= 0)
				posX += EJEX-1.0;

			posY+=movY;		
			if (posY <= 0)
				posY += EJEY-1.0;
			else if (posY >= EJEY-1.0)
				posY -= EJEY;
		
			//control.eliminar(auxposX, auxposY, this);
			//control.anadir(posX, posY, this);

			//cout << "Pájaro id: " << this << " X = " << posX << " Y = " << posY << " Ang = " << angulo  << endl;
			//sleep(1);

			usleep(5 * 1000000);
		}
	};


public:	
	float auxposX, auxposY, auxAngulo;
	Pajaro(float posX, float posY, float angulo) : posX(posX), posY(posY), angulo(angulo) {};
	~Pajaro(){}; 
};


vector <Pajaro*> bandada;

void setup()
{
	glClearColor(0.0, 0.0, 0.0, 1.0); // Color de fondo (negro)
    gluOrtho2D(0, EJEX, 0, EJEY);
}


void display(){
	
	

    while(1)
    {
    	

	    glClear(GL_COLOR_BUFFER_BIT);
	    glColor3f(1, 0, 0);

	    //cout << bandada[0]->auxposX << " " << bandada[0]->auxposY;
	    for (int i = 0; i < CANTIDAD; ++i)
	    {
	    	glColor3f(1, 1, 1); // blanco
			glTranslatef(bandada[i]->auxposX, bandada[i]->auxposY, 0);
		    glRotatef(bandada[i]->auxAngulo, 0, 0, 1);
		    glBegin(GL_TRIANGLES);			
				glVertex3f(-2.5, -4.841225, 0); // Primer vertice
	            glVertex3f( 2.5, -4.841225, 0); // Segundo vertice
	            glVertex3f( 0,  4.841225, 0); // Tercer vertice     
		    glEnd();
			glRotatef(-bandada[i]->auxAngulo, 0, 0, 1);
			glTranslatef(-bandada[i]->auxposX, -bandada[i]->auxposY, 0);
		}
	    glFlush();
    }
}


void uMain::main() 
{
	glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(0, 0); // Posicion de la ventana en pixeles
    glutInitWindowSize(EJEX, EJEY); // Tamano de la ventana en pixeles
    glutCreateWindow("Aves"); // Titulo de la ventana
    glutDisplayFunc(display); // display es la funcion que
	
	srand (time(NULL));
	//Mapa *cielo = new Mapa();
	
	for(int i = 0; i < CANTIDAD; ++i)
		bandada.push_back(new Pajaro(rand() % EJEX, rand() % EJEY, rand() % 360));
	setup();
	glutMainLoop();
}