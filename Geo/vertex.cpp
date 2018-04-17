#include "vertex.h"

Vertex::Vertex(int Id,double x,double y)
{
    this->Id = Id;
    this->x = x;
    this->y = y;
    this->z = 0.0;
}

Vertex::Vertex(int Id,double x,double y,double z)
{
    this->Id = Id;
    this->x = x;
    this->y = y;
    this->z = z;
}

Vertex::Vertex(const Vertex& vertex):Id(vertex.Id),
    x(vertex.x),y(vertex.y),z(vertex.z)
{
    //拷贝构造
}

Vertex& Vertex::operator =(const Vertex& that)
{
    if(&that != this)
    {
        //首先释放旧资源，这里没有需要delete的资源
        this->Id = that.Id;
        this->x = that.x;
        this->y = that.y;
        this->z = that.z;
    }
    return *this;
}

Vertex* Vertex::Clone() const
{
    return new Vertex(*this);
}

double Vertex::GetX()
{
    return x;
}

double Vertex::GetY()
{
    return y;
}

double Vertex::GetZ()
{
    return z;
}
