#include <cstdlib>
#include <iostream>
#include <windows.h>
#include <stdio.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <math.h>

GLuint texture[35];

GLint slices = 35;
GLint stacks = 35;

using namespace std;
static float ypos = 0, zpos = 0, xpos = 0, a = -9, b = -5, c = -30, kulkas1 = 0, kulkas2 = 0, jKiri = 0, jKanan = 0, lKanan = 0, lKiri = 0, oven = 0, pintu = 0;
int z = 0;

void init() {
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glShadeModel(GL_SMOOTH);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}

//fungsi kotak kosong, belum diisi koordinat. diisi di display()
void kotak(float x1, float y1, float z1, float x2, float y2, float z2)
{
	//depan
	glTexCoord2f(0.0, 0.0);
	glVertex3f(x1, y1, z1);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(x2, y1, z1);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(x2, y2, z1);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(x1, y2, z1);
	//atas
	glTexCoord2f(0.0, 0.0);
	glVertex3f(x1, y2, z1);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(x2, y2, z1);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(x2, y2, z2);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(x1, y2, z2);
	//belakang
	glTexCoord2f(0.0, 0.0);
	glVertex3f(x1, y2, z2);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(x2, y2, z2);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(x2, y1, z2);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(x1, y1, z2);
	//bawah
	glTexCoord2f(0.0, 0.0);
	glVertex3f(x1, y1, z2);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(x2, y1, z2);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(x2, y1, z1);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(x1, y1, z1);
	//samping kiri
	glTexCoord2f(0.0, 0.0);
	glVertex3f(x1, y1, z1);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(x1, y2, z1);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(x1, y2, z2);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(x1, y1, z2);
	//samping kanan
	glTexCoord2f(0.0, 0.0);
	glVertex3f(x2, y1, z1);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(x2, y2, z1);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(x2, y2, z2);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(x2, y1, z2);
}


