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
#include "camera.h"

GLMmodel *model1,*model2,*model3,*model4,*model5;

float fTranslate;
float fRotate;

//定义光源信息
//static GLfloat dark[4] = { 0.0, 0.0, 0.0, 1.0 };
//static GLfloat normal[4] = { 0.5, 0.5, 0.5, 1.0 };
//static GLfloat bright[4] = { 1.0, 1.0, 1.0, 1.0 };
//static GLfloat pos[4] = { -0.2588, 0.0, 0.9659, 0.0 };
GLfloat specularLight[] = { 0.8f, 0.8f, 0.8f, 1.0f };//白色主光源镜面光
GLfloat white[] = { 0.2, 0.2, 0.2, 1.0 };
GLfloat diffuse[] = { 0.5, 0.5, 0.5, 1.0 };
GLfloat specular[] = { 0.8, 0.8, 0.8, 1.0 };
GLfloat light_pos[] = {0,20,0,1};

Bitmap texture1 =Bitmap("/Users/jiwentadashi/Desktop/专题研讨/研讨题目/物体几何模型/Texture.bmp");
Bitmap texture2 =Bitmap("/Users/jiwentadashi/Desktop/专题研讨/研讨题目/物体几何模型/texture2.bmp");
Bitmap texture3 =Bitmap("/Users/jiwentadashi/Pragramming/VirtualObject/VirtualObject/cow.bmp");
GLuint texNames[10];

//定义模式
bool bPersp = true;
bool bAnim = false;
bool bWire = false;
bool bmove=false;
bool bback=false;
bool SelectMode=false;

//视窗
int wHeight = 0;
int wWidth = 0;

#define  GLUT_WHEEL_UP 3           //定义滚轮操作
#define  GLUT_WHEEL_DOWN 4
//监听鼠标滚轮
//int oldmx=-1,oldmy=-1;

//照相机类
Camera ca;

//标志物体是否被选中
bool ObjectSelected[64];
//移动全局变量
float IntX=0,IntY=0,IntZ=0;

