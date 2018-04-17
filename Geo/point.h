#ifndef POINT_H
#define POINT_H

/*
 * 点单元
 */
#include "../TopAbstractClass/abstractelement.h"


class Point: public Element
{
public:
    Point();
    Point(int ElementId,
          int MaterialId,
          int EPropId,
          Element::ElementType eletype,
          Eigen::ArrayXXi VertexIdArray);

    Point(const Point& that);
    Point& operator=(const Point& that);

    Element* Clone() const;

    ~Point();
};

#endif // POINT_H
