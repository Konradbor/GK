//
// OpenGL_Animacja_Prostokat_ConsoleApplication1.cpp : Defines the entry point for the console application.
//
// Bounce.c
// Demonstrates a simple animated rectangle program with GLUT
// OpenGL SuperBible, 2nd Edition
// Richard S. Wright Jr.

//#include "stdafx.h"
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <cmath>
#include <iostream>

using namespace std;

// Pocztkowy rozmiar i pozycja prostokta
GLfloat x = 100.0f;
GLfloat y = 150.0f;
GLsizei rsize = 50;

// Rozmiar kroku (liczba pikseli) w osi x i y
GLfloat xstep = 1.0f;
GLfloat ystep = 1.0f;
// Dane zmieniajcych się rozmiarów okna
GLfloat windowWidth;
GLfloat windowHeight;
///////////////////////////////////////////////////////////
// Wywoływana w celu przerysowania sceny
void RenderScene(void) {
	// Wyczyszczenie okna aktualnym kolorem czyszczącym
	glClear(GL_COLOR_BUFFER_BIT);

	// Aktualny kolor rysujący - czerwony
	//    R    G    B
	glColor3f(1.0f, 0.0f, 0.0f);

	// Narysowanie prostokąta wypełnionego aktualnym kolorem
	//glRectf(x1, y1, x1 + rsize, y1 + rsize);
	glBegin(GL_POLYGON);
	for (int i = 1; i <= 15; i++)
	{
		GLfloat _x = x + sin(i / 14.0 * 2 * M_PI) * 40;
		GLfloat _y = y + cos(i / 14.0 * 2 * M_PI) * 40;
		//cout << "x:" <<  _x << endl;
		//cout << "y:" << _y << endl;
		glVertex2f(_x,_y);
	}
	glEnd();
	
	

	// Wysłanie poleceń do wykonania - !!! dla animacji to jest inne polecenie
	glutSwapBuffers();
}
///////////////////////////////////////////////////////////
// Wywoływana przez bibliotek GLUT w czasie, gdy okno nie
// jest przesuwane ani nie jest zmieniana jego wielkość
void TimerFunction(int value) {
	// Odwrócenie kierunku, jeżeli osiągnięto lewą lub prawą krawędź
	if (x > windowWidth - rsize || x < 0)
		xstep = -xstep;

	// Odwrócenie kierunku, jeżeli osiągnięto dolną lub górną krawędź
	if (y > windowHeight - rsize || y < 0)
		ystep = -ystep;


	// Kontrola obramowania. Wykonywana jest na wypadek, gdyby okno     
	// zmniejszyło swoj wielkość w czasie, gdy kwadrat odbijał się od     
	// krawędzi, co mogłoby spowodować, że znalazł by się poza      
	// przestrzenią ograniczajcą.     
	if (x > windowWidth - rsize)
		x = windowWidth - rsize - 1;

	if (y > windowHeight - rsize)
		y = windowHeight - rsize - 1;

	// Wykonanie przesunięcia kwadratu
	x += xstep;
	y += ystep;

	// Ponowne rysowanie sceny z nowymi współrzędnymi  
	glutPostRedisplay();
	glutTimerFunc(1, TimerFunction, 1);
}
///////////////////////////////////////////////////////////
// Konfigurowanie stanu renderowania
void SetupRC(void) {
	// Ustalenie niebieskiego koloru czyszczącego     
	glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
}
///////////////////////////////////////////////////////////
// Wywoływana przez bibliotek GLUT przy każdej zmianie wielkości okna
void ChangeSize(GLsizei w, GLsizei h) {
	// Zabezpieczenie przed dzieleniem przez zero
	if (h == 0)
		h = 1;

	// Ustalenie wielkości widoku zgodnego z rozmiarami okna
	glViewport(0, 0, w, h);

	// Ustalenie układu współrzędnych
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Keep the square square, this time, save calculated
	// width and height for later use
	if (w <= h)
	{
		windowHeight = 250.0f*h / w;
		windowWidth = 250.0f;
	}
	else
	{
		windowWidth = 250.0f*w / h;
		windowHeight = 250.0f;
	}

	// Ustanowienie przestrzeni ograniczającej (lewo, prawo, dół, góra, blisko, daleko)
	glOrtho(0.0f, windowWidth, 0.0f, windowHeight, 1.0f, -1.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
///////////////////////////////////////////////////////////
// Główny punkt wejścia programu
int main(int argc, char* argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Bounce");
	glutDisplayFunc(RenderScene);
	glutReshapeFunc(ChangeSize);
	glutTimerFunc(1, TimerFunction, 1);
	SetupRC();
	glutMainLoop();
}
