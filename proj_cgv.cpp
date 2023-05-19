#include<iostream>
#include<string.h>
#include<GL/glut.h>
#include<GL/glu.h>
#include<GL/gl.h>
using namespace std;
 
void drawStringAtPos(double x, double y, string msg) {
	glRasterPos2f(x, y);
	for(unsigned int i = 0; i < msg.size(); i++)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, msg[i]);
}

void myinit()
{
   glMatrixMode(GL_PROJECTION_MATRIX);
   glLoadIdentity();
   gluOrtho2D(0,500,0,500);
   glMatrixMode(GL_MODELVIEW);
}
 
void disp()
{
    glClearColor(0,0,0,1);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1,0,0);
    drawStringAtPos(225,400,"Department of CSE");    
    glFlush();
}
int main(int argc,char *argv[])
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowSize(1200,650); //w h
    glutCreateWindow("T1");
    myinit();
    glutDisplayFunc(disp);
    glutMainLoop();
    return 0;
}