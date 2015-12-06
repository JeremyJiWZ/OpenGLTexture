//
//  camera.cpp
//  VirtualObject
//
//  Created by mr.ji on 15/11/27.
//  Copyright (c) 2015年 mr.ji. All rights reserved.
//

#include "camera.h"
/* 构造函数 */
Camera::Camera()   {}

Camera::~Camera()  {}

/* 设置摄像机的位置,朝向和向上向量 */
void Camera::setCamera( float eyeX, float eyeY, float eyeZ,
                       float lookX, float lookY, float lookZ,
                       float upX, float upY, float upZ)
{
    /* 构造向量 */
    eye.set(eyeX, eyeY, eyeZ);
    look.set(lookX, lookY, lookZ);
    up.set(upX, upY, upZ);
    Vector3 upvec(up.x-eye.x,up.y-eye.y,up.z-eye.z);
    
    /* 计算n、u、v并归一化*/
//    n.set(eye.x-look.x, eye.y-look.y, eye.z-look.z);
//    u.set(upvec.cross(n).x,upvec.cross(n).y,upvec.cross(n).z);
//    v.set(n.cross(u).x,n.cross(u).y,n.cross(u).z);
    
//    u.normalize();
//    v.normalize();
//    n.normalize();
//    setModelViewMatrix();
}
void Camera::forward(){
    float dx=eye.x-look.x;
    float dy=eye.y-look.y;
    float dz=eye.z-look.z;
    eye.x-=dx*0.003;
    eye.y-=dy*0.003;
    eye.z-=dz*0.003;
    look.x-=dx*0.003;
    look.y-=dy*0.003;
    look.z-=dz*0.003;
}
void Camera::backward(){
    float dx=eye.x-look.x;
    float dy=eye.y-look.y;
    float dz=eye.z-look.z;
    eye.x+=dx*0.003;
    eye.y+=dy*0.003;
    eye.z+=dz*0.003;
    look.x+=dx*0.003;
    look.y+=dy*0.003;
    look.z+=dz*0.003;
}
void Camera::left(){
    Vector3 vUp(up.x,up.y,up.z);
    Vector3 vEye(eye.x-look.x,eye.y-look.y,eye.z-look.z);
    Vector3 left(vUp.cross(vEye));
    eye.x-=left.x*0.03;
    eye.y-=left.y*0.03;
    eye.z-=left.z*0.03;
    look.x-=left.x*0.03;
    look.y-=left.y*0.03;
    look.z-=left.z*0.03;
    
}
void Camera::right(){
    Vector3 vUp(up.x,up.y,up.z);
    Vector3 vEye(eye.x-look.x,eye.y-look.y,eye.z-look.z);
    Vector3 left(vUp.cross(vEye));
    eye.x+=left.x*0.03;
    eye.y+=left.y*0.03;
    eye.z+=left.z*0.03;
    look.x+=left.x*0.03;
    look.y+=left.y*0.03;
    look.z+=left.z*0.03;
}

void Camera::rotateLR(float du){
    eye_fi+=du*0.2;
    float vector_x = r*sin(eye_fi * Pi / 180.0);
    float vector_z = r*cos(eye_fi * Pi / 180.0);
    look.x=eye.x-vector_x;
    look.z=eye.z-vector_z;
    
}
void Camera::rotateUD(float du){
    eye_theta+=du*0.2;
    float vector_y = r*sin(eye_theta*Pi/180.0);
//    printf("before:centery:%f\n",look.y);
    look.y=eye.y-vector_y;
//    printf("vector y :%f\n",vector_y);
//    printf("after:centery:%f\n",look.y);
}



