#include <windows.h>
#include <GL/freeglut.h>
#include "model.h"
#include "SOIL.h"
#include "mycamero.h"

using namespace std;

Model *wall = new Model();	//墙壁 
Model *desk = new Model();  //桌子 
Model *chairs = new Model();//椅子 
Model *screen = new Model();//屏幕 

Camero *camero = new Camero();

//加载纹理
void LoadTexture(const char *imagepath, GLuint textureId) {
    glBindTexture(GL_TEXTURE_2D, textureId);
    GLubyte *imageData = NULL;
    int picWidth, picHeight;
    imageData = SOIL_load_image(imagepath, &picWidth, &picHeight, 0, SOIL_LOAD_RGB);
    gluBuild2DMipmaps(GL_TEXTURE_2D,GL_RGBA,picWidth,picHeight,GL_RGB,GL_UNSIGNED_BYTE,imageData);
    imageData=NULL;
} 

//天空盒
void skybox(float x, float y, float z, float box_width, float box_height, float box_length) {
    //背面 
    glBindTexture(GL_TEXTURE_2D, 4);
    glBegin(GL_QUADS);
    	glTexCoord2f(1.0f, 1.0f); glVertex3f(x + box_width/2+0.1, y-0.1, z - box_length/2);
        glTexCoord2f(1.0f, 0.0f); glVertex3f(x + box_width/2+0.1, y + box_height+0.1, z - box_length/2); 
        glTexCoord2f(0.0f, 0.0f); glVertex3f(x - box_width/2-0.1, y + box_height+0.1, z - box_length/2);
        glTexCoord2f(0.0f, 1.0f); glVertex3f(x - box_width/2-0.1, y-0.1, z - box_length/2);
    glEnd();
    //前面 
    glBindTexture(GL_TEXTURE_2D, 6);
    glBegin(GL_QUADS);
    	glTexCoord2f(0.0f, 1.0f); glVertex3f(x + box_width/2+0.1, y-0.1, z + box_length/2);
        glTexCoord2f(0.0f, 0.0f); glVertex3f(x + box_width/2+0.1, y + box_height+0.1, z + box_length/2); 
        glTexCoord2f(1.0f, 0.0f); glVertex3f(x - box_width/2-0.1, y + box_height+0.1, z + box_length/2);
        glTexCoord2f(1.0f, 1.0f); glVertex3f(x - box_width/2-0.1, y-0.1, z + box_length/2);
    glEnd();
    //右面 
    glBindTexture(GL_TEXTURE_2D, 8);
    glBegin(GL_QUADS);
    	glTexCoord2f(1.0f, 1.0f); glVertex3f(x + box_width/2, y-0.1, z + box_length/2+0.1);
        glTexCoord2f(1.0f, 0.0f); glVertex3f(x + box_width/2, y + box_height+0.1, z + box_length/2+0.1); 
        glTexCoord2f(0.0f, 0.0f); glVertex3f(x + box_width/2, y + box_height+0.1, z - box_length/2-0.1);
        glTexCoord2f(0.0f, 1.0f); glVertex3f(x + box_width/2, y-0.1, z - box_length/2-0.1);
    glEnd();
    //左面 
    glBindTexture(GL_TEXTURE_2D, 7);
    glBegin(GL_QUADS);
    	glTexCoord2f(0.0f, 1.0f); glVertex3f(x - box_width/2, y-0.1, z + box_length/2+0.1);
        glTexCoord2f(0.0f, 0.0f); glVertex3f(x - box_width/2, y + box_height+0.1, z + box_length/2+0.1); 
        glTexCoord2f(1.0f, 0.0f); glVertex3f(x - box_width/2, y + box_height+0.1, z - box_length/2-0.1);
        glTexCoord2f(1.0f, 1.0f); glVertex3f(x - box_width/2, y-0.1, z - box_length/2-0.1);
    glEnd();
    //上面
	glBindTexture(GL_TEXTURE_2D, 9);
	glBegin(GL_QUADS);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(x + box_width/2+0.1, y + box_height, z - box_length/2-0.1); 
        glTexCoord2f(0.0f, 1.0f); glVertex3f(x - box_width/2-0.1, y + box_height, z - box_length/2-0.1);
        glTexCoord2f(0.0f, 0.0f); glVertex3f(x - box_width/2-0.1, y + box_height, z + box_length/2+0.1);
        glTexCoord2f(1.0f, 0.0f); glVertex3f(x + box_width/2+0.1, y + box_height, z + box_length/2+0.1); 
    glEnd();
    //下面 
    glBindTexture(GL_TEXTURE_2D, 5);
	glBegin(GL_QUADS);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(x + box_width/2+0.1, y, z - box_length/2-0.1); 
        glTexCoord2f(0.0f, 0.0f); glVertex3f(x - box_width/2-0.1, y, z - box_length/2-0.1);
        glTexCoord2f(0.0f, 1.0f); glVertex3f(x - box_width/2-0.1, y, z + box_length/2+0.1);
        glTexCoord2f(1.0f, 1.0f); glVertex3f(x + box_width/2+0.1, y, z + box_length/2+0.1); 
    glEnd();
}    

