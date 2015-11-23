//
//  main.cpp
//  VirtualObject
//
//  Created by mr.ji on 15/11/21.
//  Copyright (c) 2015年 mr.ji. All rights reserved.
//

#include <iostream>
#include <GLUT/GLUT.h>
#include <math.h>
#include "glm.h"
#include "bitmapProcess.h"
#define Pi 3.14159126
GLMmodel *model1,*model2,*model3,*model4,*model5;
float fTranslate;
float fRotate;
float scaleRatio=1.0f;//缩放率
//定义光源信息
static GLfloat dark[4] = { 0.0, 0.0, 0.0, 1.0 };
static GLfloat normal[4] = { 0.5, 0.5, 0.5, 1.0 };
static GLfloat bright[4] = { 1.0, 1.0, 1.0, 1.0 };
static GLfloat pos[4] = { -0.2588, 0.0, 0.9659, 0.0 };
Bitmap texture1 =Bitmap("/Users/jiwentadashi/Desktop/专题研讨/研讨题目/物体几何模型/Texture.bmp");
Bitmap texture2 =Bitmap("/Users/jiwentadashi/Desktop/专题研讨/研讨题目/物体几何模型/texture2.bmp");
GLuint texNames[10];
bool bPersp = true;
bool bAnim = false;
bool bWire = false;
int wHeight = 0;
int wWidth = 0;
float center[] = {0, 0, 0};
#define  GLUT_WHEEL_UP 3           //定义滚轮操作
#define  GLUT_WHEEL_DOWN 4
//监听鼠标滚轮
int oldmx=-1,oldmy=-1;
float du=90.0;
float r=8.0f,h=0.5f;
void processMouse(int button, int state, int x, int y)
{
    if (button == GLUT_WHEEL_UP)
    {
        r += 0.3;
    }
    if (button == GLUT_WHEEL_DOWN)
    {
        r -= 0.3;
    }
    if(state==GLUT_DOWN) //第一次鼠标按下时,记录鼠标在窗口中的初始坐标
        oldmx=x,oldmy=y;
}
//监听鼠标拖动
void motion(int x, int y){
    
    du+=x-oldmx;
    h +=0.03f*(y-oldmy); //鼠标在窗口y轴方向上的改变加到视点的y坐标上，就上下转了
//    if(eye[1]>1.0f) eye[1]=1.0f; //视点y坐标作一些限制，不会使视点太奇怪
//    else if(eye[1]<-1.0f) eye[1]=-1.0f;
    
    oldmx=x,oldmy=y; //把此时的鼠标坐标作为旧值，为下一次计算增量做准备
}
void bindTex();
void draw_scene(){
    bindTex();
    
    glEnable(GL_TEXTURE_2D);
    glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_REPLACE);
    glBindTexture(GL_TEXTURE_2D,texNames[1]);
    glPushMatrix();
    glBegin(GL_POLYGON);
    glTexCoord2f(0, 0); glVertex3f(-10, 0, 10);
    glTexCoord2f(0, 1); glVertex3f(10, 0, 10);
    glTexCoord2f(1, 1); glVertex3f(10, 0, -10);
    glTexCoord2f(1, 0); glVertex3f(-10, 0, -10);
    glEnd();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texNames[1]);
    glTranslatef(-5, 1, 0);
    glmDraw(model1, GLM_SMOOTH|GLM_TEXTURE);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(-3, 0.5, 0);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texNames[0]);
    glmDraw(model2, GLM_SMOOTH|GLM_TEXTURE);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(0, 0.5, 0);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texNames[0]);
    glmDraw(model3, GLM_SMOOTH|GLM_TEXTURE);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(3, 1, 0);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texNames[0]);
    glmDraw(model4, GLM_SMOOTH|GLM_TEXTURE);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(5, 0.5, 0);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texNames[0]);
    glmDraw(model5, GLM_SMOOTH|GLM_TEXTURE);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
    
}


void updateView(int width, int height)
{
    glViewport(0,0,width,height);						// Reset The Current Viewport
    
    glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
    glLoadIdentity();									// Reset The Projection Matrix
    
    float whRatio = (GLfloat)width/(GLfloat)height;
    
    if (bPersp){
        //todo when 'p' operation, hint: use FUNCTION gluPerspective
        gluPerspective(45.0, whRatio, 0.1, 300);
    }
    else
        glOrtho(-5 ,5, -5, 5,-100,100);
    
    glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
}
void key(unsigned char k, int x, int y)
{
    switch(k)
    {
        case 27:
        case 'q': {exit(0); break; }
        case 'p': {bPersp = !bPersp; updateView(wHeight, wWidth);break; }
            
        case ' ': {bAnim = !bAnim; break;}
        case 'o': {bWire = !bWire; break;}
            
        case 'a': {//todo, hint: eye[] and center[] are the keys to solve the problems
            break;
        }
        case 'd': {//todo
            break;
        }
        case 'w': {//todo
            break;
        }
        case 's': {//todo
            break;
        }
        case 'z': {//todo
            r-=0.3;
            break;
        }
        case 'c': {//todo
            r+=0.3;
            break;
        }
    }
}

void reshape(int width, int height)
{
    if (height==0)										// Prevent A Divide By Zero By
    {
        height=1;										// Making Height Equal One
    }
    
    wHeight = height;
    wWidth = width;
    
    updateView(wHeight, wWidth);
}

