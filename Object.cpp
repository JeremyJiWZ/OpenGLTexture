//
//  Object.cpp
//  VirtualObject
//
//  Created by mr.ji on 15/11/21.
//  Copyright (c) 2015年 mr.ji. All rights reserved.
//

#include "Object.h"
int Object::getVerNum(){
    return vertexNum;
}
Vertex Object::getVertex(int i){
    return v[i];
}
Vt Object::getVt(int i){
    return vt[i];
}
F Object::getF(int i){
    return f[i];
}
void Object::readFile(string fileName){
    ifstream file;
    file.open(fileName.c_str(),ios::in|ios::beg);
    if (!file.is_open()) {
        cout<<"error:file cannot be opened";
        exit(0);
    }
    //initialize
    vertexNum=0;
    char line[100];
    file.getline(line, 100);
    string strLine = line;
    while (!file.eof()) {
        file.getline(line, 100);
        
    }
    
}