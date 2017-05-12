#include <windows.h>
#include <GL/freeglut.h>
#include <math.h>
#include <time.h>
#include "model.h"

using namespace std;

Model *desk = new Model();
Model *chairs = new Model();

void init() {
    desk->LoadModel("model/desk.obj");
    chairs->LoadModel("model/chairs.obj");
}    

void renderScene() {
    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    
    glMatrixMode(GL_PROJECTION);
    glFrustum(-1,1,-1,1,0.85,100);
    gluLookAt(10.0,10.0,10.0, 0.0,0.0,0.0, 0.0,1.0,0.0);
    
    glColor3f(1.0, 1.0, 1.0);
    desk->Flat();
    chairs->Flat();

    //glColor3f(0.3, 0.3, 0.3);
	//desk->WireFrame();
    
    glFlush();
    glutSwapBuffers();
}


int main(int argc, char *argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Room");
    init();
    glutDisplayFunc(renderScene);
    glutIdleFunc(renderScene);
    glutMainLoop();
    return 0;
}