void idle()
{
    glutPostRedisplay();
}

void redraw()
{
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();									// Reset The Current Modelview Matrix
    
    gluLookAt(r*cos(du*Pi/180), h, r*sin(du*Pi/180),
              center[0], center[1], center[2],
              0, 1, 0);				// 场景（0，0，0）的视点中心 (0,5,50)，Y轴向上
    
    if (bWire) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }
    else {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
    
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    GLfloat white[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_pos[] = {5,5,5,1};
    
    glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
    glLightfv(GL_LIGHT0, GL_AMBIENT, white);
    glEnable(GL_LIGHT0);
    
    //	glTranslatef(0.0f, 0.0f,-6.0f);			// Place the triangle at Center
    glRotatef(fRotate, 0, 1.0f, 0);			// Rotate around Y axis
    glScalef(0.2, 0.2, 0.2);
    
    draw_scene();
    if (bAnim) fRotate    += 0.5f;
    
    //todo; hint: when you want to rotate the teapot, you may like to add another line here =)
    glutSwapBuffers();
}
void init(){
    glClearColor(0, 0, 0, 0);
    glmUnitize(model1);//单位化模型model并返回缩放比例因子，单位化就是把模型通过平移和缩放变换限制到3维坐标系中点为中心的一个单位正方体区域内
    glmFacetNormals(model1);//计算模型面的法向（假定多边形顶点顺序为逆时针）
    glmVertexNormals(model1, 90.0);//计算模型的平滑顶点法向，angle参数为平滑交叉的最大角度（角度制）
    
    glmUnitize(model2);//单位化模型model并返回缩放比例因子，单位化就是把模型通过平移和缩放变换限制到3维坐标系中点为中心的一个单位正方体区域内
    glmFacetNormals(model2);//计算模型面的法向（假定多边形顶点顺序为逆时针）
    glmVertexNormals(model2, 90.0);//计算模型的平滑顶点法向，angle参数为平滑交叉的最大角度（角度制）
    
    glmUnitize(model3);//单位化模型model并返回缩放比例因子，单位化就是把模型通过平移和缩放变换限制到3维坐标系中点为中心的一个单位正方体区域内
    glmFacetNormals(model3);//计算模型面的法向（假定多边形顶点顺序为逆时针）
    glmVertexNormals(model3, 90.0);//计算模型的平滑顶点法向，angle参数为平滑交叉的最大角度（角度制）
    
    glmUnitize(model4);//单位化模型model并返回缩放比例因子，单位化就是把模型通过平移和缩放变换限制到3维坐标系中点为中心的一个单位正方体区域内
    glmFacetNormals(model4);//计算模型面的法向（假定多边形顶点顺序为逆时针）
    glmVertexNormals(model4, 90.0);//计算模型的平滑顶点法向，angle参数为平滑交叉的最大角度（角度制）
    
    glmUnitize(model5);//单位化模型model并返回缩放比例因子，单位化就是把模型通过平移和缩放变换限制到3维坐标系中点为中心的一个单位正方体区域内
    glmFacetNormals(model5);//计算模型面的法向（假定多边形顶点顺序为逆时针）
    glmVertexNormals(model5, 90.0);//计算模型的平滑顶点法向，angle参数为平滑交叉的最大角度（角度制）

}
void bindTex(){
    glGenTextures(1, texNames);
    glBindTexture(GL_TEXTURE_2D, texNames[0]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexImage2D(GL_TEXTURE_2D, 0, 3,
                 texture1.getWidth(), texture1.getHeight(),
                 0, GL_RGB, GL_UNSIGNED_BYTE, texture1.getImage());
    glGenTextures(1, &texNames[1]);
    glBindTexture(GL_TEXTURE_2D, texNames[1]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexImage2D(GL_TEXTURE_2D, 0, 3,
                 texture2.getWidth(), texture2.getHeight(),
                 0, GL_RGB, GL_UNSIGNED_BYTE, texture2.getImage());
}
int main (int argc,  char *argv[])
{
    char fileName1[]="/Users/jiwentadashi/Desktop/专题研讨/研讨题目/物体几何模型/Ball_dABF.obj";
    char fileName2[]="/Users/jiwentadashi/Desktop/专题研讨/研讨题目/物体几何模型/Beetle_ABF.obj";
    char fileName3[]="/Users/jiwentadashi/Desktop/专题研讨/研讨题目/物体几何模型/Cow_dABF.obj";
    char fileName4[]="/Users/jiwentadashi/Desktop/专题研讨/研讨题目/物体几何模型/Gargoyle_ABF.obj";
    char fileName5[]="/Users/jiwentadashi/Desktop/专题研讨/研讨题目/物体几何模型/Isis_dABF.obj";
    model1 =glmReadOBJ(fileName1);
    model2 =glmReadOBJ(fileName2);
    model3 =glmReadOBJ(fileName3);
    model4 =glmReadOBJ(fileName4);
    model5 =glmReadOBJ(fileName5);
    texture1.ReadImage();
    texture2.ReadImage();
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
    glutInitWindowSize(640,480);
    glutCreateWindow("Main");
    
    init();
    glutDisplayFunc(redraw);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(key);
    glutMouseFunc(processMouse);
    glutMotionFunc(motion);
    glutIdleFunc(idle);

    glutMainLoop();
    
    return 0;
}