void bindTex();
void setLight();
void draw_identification(){
    glColor3f(1, 1, 1);
    //y coordinate
    glBegin(GL_LINES);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 5, 0);

    //x coordinate
    glVertex3f(0, 0, 0);
    glVertex3f(5, 0, 0);
    
    //z coordinate
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0, 5);
    
    glEnd();
    
}
void draw_scene(){
    int ObjectName=0;
    
    glEnable(GL_COLOR_MATERIAL);                        //启用材质的颜色跟踪
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);   //指定材料着色的面
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specularLight);   //指定材料对镜面光的反应
    glMateriali(GL_FRONT_AND_BACK, GL_SHININESS, 128);             //指定反射系数
    
    glEnable(GL_TEXTURE_2D);
    glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_REPLACE);
    glBindTexture(GL_TEXTURE_2D,texNames[1]);
    glPushMatrix();
    glBegin(GL_POLYGON);
    glTexCoord2f(0, 0); glVertex3f(-20, 0, 20);
    glTexCoord2f(0, 1); glVertex3f(20, 0, 20);
    glTexCoord2f(1, 1); glVertex3f(20, 0, -20);
    glTexCoord2f(1, 0); glVertex3f(-20, 0, -20);
    glEnd();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    
    //object 1
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texNames[1]);
    glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
    glTranslatef(-5, 1, 0);
    glLoadName(++ObjectName);
    if (ObjectSelected[1]){
        glmDraw(model1, GLM_SMOOTH);
        draw_identification();
    }
    else
        glmDraw(model1, GLM_SMOOTH|GLM_TEXTURE);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
    
    //object2
    glPushMatrix();
    glTranslatef(-3, 0.5, 0);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texNames[0]);
    glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
    glLoadName(++ObjectName);
    if (ObjectSelected[2]){
        glmDraw(model2, GLM_SMOOTH);
        draw_identification();
    }
    else
        glmDraw(model2, GLM_SMOOTH|GLM_TEXTURE);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
    
    //object 3
    glPushMatrix();
    glTranslatef(0+IntX*0.001, 0.5+IntY*0.001, 0+IntZ*0.001);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texNames[2]);
    glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
    glLoadName(++ObjectName);
    if (ObjectSelected[3]){
        glmDraw(model3, GLM_SMOOTH);
        draw_identification();
    }
    else
        glmDraw(model3, GLM_SMOOTH|GLM_TEXTURE);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
    
    //object 4
    glPushMatrix();
    glTranslatef(3, 1, 0);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texNames[0]);
    glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
    glLoadName(++ObjectName);
    if (ObjectSelected[4]){
        glmDraw(model4, GLM_SMOOTH);
        draw_identification();
    }
    else
        glmDraw(model4, GLM_SMOOTH|GLM_TEXTURE);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
    
    //object 5
    glPushMatrix();
    glTranslatef(5, 0.5, 0);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texNames[0]);
    glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
    glLoadName(++ObjectName);
    if (ObjectSelected[5]){
        glmDraw(model5, GLM_SMOOTH);
        draw_identification();
    }
    else
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
            ca.left();
            break;
        }
        case 'd': {//todo
            ca.right();
            break;
        }
        case 'w': {//todo
            ca.forward();
            break;
        }
        case 's': {//todo
            ca.backward();
            break;
        }
        case 'm':
            bmove=!bmove;
            break;
        case 'b':
            bback=!bback;
            break;
        case 'i':
            SelectMode=!SelectMode;
            break;
        case 'z': {//todo
//            ca.closer();
            break;
        }
        case 'c': {//todo
//            ca.farer();
            break;
        }
        case '=':
            white[0]+=0.1;
            white[1]+=0.1;
            white[2]+=0.1;
            break;
        case '-':
            white[0]-=0.1;
            white[1]-=0.1;
            white[2]-=0.1;
            break;
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
void processHits(GLint hits, GLuint buffer[])
{
    unsigned int i, j;
    GLuint names, *ptr;
    
    printf("hits = %d\n", hits);
    ptr = (GLuint *)buffer;
    for (i = 0; i < hits; i++) { /*  for each hit  */
        names = *ptr;
        printf(" number of names for hit = %d\n", names); ptr++;
        printf("  z1 is %g;", (float)*ptr / 0x7fffffff); ptr++;
        printf(" z2 is %g\n", (float)*ptr / 0x7fffffff); ptr++;
        printf("   the name is ");
        for (j = 0; j < names; j++) {     /*  for each name */
            printf("%d ", *ptr); ptr++;
        }
        printf("\n");
    }
}
void SelectFunc(int x, int y){
    GLuint buffer[64] = {0};
    GLint hits,view[4];
    
    glSelectBuffer(64, buffer);
    
    //retrieve info about the viewport
    glGetIntegerv(GL_VIEWPORT, view);
    //switch select mode
    glRenderMode(GL_SELECT);
    
    glInitNames();
    glPushName(0);
    
    //modify the vieving volume, restricting selection area around the cursor
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    
    //restrict the draw to an area around the cursor
    gluPickMatrix(x, y, 0.1, 0.1, view);
    gluPerspective(45.0f, (GLfloat)wWidth / (GLfloat)wHeight, 0.1f, 100.0f);
    
    //pretend to draw the objects onto the screen
    glMatrixMode(GL_MODELVIEW);
    glutSwapBuffers();
    draw_scene();
    
    //restore the view
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    
    //get number of objects drawed in that area and return to render mode
    hits = glRenderMode(GL_RENDER);
    
    processHits(hits, buffer);
    
    if (hits >= 1)
    {
        int choose = buffer[3];
        int depth = buffer[1];
        
        for (int i = 0; i < hits; i++)
        {
            if (buffer[i * 4 + 1] < (GLuint)depth)	//obtain selected object with minimum depth
            {
                choose = buffer[i * 4 + 3];
                depth = buffer[i * 4 + 1];
            }
        }
        ObjectSelected[choose] = true;
    }
    
    glMatrixMode(GL_MODELVIEW);
}
int OldX,OldY;
void processMouse(int button, int state, int x, int y)
{
    if (button == GLUT_WHEEL_UP)
    {
        //        r += 0.3;
        //        ca.closer();
    }
    if (button == GLUT_WHEEL_DOWN)
    {
        //        r -= 0.3;
        //        ca.farer();
    }
    if ((button == GLUT_LEFT_BUTTON) && (state == GLUT_DOWN)){
        SelectFunc(x, wHeight-y);
        OldX=x;
        OldY=y;
    }
    if((button==GLUT_RIGHT_BUTTON)&&(state==GLUT_DOWN)){
        for (int i=0;i<6;i++)
            ObjectSelected[i]=false;
    }
}
//监听鼠标拖动,移动物体
void motion(int x, int y){
    int dx,dy;
    dx=x-OldX,dy=y-OldY;
    if (ObjectSelected[3]){
        if (dx+dy>=-5&&dx+dy<=5) {     //移动z轴
            IntZ+=dy*powf(2.0, 0.5);
        }
        else if(abs(dy)>abs(dx)){  //移动y轴
            IntY+=-dy;
        }
        else {  //移动z轴
            IntX+=dx;
        }
    }
    
}
int lastX=-1,lastY=-1;
int deltax=0,deltay=0;
void MouseMove(int x,int y){
    deltax=x-lastX;
    deltay=y-lastY;
//    printf("delta x:%d\n",deltax);
//    printf("delta y:%d\n",deltay);
    if (lastX==-1&&lastY==-1) {
        glutWarpPointer(320, 320);
        printf("move!\n");
    }
    else if(!SelectMode){
        ca.rotateLR(-deltax);
        ca.rotateUD(deltay);
        glutWarpPointer(320, 320);
    }
    lastX=320;
    lastY=320;
}