//初始化 
void init() {
    glEnable(GL_TEXTURE_2D); 
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_POLYGON_SMOOTH); //启用多边形抗锯齿 
    glHint(GL_POLYGON_SMOOTH_HINT,GL_NICEST);
    //加载模型 
    wall->LoadModel("model/wall.obj");
    desk->LoadModel("model/desk.obj");
    chairs->LoadModel("model/chairs.obj");
    screen->LoadModel("model/screen.obj");
    //加载纹理 
    GLuint texture_ID_list[9];
	glGenTextures(9, texture_ID_list);
	LoadTexture("image/wall.jpg", 1);
    LoadTexture("image/desk.jpg", 2);
    LoadTexture("image/screen.jpg", 3);
    
    LoadTexture("image/sky_bk.jpg", 4);
    LoadTexture("image/sky_dn.jpg", 5);
    LoadTexture("image/sky_ft.jpg", 6);
    LoadTexture("image/sky_lf.jpg", 7);
    LoadTexture("image/sky_rt.jpg", 8);
    LoadTexture("image/sky_up.jpg", 9);
}

//显示回调函数 
void renderScene() {
    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    
    glMatrixMode(GL_PROJECTION);
	glFrustum(-1,1,-1,1,1,100);
    camero->setCamero();
    
    glBindTexture(GL_TEXTURE_2D, 1);
    wall->Flat();
    glBindTexture(GL_TEXTURE_2D, 2);
    desk->Flat();
    chairs->Flat();
    glBindTexture(GL_TEXTURE_2D, 3);
    screen->Flat();
    
    glDisable(GL_LIGHTING);
    skybox(0, 0, 0, 50, 20, 50); 
    glEnable(GL_LIGHTING); 
    
    glFlush();
    glutSwapBuffers();
}

//设置光源
void SetupLights() {
    GLfloat light_position[] ={0.0f,8.0f,0.0f,1.0f}; 
    GLfloat ambientLight[]={0.8f,0.8f,0.8f,1.0f};	//白色环境光  
    GLfloat diffuseLight[]={0.8f,0.8f,0.8f,0.8f};	//白色漫反射  
    GLfloat specularLight[]={1.0f,1.0f,1.0f,1.0f};	//白色镜面光
    glLightfv(GL_LIGHT0,GL_AMBIENT,ambientLight);   //设置环境光源  
    glLightfv(GL_LIGHT0,GL_DIFFUSE,diffuseLight);   //设置漫反射光源  
    glLightfv(GL_LIGHT0,GL_SPECULAR,specularLight); //设置镜面光源  
    glLightfv(GL_LIGHT0,GL_POSITION,light_position);//设置灯光位置  
    glEnable(GL_LIGHT0); //打开白色主光源
    glEnable(GL_LIGHTING); 
}    

//鼠标移动 
void motion(int x, int y) {
    camero->moveMouse(x, y);
}    

//键盘响应 
void processNormalKey(unsigned char key, int x, int y){
    switch (key) {
        case 27:	//esc退出 
            exit(0);
        case 119:	//按下w键
        	camero->moveW();
            break;
        case 115:	//按下s键
        	camero->moveS();
            break;
        case 97:	//按下a键
        	camero->moveA();
            break;
        case 100:	//按下d键
        	camero->moveD();
            break;
    }    
}    

int main(int argc, char *argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB | GLUT_MULTISAMPLE);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Room");
    init();
    glutDisplayFunc(renderScene);
    glutIdleFunc(renderScene);
    SetupLights(); //设置光源 
    glutPassiveMotionFunc(motion); //鼠标移动响应事件 
    glutKeyboardFunc(processNormalKey); //键盘响应事件 
    glutMainLoop();
    return 0;
}
