#include "truss.h"

Truss::Truss(int ElementId,
             int MaterialId,
             int EPropId,
             Element::ElementType eletype,
			 const Eigen::MatrixXi& VertexIdArray)
            :Element(ElementId,MaterialId,EPropId,
                     eletype,VertexIdArray)
{

}

Truss::Truss()
{

}

Truss::~Truss()
{

}

Truss::Truss(const Truss &that):Element(that)
{

}

Truss& Truss::operator =(const Truss& that)
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

Element* Truss::Clone() const
{
    return new Truss(*this);
}