void redraw()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();									// Reset The Current Modelview Matrix
    
//    gluLookAt(r*cos(du*Pi/180), h, r*sin(du*Pi/180),
//              center[0], center[1], center[2],
//              0, 1, 0);				// 场景（0，0，0）的视点中心 (0,5,50)，Y轴向上
    
    if (bmove) ca.forward();
    if (bback) ca.backward();
    float eyex=ca.eye.x,eyey=ca.eye.y,eyez=ca.eye.z;
    float centerx=ca.look.x,centery=ca.look.y,centerz=ca.look.z;
    float upx=ca.up.x,upy=ca.up.y,upz=ca.up.z;
//    cout<<"eye:"<<eyex<<' '<<eyey<<' '<<eyez<<endl;
//    cout<<"center:"<<centerx<<' '<<centery<<' '<<centerz<<endl;
//    cout<<upx<<' '<<upy<<' '<<upz<<endl;
    gluLookAt(eyex, eyey, eyez,
              centerx, centery, centerz,
              upx, upy, upz);
    if (bWire) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }
    else {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
    
    glEnable(GL_DEPTH_TEST);
//    glEnable(GL_LIGHTING);

    
//    glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
//    glLightfv(GL_LIGHT0, GL_AMBIENT, white);
//    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
//    glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
//    glEnable(GL_LIGHT0);
    setLight();
    
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
    bindTex();
    
    glutWarpPointer(320, 320);
    ca.setCamera(0,2.08,8,0,0,0,0,1,0);
    memset(ObjectSelected, false, sizeof(ObjectSelected));
    
    glShadeModel(GL_SMOOTH);
    setLight();
    
}
void setLight(){
        glEnable(GL_LIGHTING);
        glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
        glLightfv(GL_LIGHT0, GL_AMBIENT, white);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
        glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
        glEnable(GL_LIGHT0);
}

void bindTex(){
    
    glEnable(GL_COLOR_MATERIAL);                        //启用材质的颜色跟踪
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);   //指定材料着色的面
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specularLight);   //指定材料对镜面光的反应
    glMateriali(GL_FRONT_AND_BACK, GL_SHININESS, 128);             //指定反射系数
    
    glGenTextures(1, texNames);
    glBindTexture(GL_TEXTURE_2D, texNames[0]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexImage2D(GL_TEXTURE_2D, 0, 3,
                 texture1.getWidth(), texture1.getHeight(),
                 0, GL_RGB, GL_UNSIGNED_BYTE, texture1.getImage());
    glGenTextures(1, &texNames[1]);
    
    glBindTexture(GL_TEXTURE_2D, texNames[1]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexImage2D(GL_TEXTURE_2D, 0, 3,
                 texture2.getWidth(), texture2.getHeight(),
                 0, GL_RGB, GL_UNSIGNED_BYTE, texture2.getImage());
    
    glGenTextures(1, &texNames[2]);
    glBindTexture(GL_TEXTURE_2D, texNames[2]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexImage2D(GL_TEXTURE_2D, 0, 3,
                 texture3.getWidth(), texture3.getHeight(),
                 0, GL_RGB, GL_UNSIGNED_BYTE, texture3.getImage());
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
    texture3.ReadImage();
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
    glutInitWindowSize(640,640);
    glutCreateWindow("Main");
    
    init();
    
    glutDisplayFunc(redraw);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(key);
    glutMouseFunc(processMouse);
    glutMotionFunc(motion);
    glutPassiveMotionFunc(MouseMove);
    glutIdleFunc(idle);

    glutMainLoop();
    
    return 0;
}

