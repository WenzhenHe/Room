#ifndef _MYCAMERO_
#define _MYCAMERO_

#include <GL/freeglut.h>
#include <windows.h>
#include <iostream>
#include <math.h>
using namespace std;

class Vector3
{
public:
    Vector3()  { x = 0.0; y = 0.0; z = 0.0; }
    Vector3(float a, float b, float c)
    {
        x = a;
        y = b;
        z = c;
    }
    Vector3(const Vector3& vector)
    {
        x = vector.x;
        y = vector.y;
        z = vector.z;
    }    
    void normalize() {
        float length = (float)(x * x + y * y + z * z);
        if(length == 0) length = 1;
        x = x/length;
        y = y/length;
        z = z/length;
    }
    Vector3 normalVector(const Vector3& v) {
        Vector3 vec;

    	vec.x = y * v.z - z * v.y;
    	vec.y = z * v.x - x * v.z;
    	vec.z = x * v.y - y * v.x;

    	return vec;
    }    
    Vector3 operator - (const Vector3& v) {
        Vector3 vec;

    	vec.x = x - v.x;
    	vec.y = y - v.y;
    	vec.z = z - v.z;

    	return vec;
    }
    Vector3 operator + (const Vector3& v) {
        Vector3 vec;

    	vec.x = x + v.x;
    	vec.y = y + v.y;
    	vec.z = z + v.z;

    	return vec;
    }
    Vector3 operator * (float scale) {
    	x = x * scale;
    	y = y * scale;
    	z = z * scale;

    	return *this;
    }    
public:
    float x,y,z;
};    

class Camero
{
public:
    Camero() {
    	Vector3 a = Vector3(-5.0, 5.0, 5.0);      
    	Vector3 b = Vector3(0.0, 5.0, 5.0);      
    	Vector3 c = Vector3(0.0, 1.0, 0.0);
    	
    	position = a;
    	center = b;
    	upVector = c;
    	mouseX = -1;
    	mouseY = -1;
    	speed = 0.5;
    }
    ~Camero() {} 
	void setCamero() {
	    gluLookAt(position.x,position.y,position.z,
     			  center.x,center.y,center.z,
      			  upVector.x,upVector.y,upVector.z);
	}    
	void moveW() {
	    Vector3 vector = center - position;
	    vector.normalize();   
 		
 		position.x += vector.x * speed;
 		//position.y += vector.y * speed;
 		position.z += vector.z * speed;
 		
 		center.x += vector.x * speed;
 		//center.y += vector.y * speed;
 		center.z += vector.z * speed;
	}    
	void moveS() {
	    Vector3 vector = position - center;
	    vector.normalize();   
 		
 		position.x += vector.x * speed;
 		//position.y += vector.y * speed;
 		position.z += vector.z * speed;
 		
 		center.x += vector.x * speed;
 		//center.y += vector.y * speed;
 		center.z += vector.z * speed;
	}
	void moveA() {
	    Vector3 vector = position - center;
	    vector = vector.normalVector(upVector);
	    vector.normalize();
	    
	    position.x += vector.x * speed;
 		//position.y += vector.y * speed;
 		position.z += vector.z * speed;
 		
 		center.x += vector.x * speed;
 		//center.y += vector.y * speed;
 		center.z += vector.z * speed;
	}
	void moveD() {
	    Vector3 vector = center - position;
	    vector = vector.normalVector(upVector);
	    vector.normalize();
	    
	    position.x += vector.x * speed;
 		//position.y += vector.y * speed;
 		position.z += vector.z * speed;
 		
 		center.x += vector.x * speed;
 		//center.y += vector.y * speed;
 		center.z += vector.z * speed;
	}
	void moveMouse(int x, int y) {
	    if (mouseX == -1) {
	        mouseX = x;
	        mouseY = y;
	        return;
	    }
	    else if (mouseX == x && mouseY == y) {
	        return;
	    }    
	    else {
	        float aX = (float)(mouseX - x)/100.0;
	        float aY = (float)(mouseY - y)/250.0;
	        Vector3 vector = center - position;
	        Vector3 vectorX = vector.normalVector(upVector) * (-1);
	        Vector3 vectorY = upVector;
	        float length = (float)(vector.x * vector.x + vector.y * vector.y + vector.z * vector.z);
	        float radius = (float)(vector.x * vector.x + vector.z * vector.z);
	        vectorX.normalize();
	        vectorY.normalize();
	        Vector3 vectorXY;
	        //限制上下视角角度范围 
	        if (vector.y > 5 && vectorY.y * aY > 0) {
	            vectorXY = vectorX * aX;
	        }    
	        else if (vector.y < -5 && vectorY.y * aY < 0) {
	            vectorXY = vectorX * aX;
	        }    
	        else {
	            vectorXY = vectorX * aX + vectorY * aY;
	        }    
	        vectorXY = vectorXY * (length + 1.0);
	        vector = vector + vectorXY;
	        vector.normalize();
	        float scale = (float)radius/(vector.x * vector.x + vector.z * vector.z);
	        scale = sqrt(scale);
	        vector = vector * scale;
	        
	        center = position + vector;
	        mouseX = x;
	        mouseY = y;
	    } 
	}    

private:
    Vector3 position; //位置 
    Vector3 center; //朝向 
    Vector3 upVector; //向上方向 
    int mouseX;
    int mouseY;
    float speed;
};    

#endif
