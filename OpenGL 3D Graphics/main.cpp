#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "GL\glew.h"
#include "GL\freeglut.h"

#include "shaderLoader.h"
#include "tekstura.h"


#include "glm/vec3.hpp" 
#include "glm/vec4.hpp" 
#include "glm/mat4x4.hpp" 
#include "glm/gtc/matrix_transform.hpp" 



int screen_width = 640;
int screen_height = 480;

GLint uniformTex0, uniformTex1; //do dwoch tekstur
int pozycjaMyszyX;
int pozycjaMyszyY;
int mbutton;

double kameraX = 40.0;
double kameraZ = 20.0;
double kameraD = -6;
double kameraPredkosc;
double kameraKat = -20;
double kameraPredkoscObrotu;
double poprzednie_kameraX;
double poprzednie_kameraZ;
double poprzednie_kameraD;

double blend = 0.5;
double blend2 = 0;


glm::mat4 MV;
glm::mat4 P;


//inicjacja dla elementu z pliku
#define TEAPOT_VER 12*3
#define TEAPOT_FACE 20*3

//wieloscian
GLuint elements3[TEAPOT_FACE] = {

};

float vertices3[TEAPOT_VER] = {

};


//podloga
float vertices[] = {
	-5,1,4,
	5,1,4,
	5,1,-8,
	-5,1,-8,

};

//kawa
float vertices2[] = {
	-2, 1.1, -2,
	2, 1.1, -2,
	2, 5.1, -2,
	-2, 5.1, -2,
};

//ebo
GLuint elements[] = {
	0,1,2,3

};
GLuint elements2[] = {
	3,2,1,0
};

//podloga
float textureCoords[] = {
	0,0,
	3,0,
	3,3,
	0,3, };

//kawa
float textureCoords2[] = {
	0,0,
	1,0,
	1,1,
	0,1,
};


//shaders
GLuint programID = 0, programID2 = 0;

unsigned int VBO, VBO2, VBO3, ebo, ebo2, ebo3, vtex, vtex2;
GLuint  tex_id0, tex_id1;
unsigned int VAO[3]; //elementy

double dx = -5;


void mysz(int button, int state, int x, int y)
{
	mbutton = button;
	switch (state)
	{
	case GLUT_UP:
		break;
	case GLUT_DOWN:
		pozycjaMyszyX = x;
		pozycjaMyszyY = y;
		poprzednie_kameraX = kameraX;
		poprzednie_kameraZ = kameraZ;
		poprzednie_kameraD = kameraD;
		break;

	}
}
void mysz_ruch(int x, int y)
{
	if (mbutton == GLUT_LEFT_BUTTON)
	{
		kameraX = poprzednie_kameraX - (pozycjaMyszyX - x) * 0.1;
		kameraZ = poprzednie_kameraZ - (pozycjaMyszyY - y) * 0.1;
	}
	if (mbutton == GLUT_RIGHT_BUTTON)
	{
		kameraD = poprzednie_kameraD + (pozycjaMyszyY - y) * 0.1;
	}

}
void rozmiar(int width, int height)
{
	screen_width = width;
	screen_height = height;

	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glViewport(0, 0, screen_width, screen_height);

	P = glm::perspective(glm::radians(60.0f), (GLfloat)screen_width / (GLfloat)screen_height, 1.0f, 1000.0f);

	glutPostRedisplay(); // Przerysowanie sceny
}
void idle()
{
	glutPostRedisplay();
}


//klawiatura
void klawisz(GLubyte key, int x, int y)
{
	switch (key) {

	case 27:    /* Esc - koniec */
		exit(1);
		break;

	case 'x':

		break;
	case 'c':

		break;


	case '1':

		break;
	case '2':

		break;
	}
}


//do animacji
GLfloat k = 0.1;
GLfloat ad = 0.0;
GLfloat alpha = 0.2; //dla wieloscianu
GLfloat rotation = 0.0; //do rotacji
GLfloat r = 5;
void timer(int value) {

	ad += k;
	rotation += r; //do rotacji
	if (ad > 4.5 || ad < -4.5)
	{
		k = -k;
		r = -r; //rotacja
	}
	//if (rotation > 4.0 || rotation < -4.0)	r = -r;

	glutTimerFunc(20, timer, 0);
}

