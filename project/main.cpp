#include <windows.h>
#include <GL/freeglut.h>
#include <math.h>
#include <time.h>
#include "model.h"
#include "SOIL.h"

using namespace std;

Model *wall = new Model();	//墙壁 
Model *desk = new Model();  //桌子 
Model *chairs = new Model();//椅子 
Model *screen = new Model();//屏幕 

//加载纹理
void LoadTexture(const char *imagepath, GLuint textureId) {
    glBindTexture(GL_TEXTURE_2D, textureId);
    GLubyte *imageData = NULL;
    int picWidth, picHeight;
    imageData = SOIL_load_image(imagepath, &picWidth, &picHeight, 0, SOIL_LOAD_RGB);
    //glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, picWidth, picHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, imageData);
    gluBuild2DMipmaps(GL_TEXTURE_2D,GL_RGBA,picWidth,picHeight,GL_RGB,GL_UNSIGNED_BYTE,imageData);
    glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
    imageData=NULL;
} 

void init() {
    glEnable(GL_TEXTURE_2D); 
    glEnable(GL_DEPTH_TEST);
    //加载模型 
    wall->LoadModel("model/wall.obj");
    desk->LoadModel("model/desk.obj");
    chairs->LoadModel("model/chairs.obj");
    screen->LoadModel("model/screen.obj");
    //加载纹理 
    GLuint texture_ID_list[3];
	glGenTextures(3, texture_ID_list);
	LoadTexture("image/wall.jpg", 1);
    LoadTexture("image/desk.jpg", 2);
    LoadTexture("image/screen.jpg", 3);
}

void renderScene() {
    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    
    glMatrixMode(GL_PROJECTION);
    //glFrustum(-1,1,-1,1,0.85,10);
//    gluLookAt(0.0,0.0,2.0, 0.0,0.0,0.0, 0.0,1.0,0.0);
	glFrustum(-1,1,-1,1,0.85,100);
    gluLookAt(-5.0,5.0,-5.0, 0.0,0.0,0.0, 0.0,1.0,0.0);
    
    glBindTexture(GL_TEXTURE_2D, 1);
    wall->Flat();
    glBindTexture(GL_TEXTURE_2D, 2);
    desk->Flat();
    chairs->Flat();
    glBindTexture(GL_TEXTURE_2D, 3);
    screen->Flat();

    //glColor3f(0.3, 0.3, 0.3);
//    monkey->WireFrame();
    
    glFlush();
    glutSwapBuffers();
}


int main(int argc, char *argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("MeshView");
    init();
    glutDisplayFunc(renderScene);
    glutIdleFunc(renderScene);
    glutMainLoop();
    return 0;
}