void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
		//putar arah jarum jam (menambah derajat putaran)
	case 'z':
		ypos = ypos + 5;
		if (ypos > 360) ypos = 0;
		glutPostRedisplay();
		break;
		//putar berlawanan arah jarum jam (mengurangi derajat putaran)
	case 'x':
		ypos = ypos - 5;
		if (ypos > 360) ypos = 0;
		glutPostRedisplay();
		break;
		//vertikal bawah (menambah koordinat y)
	case 's':
		b = b + 1;
		glutPostRedisplay();
		break;
		//vertikal atas (mengurangi koordinat y)
	case 'w':
		b = b - 1;
		glutPostRedisplay();
		break;
		//horisontal kiri (mengurangi koordinat x)
	case 'a':
		a = a + 1;
		glutPostRedisplay();
		break;
		//horisontal kanan (menambah koordinat x)
	case 'd':
		a = a - 1;
		glutPostRedisplay();
		break;
		//memperbesar objek (menambah koordinat z)
	case 'q':
		c = c + 1;
		glutPostRedisplay();
		break;
		//memperkecil abjek(mengurangi koordinat z)
	case 'e':
		c = c - 1;
		glutPostRedisplay();
		break;
		//putar arah jarum jam (menambah derajat putaran)
	case 'c':
		xpos = xpos + 5;
		if (xpos > 360) xpos = 0;
		glutPostRedisplay();
		break;
		//putar berlawanan arah jarum jam (mengurangi derajat putaran)
	case 'v':
		xpos = xpos - 5;
		if (xpos > 360) xpos = 0;
		glutPostRedisplay();

	}
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glEnable(GL_DEPTH_TEST);
	//perpindahan
	glTranslatef(a, b, c);
	//putaran
	glRotatef(xpos, 1, 0, 0);
	glRotatef(ypos, 0, 1, 0);
	glRotatef(zpos, 0, 0, 1);

		//lantai
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, texture[1]);
	glBegin(GL_QUADS);
	glColor3f(0.3f, 0.3f, 0.3f);
	kotak(0, 0, 18, 25, 0.5, 0);
	glEnd();
	glPopMatrix();

	//dinding kiri
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, texture[2]);
	glBegin(GL_QUADS);
	glColor3f(0.0f, 0.0f, 1.0f);
	kotak(0, 0.5, 18, 0.5, 10, 0);
	glEnd();
	glPopMatrix();

	//dinding belakang
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, texture[2]);
	glBegin(GL_QUADS);
	glColor3f(0.0f, 0.0f, 1.0f);
	kotak(6, 0.5, 0.5, 25, 10, 0.0);
	glEnd();
	glPopMatrix();

	//saklar
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, texture[10]);
	glBegin(GL_QUADS);
	glColor3f(1.1f, 1.0f, 1.0f);
	kotak(6.5, 6.5, 0.6, 7.5, 7.5, 0.5);
	glColor3f(0.1f, 0.0f, 0.0f);
	kotak(6.65, 6.7, 0.65, 6.92, 7.3, 0.6);
	kotak(7.08, 6.7, 0.65, 7.35, 7.3, 0.6);
	glEnd();
	glPopMatrix();
	//pintu
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, texture[3]);
	glBegin(GL_QUADS);
	glColor3f(0.1f, 0.0f, 0.0f);
	kotak(0.5, 0.5, 0.5, 6, 10, 0);
	glEnd();
	glPopMatrix();
	//gagang pintu
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glBegin(GL_QUADS);
	//gagang pintu
	glColor3f(1.0f, 1.0f, 1.0f);
	kotak(5.2, 5.8, 0.7, 5.5, 6, 0.5);
	kotak(4.5, 5.8, 0.9, 5.6, 6, 0.7);
	//alas gagang
	kotak(5.1, 6.5, 0.55, 5.7, 5, 0.5);
	glColor3f(0.0f, 0.0f, 0.0f);
	kotak(5.35, 5.2, 0.56, 5.45, 5.5, 0.55);
	glEnd();
	glPopMatrix();
	//gagang pintu belakang 
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glBegin(GL_QUADS);
	//gagang pintu
	glColor3f(1.0f, 1.0f, 1.0f);
	kotak(5.2, 5.8, 0, 5.5, 6, -0.2);
	kotak(4.5, 5.8, -0.2, 5.6, 6, -0.4);
	//alas gagang
	kotak(5.1, 6.5, 0, 5.7, 5, -0.05);
	glColor3f(0.0f, 0.0f, 0.0f);
	kotak(5.35, 5.2, -0.05, 5.45, 5.5, -0.06);
	glEnd();
	glPopMatrix();

	//meja
	//atas
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, texture[2]);
	glBegin(GL_QUADS);
	glColor3f(1.1f, 1.0f, 1.0f);
	kotak(21, 3.5, 16, 24.8, 3.8, 9.5);
	//kaki kanan belakang
	kotak(24.3, 0.5, 15.9, 24.6, 3.6, 15.6);
	//kaki kiri belakang
	kotak(24.3, 0.5, 9.9, 24.6, 3.6, 9.6);
	//kaki kiri depan
	kotak(21.1, 0.5, 9.9, 21.4, 3.6, 9.6);
	//kaki kanan depan
	kotak(21.1, 0.5, 15.9, 21.4, 3.6, 15.6);
	//belakang bawah
	kotak(24.4, 1, 15.6, 24.6, 1.6, 9.9);
	//kanan bawah
	kotak(21.4, 1, 15.9, 24.3, 1.6, 15.7);
	//kiri bawah
	kotak(21.4, 1, 9.8, 24.3, 1.6, 9.9);
	glEnd();
	glPopMatrix();

	//pc
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, texture[2]);
	glBegin(GL_QUADS);
	glColor3f(0.0f, 0.0f, 0.0f);
	//cpu
	kotak(21.5, 3.8, 11.8, 23.5, 6, 10.8);
	//Monitor lcd
	kotak(23.3, 4.1, 15.5, 23.5, 6.4, 12.2);
	kotak(23.5, 4.3, 15.3, 23.6, 6.2, 12.4);
	kotak(23.6, 3.8, 14, 23.8, 6, 13.5);
	kotak(23.4, 3.8, 14.3, 23.9, 4, 13.2);
	//keyboard
	kotak(21.8, 3.8, 12.3, 23, 4, 15.2);
	glEnd();
	glPopMatrix();
	//layar lcd
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, texture[8]);
	glBegin(GL_QUADS);
	glColor3f(1.1f, 1.0f, 1.0f);
	kotak(23.29, 4.3, 15.3, 23.29, 6.2, 12.4);
	glEnd();
	glPopMatrix();
	//cpu
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, texture[4]);
	glBegin(GL_QUADS);
	glColor3f(0.3f, 0.3f, 0.3f);
	kotak(21.49, 3.8, 11.8, 21.5, 6, 10.8);
	glEnd();
	glPopMatrix();


	//kursi
	//alas
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, texture[3]);
	glBegin(GL_QUADS);
	glColor3f(0.1f, 0.0f, 0.0f);
	kotak(18, 2.2, 15.5, 20.8, 2.5, 12.8);
	//kiri depan
	kotak(20.5, 0.5, 15.5, 20.8, 2.5, 15.2);
	//kanan depan
	kotak(20.5, 0.5, 13.1, 20.8, 2.5, 12.8);
	//kanan belakang
	kotak(18, 0.5, 13.1, 18.3, 5.2, 12.8);
	//kiri belakang
	kotak(18, 0.5, 15.5, 18.3, 5.2, 15.2);
	//senderan 
	kotak(18, 3.8, 15.5, 18.2, 4.9, 12.8);
	glEnd();
	glPopMatrix();


	//lukisan
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, texture[9]);
	glBegin(GL_QUADS);
	glColor3f(1.0f, 1.0f, 1.0f);
	kotak(0.6, 6.6, 15.5, 0.61, 8.8, 8.9);
	glColor3f(0.0f, 0.0f, 0.0f);
	kotak(0.5, 6.4, 15.7, 0.6, 9, 8.7);
	glEnd();
	glPopMatrix();

	//lemari kecil
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, texture[2]);
	glBegin(GL_QUADS);
	glColor3f(1.2f, 1.2f, 1.2f);
	kotak(0.5, 0.8, 8.5, 4, 4.5, 4.7);
	//kaki kiri
	kotak(0.5, 0.5, 8.5, 4.3, 4.9, 8.3);
	//kaki kanan
	kotak(0.5, 0.5, 4.5, 4.3, 4.9, 4.7);
	//pegangan
	kotak(4.2, 2.1, 6.9, 4.3, 2.3, 6.2);
	kotak(4.2, 3.9, 6.9, 4.3, 4.1, 6.2);
	glEnd();
	glPopMatrix();
	//lacinya
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, texture[3]);
	glBegin(GL_QUADS);
	glColor3f(0.3f, 0.1f, 0.1f);
	kotak(4, 1, 8.2, 4.2, 2.5, 4.9);
	kotak(4, 2.7, 8.2, 4.2, 4.3, 4.9);
	glEnd();
	glPopMatrix();

	//lemari pakaian
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, texture[2]);
	glBegin(GL_QUADS);
	glColor3f(1.1f, 1.0f, 1.0f);
	kotak(16, 0.6, 3.5, 23.8, 8.5, 0.5);
	//kanan
	kotak(23.8, 0.5, 3.7, 24, 8.7, 0.5);
	//kiri
	kotak(15.8, 0.5, 3.7, 16, 8.7, 0.5);
	//gagang pintu kiri
	glColor3f(1.1f, 1.0f, 1.0f);
	kotak(19.3, 4.5, 3.9, 19.5, 5.7, 3.7);
	//gagang pintu kanan
	kotak(20.3, 4.5, 3.9, 20.5, 5.7, 3.7);
	glEnd();
	glPopMatrix();
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, texture[3]);
	glBegin(GL_QUADS);
	glColor3f(0.2f, 0.1f, 0.1f);
	//pintu kiri
	kotak(16.2, 0.9, 3.7, 19.7, 8.3, 3.5);
	//pintu kanan
	kotak(20.1, 0.9, 3.7, 23.6, 8.3, 3.5);
	glEnd();
	glPopMatrix();

	//lukisan 
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, texture[5]);
	glBegin(GL_QUADS);
	glColor3f(0.0f, 0.0f, 0.0f);
	kotak(9.2, 2.8, 0.55, 13.2, 8.2, 0.5);
	glColor3f(1.1f, 1.0f, 1.0f);
	kotak(9.4, 3, 0.6, 13, 8, 0.55);
	glEnd();
	glPopMatrix();

	//ac
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, texture[10]);
	glBegin(GL_QUADS);
	glColor3f(1.1f, 1.1f, 1.1f);
	kotak(0.55, 8.45, 8.2, 1.2, 9.7, 4.5);
	glColor3f(0.0f, 0.0f, 0.0f);
	kotak(1.2, 8.5, 8.2, 1.25, 8.45, 4.5);
	kotak(1.2, 8.6, 8.1, 1.25, 8.62, 4.6);
	kotak(1.2, 9.58, 8.1, 1.25, 9.6, 7);
	kotak(1.2, 9.52, 8.2, 1.25, 9.54, 6.5);
	kotak(0.55, 8.39, 8.1, 1.15, 8.4, 4.6);
	glEnd();
	glPopMatrix();

	glFlush();
	glutSwapBuffers();

}

void reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, 1.0 * (GLfloat)w / (GLfloat)h, 1.0, 40.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.0, 0.0, 0.0);
	gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(1024, 600);
	glutInitWindowPosition(20, 75);
	glutCreateWindow("Hasil");
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutMainLoop();
	return 0;
}


