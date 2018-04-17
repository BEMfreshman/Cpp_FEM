#ifndef TRUSS_H
#define TRUSS_H
#include "../TopAbstractClass/abstractelement.h"

/*
 * 杆单元
 */

class Truss:public Element
{
public:
    Truss();
    Truss(int ElementId,
          int MaterialId,
          int EPropId,
          Element::ElementType eletype,
          Eigen::ArrayXXi VertexIdArray);

    ~Truss();

    Truss(const Truss& that);
    Truss& operator=(const Truss& that);

    Element* Clone() const;
};

#endif // TRUSS_H
