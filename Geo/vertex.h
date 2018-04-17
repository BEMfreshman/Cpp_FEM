#ifndef VERTEX_H
#define VERTEX_H
/*
 * 定点，用于组成Element
 */

class Vertex
{
public:
    Vertex(int Id,double x,double y); // 二维点
    Vertex(int Id,double x,double y,double z); // 三维点


    Vertex(const Vertex& vertex);
    //拷贝构造

    Vertex& operator=(const Vertex& vertex);

    Vertex* Clone() const;


    double GetX();
    double GetY();
    double GetZ();

private:
    int Id;
    double x;
    double y;
    double z;
};

#endif // VERTEX_H
