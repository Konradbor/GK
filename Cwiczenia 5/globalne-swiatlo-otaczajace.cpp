// opengl_globalne_swiatlo_otaczajace.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


/*
(c) Janusz Ganczarski
http://www.januszg.hg.pl
JanuszG@enter.net.pl
*/

#include <GL/glut.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "colors.h"

// stałe do obsługi menu podręcznego

enum
{
	FULL_WINDOW,    // aspekt obrazu - całe okno
	ASPECT_1_1,     // aspekt obrazu 1:1
	EXIT            // wyjście
};

// aspekt obrazu

int aspect = FULL_WINDOW;

// rozmiary bryły obcinania

const GLdouble left = -2.0;
const GLdouble right = 2.0;
const GLdouble bottom = -2.0;
const GLdouble top = 2.0;
const GLdouble near_ = 3.0;
const GLdouble far_ = 7.0;

// kąty obrotu

GLfloat rotatex = 0.0;
GLfloat rotatey = 0.0;

// wskaŸnik naciśnięcia lewego przycisku myszki

int button_state = GLUT_UP;

// poło¿enie kursora myszki

int button_x, button_y;

// składowe globalnego światła otaczającego
// wartośæ początkowa odpowiada wartości domyślnej
// składowych tego światła

GLfloat ambient_light[4] =
{
	0.2,0.2,0.2,1.0
};

// funkcja rysująca napis w wybranym miejscu

void DrawString(GLfloat x, GLfloat y, char *string)
{
	// poło¿enie napisu
	glRasterPos2f(x, y);

	// wyświetlenie napisu
	int len = strlen(string);
	for (int i = 0; i < len; i++)
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, string[i]);
}

// funkcja generująca scenę 3D

