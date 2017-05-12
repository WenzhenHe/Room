#ifndef _MODEL_
#define _MODEL_

#include <stdio.h>
#include <io.h>

class Model
{
    public:
        Model() {
            v_num = 0;
            vt_num = 0;
            vn_num = 0;
            f_num = 0;
        }
        ~Model() {}
        //加载模型
        void LoadModel(const char *path) {
            FILE * file = fopen(path, "r");
            if( file == NULL ){  
                    return;  
            }
        
            while (1)
            {
                char lineHeader[128];
                int res = fscanf(file, "%s", lineHeader);  
                if (res == EOF)
                	break;
            	
            	if (strcmp(lineHeader, "v" ) == 0)
                {
                    v_num++;
                }
                else if (strcmp( lineHeader, "vt" ) == 0)
                {
                    vt_num++;
                }    
                else if (strcmp( lineHeader, "vn" ) == 0)
                {
                    vn_num++;
                }   
                else if (strcmp( lineHeader, "f" ) == 0) 
                {
                    f_num++;
                }
            	char stupidBuffer[100];  
            	fgets(stupidBuffer, 100, file);
            }
            
            
            fclose(file);
            file = fopen(path, "r");
        
            
            vArr = new float*[v_num];
         	for (int i = 0; i < v_num; i++) 
        	{
             	vArr[i] = new float[3];
        	}
        	vtArr = new float*[vt_num];
         	for (int i = 0; i < vt_num; i++) 
        	{
             	vtArr[i] = new float[2];
        	}
        	vnArr = new float*[vn_num];
         	for (int i = 0; i < vn_num; i++) 
        	{
             	vnArr[i] = new float[3];
        	}
        	fvArr = new int*[f_num];
        	fvtArr = new int*[f_num];
         	fvnArr = new int*[f_num];
          	for (int i = 0; i < f_num; i++)
           	{
                fvArr[i] = new int[3];
                fvtArr[i] = new int[3];
                fvnArr[i] = new int[3];
            } 
            
            int v_i = 0;
            int vt_i = 0;
            int vn_i = 0;
            int f_i = 0;
            while (1)
            {
                char lineHeader[128];
                int res = fscanf(file, "%s", lineHeader);  
                if (res == EOF)
                	break;
                
                if (strcmp(lineHeader, "v" ) == 0)
                {       
                    fscanf(file, "%f %f %f\n", &vArr[v_i][0], &vArr[v_i][1], &vArr[v_i][2]);
                    v_i++;
                }
                else if (strcmp( lineHeader, "vt" ) == 0)
                {
                    fscanf(file, "%f %f\n", &vtArr[vt_i][0], &vtArr[vt_i][1]);
                    vt_i++;
                }    
                else if (strcmp( lineHeader, "vn" ) == 0)
                {
                    fscanf(file, "%f %f %f\n", &vnArr[vn_i][0], &vnArr[vn_i][1], &vnArr[vn_i][2]);
                    vn_i++;
                }   
                else if (strcmp( lineHeader, "f" ) == 0) 
                {
                    fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n",
                    &fvArr[f_i][0], &fvtArr[f_i][0], &fvnArr[f_i][0],
                    &fvArr[f_i][1], &fvtArr[f_i][1], &fvnArr[f_i][1],
                    &fvArr[f_i][2], &fvtArr[f_i][2], &fvnArr[f_i][2]);
                    for (int i = 0; i < 3; i++)
                    {
                        fvArr[f_i][i] = fvArr[f_i][i] - 1;
                        fvtArr[f_i][i] = fvtArr[f_i][i] - 1;
                        fvnArr[f_i][i] = fvnArr[f_i][i] - 1;
                    }
                    f_i++;
                }
                else
                {
                	char stupidBuffer[100];  
                	fgets(stupidBuffer, 100, file); 
                }        
            }
            v_num = v_i;
            vt_num = vt_i;
            vn_num = vn_i;
            f_num = f_i;
        }
        //绘制网格模型 
        void WireFrame() {
            for (int i = 0; i < f_num; i++)
            {
                glBegin(GL_LINES);
                glVertex3f(vArr[fvArr[i][0]][0], vArr[fvArr[i][0]][1], vArr[fvArr[i][0]][2]);
                glVertex3f(vArr[fvArr[i][1]][0], vArr[fvArr[i][1]][1], vArr[fvArr[i][1]][2]);
                
                glVertex3f(vArr[fvArr[i][1]][0], vArr[fvArr[i][1]][1], vArr[fvArr[i][1]][2]);
                glVertex3f(vArr[fvArr[i][2]][0], vArr[fvArr[i][2]][1], vArr[fvArr[i][2]][2]);
                
                glVertex3f(vArr[fvArr[i][0]][0], vArr[fvArr[i][0]][1], vArr[fvArr[i][0]][2]);
                glVertex3f(vArr[fvArr[i][2]][0], vArr[fvArr[i][2]][1], vArr[fvArr[i][2]][2]);
                glEnd();
            }
        }
        //绘制面模型 
        void Flat() {
            for (int i = 0; i < f_num; i++)
            {
                glBegin(GL_TRIANGLES);
                glVertex3f(vArr[fvArr[i][0]][0], vArr[fvArr[i][0]][1], vArr[fvArr[i][0]][2]);
                glVertex3f(vArr[fvArr[i][1]][0], vArr[fvArr[i][1]][1], vArr[fvArr[i][1]][2]);
                glVertex3f(vArr[fvArr[i][2]][0], vArr[fvArr[i][2]][1], vArr[fvArr[i][2]][2]);
                glEnd();
            }
        }
        //加载纹理
        //void Texture(const char *iamgepath) {
//            GLuint textureId;
//            glEnable(GL_TEXTURE_2D); 
//            glGenTextures(1, &textureId);
//            glBindTexture(GL_TEXTURE_2D, textureId);
//            
//            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//            
//            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
//            
//            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imagewidth,imageheight, 0, GL_RGB, GL_UNSIGNED_BYTE, imageData); // 定义纹理图像
//        }
    
    private:
        int v_num;
		int vt_num;
		int vn_num;
		int f_num;

		float **vArr; 	//顶点数组 
		float **vtArr;	//纹理坐标数组 
		float **vnArr;	//法向量数组
		//面数组 
		int **fvArr;
		int **fvtArr;
		int **fvnArr;
};
#endif
