#include "point.h"

Point::Point(int ElementId,
             int MaterialId,
             int EPropId,
             ElementType eletype,
             Eigen::ArrayXXi VertexIdArray)
            :Element(ElementId,MaterialId,EPropId,
                     eletype,VertexIdArray)
{

}

Point::Point()
{

}

Point::~Point()
{

}

Point::Point(const Point& that):Element(that)
{

}

Point& Point::operator =(const Point& that)
{
    if(this != &that)
    {
        Element::operator =(that);
        return *this;
    }
    else
    {
        return *this;
    }

}

Element* Point::Clone() const
{
    return new Point(*this);
}