void Display()
{
	// kolor tła - zawartośæ bufora koloru
	glClearColor(1.0, 1.0, 1.0, 1.0);

	// czyszczenie bufora koloru i bufora głębokości
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// wybór macierzy modelowania
	glMatrixMode(GL_MODELVIEW);

	// macierz modelowania = macierz jednostkowa
	glLoadIdentity();

	// przesunięcie układu współrzędnych sześcianu do środka bryły odcinania
	glTranslatef(0, 0, -(near_ + far_) / 2);

	// obroty sześcianu
	glRotatef(rotatex, 1.0, 0, 0);
	glRotatef(rotatey, 0, 1.0, 0);

	// niewielkie powiększenie sześcianu
	glScalef(1.15, 1.15, 1.15);

	// włączenie oświetlenia
	glEnable(GL_LIGHTING);

	// parametry globalnego światła otaczającego
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient_light);

	// włączenie obsługi właściwości materiałów
	glEnable(GL_COLOR_MATERIAL);

	// właściwości materiału określone przez kolor wierzchołków
	glColorMaterial(GL_FRONT, GL_AMBIENT);

	// włączenie testu bufora głębokości
	glEnable(GL_DEPTH_TEST);

	// rysowanie sześcianu - 12 trójkątów
	glBegin(GL_TRIANGLES);
	glColor3fv(Red);
	glVertex3f(-1.0, -1.0, 1.0);
	glVertex3f(1.0, -1.0, 1.0);
	glVertex3f(1.0, 1.0, 1.0);
	glVertex3f(-1.0, -1.0, 1.0);
	glVertex3f(1.0, 1.0, 1.0);
	glVertex3f(-1.0, 1.0, 1.0);

	glColor3fv(Magenta);
	glVertex3f(-1.0, 1.0, 1.0);
	glVertex3f(1.0, 1.0, 1.0);
	glVertex3f(-1.0, 1.0, -1.0);
	glVertex3f(-1.0, 1.0, -1.0);
	glVertex3f(1.0, 1.0, 1.0);
	glVertex3f(1.0, 1.0, -1.0);

	glColor3fv(Cyan);
	glVertex3f(1.0, 1.0, -1.0);
	glVertex3f(1.0, 1.0, 1.0);
	glVertex3f(1.0, -1.0, 1.0);
	glVertex3f(1.0, 1.0, -1.0);
	glVertex3f(1.0, -1.0, 1.0);
	glVertex3f(1.0, -1.0, -1.0);

	glColor3fv(Lime);
	glVertex3f(1.0, -1.0, -1.0);
	glVertex3f(1.0, -1.0, 1.0);
	glVertex3f(-1.0, -1.0, -1.0);
	glVertex3f(-1.0, -1.0, -1.0);
	glVertex3f(1.0, -1.0, 1.0);
	glVertex3f(-1.0, -1.0, 1.0);

	glColor3fv(Blue);
	glVertex3f(-1.0, -1.0, -1.0);
	glVertex3f(-1.0, -1.0, 1.0);
	glVertex3f(-1.0, 1.0, -1.0);
	glVertex3f(-1.0, 1.0, -1.0);
	glVertex3f(-1.0, -1.0, 1.0);
	glVertex3f(-1.0, 1.0, 1.0);

	glColor3fv(Yellow);
	glVertex3f(-1.0, -1.0, -1.0);
	glVertex3f(-1.0, 1.0, -1.0);
	glVertex3f(1.0, 1.0, -1.0);
	glVertex3f(1.0, -1.0, -1.0);
	glVertex3f(-1.0, -1.0, -1.0);
	glVertex3f(1.0, 1.0, -1.0);

	// koniec definicji sześcianu
	glEnd();

	// wyłączenie oświetlenia
	glDisable(GL_LIGHTING);

	// wyłączenie obsługi właściwości materiałów
	glDisable(GL_COLOR_MATERIAL);

	// wyświetlenie składowych globalnego światła otaczającego
	char string[100];
	GLfloat rgba[4];
	glColor3fv(Black);

	// pobranie wartości składowych światła otaczającego
	// (oczywiście wartości te odpowiadają tablicy ambient_light)
	glGetFloatv(GL_LIGHT_MODEL_AMBIENT, rgba);
	sprintf(string, "AMBIENT: R=%f G=%f B=%f A=%f", rgba[0], rgba[1], rgba[2], rgba[3]);

	// trzeba odpowiednio przekształciæ układ współrzędnych
	// aby napis znajdował się na samej "górze" bryły obcinania
	glLoadIdentity();
	glTranslatef(0, 0, -near_);

	// narysowanie napisu
	DrawString(left, bottom, string);

	// skierowanie poleceñ do wykonania
	glFlush();

	// zamiana buforów koloru
	glutSwapBuffers();
}

// zmiana wielkości okna

void Reshape(int width, int height)
{
	// obszar renderingu - całe okno
	glViewport(0, 0, width, height);

	// wybór macierzy rzutowania
	glMatrixMode(GL_PROJECTION);

	// macierz rzutowania = macierz jednostkowa
	glLoadIdentity();

	// parametry bryły obcinania
	if (aspect == ASPECT_1_1)
	{
		// wysokośæ okna większa od wysokości okna
		if (width < height && width > 0)
			glFrustum(left, right, bottom*height / width, top*height / width, near_, far_);
		else

			// szerokośæ okna większa lub równa wysokości okna
			if (width >= height && height > 0)
				glFrustum(left*width / height, right*width / height, bottom, top, near_, far_);
	}
	else
		glFrustum(left, right, bottom, top, near_, far_);

	// generowanie sceny 3D
	Display();
}

// obsługa klawiatury

void Keyboard(unsigned char key, int x, int y)
{
	// zmiana wartości składowej R
	if (key == 'R' && ambient_light[0] < 1.0)
		ambient_light[0] += 0.05;
	else
		if (key == 'r' && ambient_light[0] > -1.0)
			ambient_light[0] -= 0.05;

	// zmiana wartości składowej G
	if (key == 'G' && ambient_light[1] < 1.0)
		ambient_light[1] += 0.05;
	else
		if (key == 'g' && ambient_light[1] > -1.0)
			ambient_light[1] -= 0.05;

	// zmiana wartości składowej B
	if (key == 'B' && ambient_light[2] < 1.0)
		ambient_light[2] += 0.05;
	else
		if (key == 'b' && ambient_light[2] > -1.0)
			ambient_light[2] -= 0.05;

	// narysowanie sceny
	Display();
}

