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
#include <uBarrier.h>

#define PI 3.14159265
#define EJEX 640
#define EJEY 640
#define CANTIDAD 3
#define DMAX 100
#define CMAX 50

using namespace std;
bool ready;


_Task Pajaro;
void cohesion(Pajaro* ave, vector <Pajaro*> *cumpleDMAX, vector <Pajaro*> *cumpleCMAX);

_Task Pajaro
{
	float posX, posY, angulo, velocidad, aceleracion;


protected:
	
	void main ()
	{
		//cielo->nacer(this);
		cout << "Creada id: " << this << " X = " << posX << " Y = " << posY << " Ang = " << angulo << " Vel = " << velocidad << endl;
		//cout << "rad " << ( angulo * PI / 180.0 ) << endl;
		//cielo->anadir(posX, posY, this);


		while(1)
		{

			// Separacion
			// Cohecion
			// Alineacion

			vector <Pajaro*> cumpleDMAX, cumpleCMAX;
			cohesion(this, &cumpleDMAX, &cumpleCMAX);


			//for (int i = 0; i < cumpleDMAX.size(); ++i)
			//	cout << this << " está cerca de " << cumpleDMAX[i] << endl;

			float movX = pow (sin ( angulo * PI / 180.0 ), 2);
			if (angulo < 360 && angulo > 180)
				movX *= -1.0;
			float movY = pow (cos ( angulo * PI / 180.0 ), 2);
			if (angulo > 90 && angulo < 270)
				movY *= -1.0;

			posX+=(movX*velocidad);
			if (posX >= EJEX)
				posX -= EJEX;
			else if (posX <= 0)
				posX += EJEX-1.0;

			posY+=(movY*velocidad);	
			if (posY <= 0)
				posY += EJEY-1.0;
			else if (posY >= EJEY)
				posY -= EJEY;

			//Programar toda la interaccion entre las aves

			cumpleDMAX.clear();
			cumpleCMAX.clear();
			ready=false;
			uBarrier x(CANTIDAD);

			auxposX = posX;
			auxposY = posY;
			auxAngulo = angulo;
			auxaceleracion = aceleracion;
			auxvelocidad = velocidad;

			uBarrier y(CANTIDAD);
			ready=true;
		}
	};


public:	
	float auxposX, auxposY, auxAngulo, auxaceleracion, auxvelocidad;
	Pajaro(float posX, float posY, float angulo, float velocidad) : posX(posX), posY(posY), angulo(angulo), velocidad(velocidad) {};
	~Pajaro(){}; 
};


vector <Pajaro*> bandada;

void cohesion(Pajaro* ave, vector <Pajaro*> *cumpleDMAX, vector <Pajaro*> *cumpleCMAX)
{
	//cout << "coqueo" << endl;
	float x1, x2, y1, y2, distancia;
	
	 
	for (int i = 0; i < bandada.size(); ++i)
	{
		if (bandada[i]==ave)
			continue;
		distancia = sqrt(pow(bandada[i]->auxposY - ave->auxposY, 2) +  pow(bandada[i]->auxposX - ave->auxposX, 2));
		//cout << "pico de " << ave << " " << distancia << endl;
		if (distancia <= DMAX)
		{
			cumpleDMAX->push_back(bandada[i]);
			//cout << cumpleDMAX << endl;
		}
		if (distancia <= CMAX)
		{
			cumpleCMAX->push_back(bandada[i]);
			//cout << "coqueoC" << endl;
		}
	}
}


void setup()
{
	glClearColor(0.0, 0.0, 0.0, 1.0); // Color de fondo (negro)
    gluOrtho2D(0, EJEX, 0, EJEY);
}

void draw (float auxposX, float auxposY, float auxAngulo)
{
	glColor3f(1, 1, 1); // blanco
	glTranslatef(auxposX, auxposY, 0);
	glRotatef(-auxAngulo, 0, 0, 1);
	glBegin(GL_TRIANGLES);			
		glVertex3f(-2.5, -4.841225, 0); // Primer vertice
	    glVertex3f( 2.5, -4.841225, 0); // Segundo vertice
	    glVertex3f( 0,  4.841225, 0); // Tercer vertice     
	glEnd();
	glRotatef(auxAngulo, 0, 0, 1);
	glTranslatef(-auxposX, -auxposY, 0);
}


void display(){
    while(1)
    {
    	if (ready)
    	{
		    glClear(GL_COLOR_BUFFER_BIT);
		    //cout << bandada[0]->auxposX << " " << bandada[0]->auxposY;
		    for (int i = 0; i < CANTIDAD; ++i)
			    draw(bandada[i]->auxposX, bandada[i]->auxposY, bandada[i]->auxAngulo);
		    glFlush();
		}
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
		bandada.push_back(new Pajaro(rand() % EJEX, rand() % EJEY, rand() % 360, ((rand() % 100)+1)/10000.0 ));
	setup();
	glutMainLoop();
}