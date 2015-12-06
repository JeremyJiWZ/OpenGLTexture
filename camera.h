//
//  camera.h
//  VirtualObject
//
//  Created by mr.ji on 15/11/27.
//  Copyright (c) 2015年 mr.ji. All rights reserved.
//

#ifndef __VirtualObject__camera__
#define __VirtualObject__camera__

#include <stdio.h>
#include <math.h>
#include <GLUT/GLUT.h>
#define Pi 3.14159265
class Point3
{
public:
    float x,y,z;
    void set(float dx,float dy,float dz)
    {
        x=dx; y=dy; z=dz;
    }
    void set(Point3& p)
    {
        x=p.x; y=p.y; z=p.z;
    }
    Point3(float xx,float yy,float zz)
    {
        x=xx; y=yy; z=zz;
    }
    Point3()
    {
        x=y=z=0;
    }
    void build4tuple(float v[])
    {
        v[0]=x; v[1]=y; v[2]=z; v[3]=1.0f;
    }
    float dist()
    {
        float dist;
        dist=powf(x, 2)+powf(y, 2)+powf(z, 2);
        dist=sqrtf(dist);
        return dist;
    }
};

class Vector3
{
public:
    float x,y,z;
    void set(float dx,float dy,float dz)
    {
        x=dx; y=dy; z=dz;
    }
    void set(Vector3& v)
    {
        x=v.x; y=v.y; z=v.z;
    }
    void flip()
    {
        x=-x; y=-y; z=-z;
    }
    void setDiff(Point3& a,Point3& b)
    {
        x=a.x-b.x; y=a.y-b.y; z=a.z-b.z;
    }
    //noramalize the vector to distance 1
    void normalize()
    {
        float base=pow(x,2)+pow(y,2)+pow(z,2);
        x=x/pow(base,0.5);
        y=y/pow(base,0.5);
        z=z/pow(base,0.5);
    }
    Vector3(float xx, float yy, float zz)
    {
        x=xx; y=yy; z=zz;
    }
    Vector3(Vector3 const &v)
    {
        x=v.x; y=v.y; z=v.z;
    }
    Vector3()
    {
        x=0; y=0; z=0;
    }
    //叉积
    Vector3 cross(Vector3 b)
    {
        float x1,y1,z1;
        x1=y*b.z-z*b.y;
        y1=z*b.x-x*b.z;
        z1=x*b.y-y*b.x;
        Vector3 c(x1,y1,z1);
        return c;
    }
    //点积
    float dot(Vector3 b)
    {
        float d=x*b.x+y*b.y+z*b.z;
        return d;
    }
};

class Camera
{
public:
    /* 构造函数和析构函数 */
    Camera();
    ~Camera();
    
    /* 设置摄像机的位置, 观察点和向上向量 */
    void setCamera( float eyeX, float eyeY, float eyeZ,
                   float lookX, float lookY, float lookZ,
                   float upX, float upY, float upZ);
    
    //往前走
    void forward();
    //向后走
    void backward();
    //向左走
    void left();
    //向右走
    void right();
    //绕中心左右转
    void rotateLR(float du);
    //绕中心上下转
    void rotateUD(float du);
    
    //平移
    void slide(float du, float dv, float dn);
    
    Point3  eye,look,up;
    int eye_fi=0,eye_theta=15;
    float r=8.0;
    
    
private:
    /* 摄像机属性 */

//    Vector3        u,v,n;
    float          viewAngle, aspect, nearDist, farDist;
//    void           setModelViewMatrix();
    
};

#endif /* defined(__VirtualObject__camera__) */
