﻿#ifndef VERTEX_H
#define VERTEX_H
/*
 * 定点，用于组成Element
 */

#include "../TopAbstractClass/DofManager.h"

using namespace std;

class Vertex:public DofManager
{
public:
    Vertex(int Id,double x,double y,double z,int SPCsNum); // 三维点


    //Vertex(const Vertex& vertex);
    //拷贝构造

    //Vertex& operator=(const Vertex& vertex);

    //Vertex* Clone() const;


    double GetX() const;
    double GetY() const;
    double GetZ() const;


private:
    int Id;
	
    double x;
    double y;
    double z;
	
};

#endif // VERTEX_H