//rysowanie
void rysuj(void)
{
	glClearColor(1.0, 1.0, 0.8, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Kasowanie ekranu

	//fragment
	glUseProgram(programID);

	//kamera
	GLuint MVP_id = glGetUniformLocation(programID, "MVP");
	MV = glm::mat4(1.0f);  //macierz jednostkowa
	MV = glm::translate(MV, glm::vec3(1, -1, kameraD + dx));
	MV = glm::rotate(MV, (float)glm::radians(kameraZ), glm::vec3(1, 0, 0));
	MV = glm::rotate(MV, (float)glm::radians(kameraX), glm::vec3(0, 1, 0));
	glm::mat4 MVP = P * MV;
	glUniformMatrix4fv(MVP_id, 1, GL_FALSE, &(MVP[0][0]));


	//podloga
	glBindVertexArray(VAO[0]);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glActiveTexture(GL_TEXTURE0);
	uniformTex0 = glGetUniformLocation(programID, "tex0");
	glUniform1i(uniformTex0, 0);
	glBindTexture(GL_TEXTURE_2D, tex_id0);
	glDrawElements(GL_QUADS, 4, GL_UNSIGNED_INT, 0);

	//kawa
	//blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDepthMask(GL_FALSE);

	glBindVertexArray(VAO[1]);
	glActiveTexture(GL_TEXTURE0);
	uniformTex1 = glGetUniformLocation(programID, "tex1");
	glUniform1i(uniformTex1, 1);
	glBindTexture(GL_TEXTURE_2D, tex_id1);

	glDrawElements(GL_QUADS, 4, GL_UNSIGNED_INT, 0);

	//wylaczenie
	glDisable(GL_BLEND);
	glDepthMask(GL_TRUE);



	//fragment2
	glUseProgram(programID2);
	glUniformMatrix4fv(MVP_id, 1, GL_FALSE, &(MVP[0][0]));

	//wiescian
	//blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDepthMask(GL_FALSE);

	MV = glm::translate(MV, glm::vec3(ad, 2.5, 0.5));
	MV = glm::rotate(MV, glm::radians(-rotation), glm::vec3(0, 0, 1));
	MV = glm::scale(MV, glm::vec3(1.5, 1.5, 1.5));
	MVP = P * MV;
	glUniformMatrix4fv(MVP_id, 1, GL_FALSE, &(MVP[0][0]));

	glBindVertexArray(VAO[2]);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glVertexAttrib4f(2, 0.0, 1.0, 0.0, alpha);
	glDrawElements(GL_TRIANGLES, 60, GL_UNSIGNED_INT, 0);

	//wylaczenie
	glDisable(GL_BLEND);
	glDepthMask(GL_TRUE);

	//krawedzie
	glBindVertexArray(VAO[2]);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glLineWidth(1);
	glVertexAttrib4f(2, 0.0, 1.0, 0.0, 1.0);
	glDrawElements(GL_TRIANGLES, 60, GL_UNSIGNED_INT, 0);

	glFlush();
	glutSwapBuffers();

}




int main(int argc, char** argv)
{
	//odczytywanie z pliku i przypisywanie do vertices oraz elements
	FILE* dane;
	dane = fopen("icosahedron.txt", "r");
	if (dane == NULL) printf("Prosze wkleic plik do miejsca uruchamania projektu\n");
	else
	{
		char a[99];
		int t;
		fscanf(dane, "%s", a);
		fscanf(dane, "%d", &t);
		for (int i = 0; i < TEAPOT_VER; i++)
		{
			if (feof(dane)) break;/*jeśli koniec pliku kończy pobieranie*/
			fscanf(dane, "%g,", &vertices3[i]);
			//printf("%f\n", vertices4[i]);
		}
		fscanf(dane, "%s", a);
		fscanf(dane, "%d", &t);
		for (int i = 0; i < TEAPOT_FACE; i++)
		{
			if (feof(dane)) break;/*jeśli koniec pliku kończy pobieranie*/
			fscanf(dane, "%d,", &elements3[i]);
			//printf("%d\n", elements4[i]);
		}
	}



	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(screen_width, screen_height);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Grupa 4 IAD");
	glewInit();
	glutDisplayFunc(rysuj);
	glutIdleFunc(idle);
	glutTimerFunc(20, timer, 0);
	glutReshapeFunc(rozmiar);
	glutKeyboardFunc(klawisz);
	glutMouseFunc(mysz);
	glutMotionFunc(mysz_ruch);


	glEnable(GL_DEPTH_TEST);

	//podloga
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements2), elements2, GL_STATIC_DRAW);
	//tekstura na podloge
	glGenBuffers(1, &vtex);
	glBindBuffer(GL_ARRAY_BUFFER, vtex);
	glBufferData(GL_ARRAY_BUFFER, sizeof(textureCoords), textureCoords, GL_STATIC_DRAW);


	//prostokat na kawe
	glGenBuffers(1, &VBO2);
	glBindBuffer(GL_ARRAY_BUFFER, VBO2);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);

	glGenBuffers(1, &ebo2);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo2);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);
	//kawa
	glGenBuffers(1, &vtex2);
	glBindBuffer(GL_ARRAY_BUFFER, vtex2);
	glBufferData(GL_ARRAY_BUFFER, sizeof(textureCoords2), textureCoords2, GL_STATIC_DRAW);

	//wieloscian
	glGenBuffers(1, &VBO3);
	glBindBuffer(GL_ARRAY_BUFFER, VBO3);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices3), vertices3, GL_STATIC_DRAW);

	glGenBuffers(1, &ebo3);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo3);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements3), elements3, GL_STATIC_DRAW);


	programID = loadShaders("vertex_shader.glsl", "fragment_shader.glsl");
	programID2 = loadShaders("vertex_shader.glsl", "fragment_shader2.glsl");


	tex_id0 = WczytajTeksture("sand.bmp");
	if (tex_id0 == -1)
	{
		MessageBox(NULL, "Nie znaleziono pliku z teksturą", "Problem", MB_OK | MB_ICONERROR);
		exit(0);
	}

	tex_id1 = WczytajTeksture("coffee.bmp");
	if (tex_id1 == -1)
	{
		MessageBox(NULL, "Nie znaleziono pliku z teksturą", "Problem", MB_OK | MB_ICONERROR);
		exit(0);
	}


	glGenVertexArrays(3, VAO);
	//0 to podloga z teksturą
	glBindVertexArray(VAO[0]);
	glBindBuffer(GL_ARRAY_BUFFER, vtex);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	//1 to prostokat na kawe
	glBindVertexArray(VAO[1]);
	glBindBuffer(GL_ARRAY_BUFFER, vtex2);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);


	glBindBuffer(GL_ARRAY_BUFFER, VBO2);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo2);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	//2 to wieloscian
	glBindVertexArray(VAO[2]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO3);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo3);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glutMainLoop();


	//usuwanie
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &ebo);
	glDeleteBuffers(1, &vtex);
	glDeleteBuffers(1, &VBO2);
	glDeleteBuffers(1, &ebo2);
	glDeleteBuffers(1, &vtex2);
	glDeleteBuffers(1, &VBO3);
	glDeleteBuffers(1, &ebo3);
	glDeleteBuffers(3, VAO);
	return(0);

}