// obsługa klawiszy funkcyjnych i klawiszy kursora

void SpecialKeys(int key, int x, int y)
{
	switch (key)
	{
		// kursor w lewo
	case GLUT_KEY_LEFT:
		rotatey -= 1;
		break;

		// kursor w górę
	case GLUT_KEY_UP:
		rotatex -= 1;
		break;

		// kursor w prawo
	case GLUT_KEY_RIGHT:
		rotatey += 1;
		break;

		// kursor w dół
	case GLUT_KEY_DOWN:
		rotatex += 1;
		break;
	}

	// odrysowanie okna
	Reshape(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
}

// obsługa przycisków myszki

void MouseButton(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON)
	{
		// zapamiętanie stanu lewego przycisku myszki
		button_state = state;

		// zapamiętanie poło¿enia kursora myszki
		if (state == GLUT_DOWN)
		{
			button_x = x;
			button_y = y;
		}
	}
}

// obsługa ruchu kursora myszki

void MouseMotion(int x, int y)
{
	if (button_state == GLUT_DOWN)
	{
		rotatey += 30 * (right - left) / glutGet(GLUT_WINDOW_WIDTH) * (x - button_x);
		button_x = x;
		rotatex -= 30 * (top - bottom) / glutGet(GLUT_WINDOW_HEIGHT) * (button_y - y);
		button_y = y;
		glutPostRedisplay();
	}
}

// obsługa menu podręcznego

void Menu(int value)
{
	switch (value)
	{
		// obszar renderingu - całe okno
	case FULL_WINDOW:
		aspect = FULL_WINDOW;
		Reshape(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
		break;

		// obszar renderingu - aspekt 1:1
	case ASPECT_1_1:
		aspect = ASPECT_1_1;
		Reshape(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
		break;

		// wyjście
	case EXIT:
		exit(0);
	}
}

int main(int argc, char *argv[])
{
	// inicjalizacja biblioteki GLUT
	glutInit(&argc, argv);

	// inicjalizacja bufora ramki
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	// rozmiary głównego okna programu
	glutInitWindowSize(500, 500);

	// utworzenie głównego okna programu
#ifdef WIN32

	glutCreateWindow("Globalne światło otaczające");
#else

	glutCreateWindow("Globalne swiatlo otaczajace");
#endif

	// dołączenie funkcji generującej scenę 3D
	glutDisplayFunc(Display);

	// dołączenie funkcji wywoływanej przy zmianie rozmiaru okna
	glutReshapeFunc(Reshape);

	// dołączenie funkcji obsługi klawiatury
	glutKeyboardFunc(Keyboard);

	// dołączenie funkcji obsługi klawiszy funkcyjnych i klawiszy kursora
	glutSpecialFunc(SpecialKeys);

	// obsługa przycisków myszki
	glutMouseFunc(MouseButton);

	// obsługa ruchu kursora myszki
	glutMotionFunc(MouseMotion);

	// utworzenie menu podręcznego
	glutCreateMenu(Menu);

	// utworzenie podmenu - aspekt obrazu
	int MenuAspect = glutCreateMenu(Menu);
#ifdef WIN32

	glutAddMenuEntry("Aspekt obrazu - całe okno", FULL_WINDOW);
#else

	glutAddMenuEntry("Aspekt obrazu - cale okno", FULL_WINDOW);
#endif

	glutAddMenuEntry("Aspekt obrazu 1:1", ASPECT_1_1);

	// menu główne
	glutCreateMenu(Menu);
	glutAddSubMenu("Aspekt obrazu", MenuAspect);
#ifdef WIN32

	glutAddMenuEntry("Wyjście", EXIT);
#else

	glutAddMenuEntry("Wyjscie", EXIT);
#endif

	// określenie przycisku myszki obsługującej menu podręczne
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	// wprowadzenie programu do obsługi pętli komunikatów
	glutMainLoop();
	return 0;
}
