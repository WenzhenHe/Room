#include <windows.h>
#include <GL/freeglut.h>
#include "model.h"
#include "SOIL.h"
#include "mycamero.h"

using namespace std;

Model *wall = new Model();	//ǽ�� 
Model *desk = new Model();  //���� 
Model *chairs = new Model();//���� 
Model *screen = new Model();//��Ļ 

Camero *camero = new Camero();

//��������
void LoadTexture(const char *imagepath, GLuint textureId) {
    glBindTexture(GL_TEXTURE_2D, textureId);
    GLubyte *imageData = NULL;
    int picWidth, picHeight;
    imageData = SOIL_load_image(imagepath, &picWidth, &picHeight, 0, SOIL_LOAD_RGB);
    gluBuild2DMipmaps(GL_TEXTURE_2D,GL_RGBA,picWidth,picHeight,GL_RGB,GL_UNSIGNED_BYTE,imageData);
    imageData=NULL;
} 

//��պ�
void skybox(float x, float y, float z, float box_width, float box_height, float box_length) {
    //���� 
    glBindTexture(GL_TEXTURE_2D, 4);
    glBegin(GL_QUADS);
    	glTexCoord2f(1.0f, 1.0f); glVertex3f(x + box_width/2+0.1, y-0.1, z - box_length/2);
        glTexCoord2f(1.0f, 0.0f); glVertex3f(x + box_width/2+0.1, y + box_height+0.1, z - box_length/2); 
        glTexCoord2f(0.0f, 0.0f); glVertex3f(x - box_width/2-0.1, y + box_height+0.1, z - box_length/2);
        glTexCoord2f(0.0f, 1.0f); glVertex3f(x - box_width/2-0.1, y-0.1, z - box_length/2);
    glEnd();
    //ǰ�� 
    glBindTexture(GL_TEXTURE_2D, 6);
    glBegin(GL_QUADS);
    	glTexCoord2f(0.0f, 1.0f); glVertex3f(x + box_width/2+0.1, y-0.1, z + box_length/2);
        glTexCoord2f(0.0f, 0.0f); glVertex3f(x + box_width/2+0.1, y + box_height+0.1, z + box_length/2); 
        glTexCoord2f(1.0f, 0.0f); glVertex3f(x - box_width/2-0.1, y + box_height+0.1, z + box_length/2);
        glTexCoord2f(1.0f, 1.0f); glVertex3f(x - box_width/2-0.1, y-0.1, z + box_length/2);
    glEnd();
    //���� 
    glBindTexture(GL_TEXTURE_2D, 8);
    glBegin(GL_QUADS);
    	glTexCoord2f(1.0f, 1.0f); glVertex3f(x + box_width/2, y-0.1, z + box_length/2+0.1);
        glTexCoord2f(1.0f, 0.0f); glVertex3f(x + box_width/2, y + box_height+0.1, z + box_length/2+0.1); 
        glTexCoord2f(0.0f, 0.0f); glVertex3f(x + box_width/2, y + box_height+0.1, z - box_length/2-0.1);
        glTexCoord2f(0.0f, 1.0f); glVertex3f(x + box_width/2, y-0.1, z - box_length/2-0.1);
    glEnd();
    //���� 
    glBindTexture(GL_TEXTURE_2D, 7);
    glBegin(GL_QUADS);
    	glTexCoord2f(0.0f, 1.0f); glVertex3f(x - box_width/2, y-0.1, z + box_length/2+0.1);
        glTexCoord2f(0.0f, 0.0f); glVertex3f(x - box_width/2, y + box_height+0.1, z + box_length/2+0.1); 
        glTexCoord2f(1.0f, 0.0f); glVertex3f(x - box_width/2, y + box_height+0.1, z - box_length/2-0.1);
        glTexCoord2f(1.0f, 1.0f); glVertex3f(x - box_width/2, y-0.1, z - box_length/2-0.1);
    glEnd();
    //����
	glBindTexture(GL_TEXTURE_2D, 9);
	glBegin(GL_QUADS);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(x + box_width/2+0.1, y + box_height, z - box_length/2-0.1); 
        glTexCoord2f(0.0f, 1.0f); glVertex3f(x - box_width/2-0.1, y + box_height, z - box_length/2-0.1);
        glTexCoord2f(0.0f, 0.0f); glVertex3f(x - box_width/2-0.1, y + box_height, z + box_length/2+0.1);
        glTexCoord2f(1.0f, 0.0f); glVertex3f(x + box_width/2+0.1, y + box_height, z + box_length/2+0.1); 
    glEnd();
    //���� 
    glBindTexture(GL_TEXTURE_2D, 5);
	glBegin(GL_QUADS);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(x + box_width/2+0.1, y, z - box_length/2-0.1); 
        glTexCoord2f(0.0f, 0.0f); glVertex3f(x - box_width/2-0.1, y, z - box_length/2-0.1);
        glTexCoord2f(0.0f, 1.0f); glVertex3f(x - box_width/2-0.1, y, z + box_length/2+0.1);
        glTexCoord2f(1.0f, 1.0f); glVertex3f(x + box_width/2+0.1, y, z + box_length/2+0.1); 
    glEnd();
}    

//��ʼ�� 
void init() {
    glEnable(GL_TEXTURE_2D); 
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_POLYGON_SMOOTH); //���ö���ο���� 
    glHint(GL_POLYGON_SMOOTH_HINT,GL_NICEST);
    //����ģ�� 
    wall->LoadModel("model/wall.obj");
    desk->LoadModel("model/desk.obj");
    chairs->LoadModel("model/chairs.obj");
    screen->LoadModel("model/screen.obj");
    //�������� 
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

//��ʾ�ص����� 
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

//���ù�Դ
void SetupLights() {
    GLfloat light_position[] ={0.0f,8.0f,0.0f,1.0f}; 
    GLfloat ambientLight[]={0.8f,0.8f,0.8f,1.0f};	//��ɫ������  
    GLfloat diffuseLight[]={0.8f,0.8f,0.8f,0.8f};	//��ɫ������  
    GLfloat specularLight[]={1.0f,1.0f,1.0f,1.0f};	//��ɫ�����
    glLightfv(GL_LIGHT0,GL_AMBIENT,ambientLight);   //���û�����Դ  
    glLightfv(GL_LIGHT0,GL_DIFFUSE,diffuseLight);   //�����������Դ  
    glLightfv(GL_LIGHT0,GL_SPECULAR,specularLight); //���þ����Դ  
    glLightfv(GL_LIGHT0,GL_POSITION,light_position);//���õƹ�λ��  
    glEnable(GL_LIGHT0); //�򿪰�ɫ����Դ
    glEnable(GL_LIGHTING); 
}    

//����ƶ� 
void motion(int x, int y) {
    camero->moveMouse(x, y);
}    

//������Ӧ 
void processNormalKey(unsigned char key, int x, int y){
    switch (key) {
        case 27:	//esc�˳� 
            exit(0);
        case 119:	//����w��
        	camero->moveW();
            break;
        case 115:	//����s��
        	camero->moveS();
            break;
        case 97:	//����a��
        	camero->moveA();
            break;
        case 100:	//����d��
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
    SetupLights(); //���ù�Դ 
    glutPassiveMotionFunc(motion); //����ƶ���Ӧ�¼� 
    glutKeyboardFunc(processNormalKey); //������Ӧ�¼� 
    glutMainLoop();
    return 0;
}
