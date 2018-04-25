// OpenGL_POINTS_ConsoleApplication.cpp : Defines the entry point for the console application.
//

//#include "stdafx.h"
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <math.h>
// Definiujemy stał o wartoci liczby PI
#define GL_PI 3.1415f
// Wielko obrotów
static GLfloat xRot = 0.0f;
static GLfloat yRot = 0.0f;
static GLfloat zRot = 0.0f;
// Wywoływana w celu przerysowania sceny
void RenderScene(void)
{
	GLfloat x, y, z, angle; // Zmienne przechowujące współrzędne i kąty
							// Wyczyszczenie okna aktualnym kolorem czyszczącym
	glClear(GL_COLOR_BUFFER_BIT);
	// Zapisanie stanu macierzy i wykonanie obrotu
	glPushMatrix();
	glRotatef(xRot, 1.0f, 0.0f, 0.0f);
	glRotatef(yRot, 0.0f, 1.0f, 0.0f);
	glRotatef(zRot, 0.0f, 0.0f, 1.0f);
	// Wywoła tylko raz, przed rysowaniem wszystkich punktów
	glBegin(GL_POINTS);
	y = -200.0f;
	float obroty = 15.0f;
	for (angle = 0.0f; angle <= (2.0f*GL_PI)*obroty; angle += 0.1f)
	{
		x = 50.0f*sin(angle);
		z = 50.0f*cos(angle);
		// Określenie punktu i przesunięcie współrzędnej Z
		glVertex3f(x, y, z);
		y += 0.5f;
	}
	// Zakończenie rysowania punktów
	glEnd();
	// Odtworzenie macierzy przekształce
	glPopMatrix();
	// Wykonanie poleceń rysowania
	glutSwapBuffers();
}
// Ta funkcja wykonuje wszystkie konieczne inicjalizacje kontekstu renderowania
void SetupRC()
{
	// Czarne tło
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	// Będziemy rysować kolorem zielonym
	glColor3f(0.0f, 1.0f, 0.0f);
}
void SpecialKeys(int key, int x, int y)
{
	if (key == GLUT_KEY_UP)
		xRot -= 5.0f;
	if (key == GLUT_KEY_DOWN)
		xRot += 5.0f;
	if (key == GLUT_KEY_LEFT)
		zRot -= 5.0f;
	if (key == GLUT_KEY_RIGHT)
		zRot += 5.0f;
	if (key > 356.0f)
		xRot = 0.0f;
	if (key < -1.0f)
		xRot = 355.0f;
	if (key > 356.0f)
		zRot = 0.0f;
	if (key < -1.0f)
		zRot = 355.0f;
	// Odświeżenie zawartości okna
	glutPostRedisplay();
}
void ChangeSize(int w, int h)
{
	GLfloat nRange = 300.0f;
	// Zabezpieczenie przed dzieleniem przez zero
	if (h == 0)
		h = 1;
	// Ustalenie wymiarów widoku na zgodnych z wymiarami okna
	glViewport(0, 0, w, h);
	// Ponowne ustawienie stosu macierzy rzutowania
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	// Utworzenie przestrzeni ograniczającej (lewo, prawo, dół, góra, blisko, daleko)
	if (w <= h)
		glOrtho(-nRange, nRange, -nRange*h / w, nRange*h / w, -nRange, nRange);
	else
		glOrtho(-nRange*w / h, nRange*w / h, -nRange, nRange, -nRange, nRange);
	// Ponowne ustawienie stosu macierzy rzutowania
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void Menu(int value)
{
	switch (value)
	{
		//
	case 1:
		glColor3f(0.0f, 1.0f, 0.0f);
		RenderScene();
		break;

		//
	case 2:
		glColor3f(0.0f, 0.0f, 1.0f);
		RenderScene();
		break;

		//
	case 3:
		glColor3f(0.647f, 0.165f, 0.165f);
		RenderScene();
		break;

		//
	case 4:
		glColor3f(1.000f, 0.078f, 0.576f);
		RenderScene();
		break;
	}
}


int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(400, 600);
	glutCreateWindow("Points Example");
	glutReshapeFunc(ChangeSize);
	glutSpecialFunc(SpecialKeys);
	glutDisplayFunc(RenderScene);
	SetupRC();
	int MenuPrimitive = glutCreateMenu(Menu);
	glutAddMenuEntry("Zielony", 1);
	glutAddMenuEntry("Niebieski", 2);
	glutAddMenuEntry("Brazowy", 3);
	glutAddMenuEntry("Rozowy", 4);

	// określenie przycisku myszki obsługującego menu podręczne
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	glutMainLoop();
	return 0;
}