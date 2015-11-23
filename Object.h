//
//  Object.h
//  VirtualObject
//
//  Created by mr.ji on 15/11/21.
//  Copyright (c) 2015年 mr.ji. All rights reserved.
//

#ifndef __VirtualObject__Object__
#define __VirtualObject__Object__

#include <string>
#include <fstream>
#include <iostream>
using namespace std;
//for parameter v
struct Vertex{
    float x,y,z;
};
//for parameter vt
struct Vt{
    float x,y;
};
//for parameter f
struct F{
    
};

class Object{
    Vertex *v;
    Vt *vt;
    F *f;
    int vertexNum;
public:
    int getVerNum();
    Vertex getVertex(int i);
    Vt getVt(int i );
    F getF(int i);
    void readFile(string fileName);
};

#endif /* defined(__VirtualObject__Object__) */
