#include "quadelement.h"

QuadElement::QuadElement(int ElementId,
                         int MaterialId,
                         Element::ElementType eletype,
						 const Eigen::MatrixXi& VertexIdArray) :
    Element(ElementId,MaterialId,eletype,VertexIdArray)
{

}

QuadElement::QuadElement()
{

}

QuadElement::~QuadElement()
{

}

QuadElement::QuadElement(const QuadElement& that):Element(that)
{

}

QuadElement& QuadElement::operator =(const QuadElement& that)
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

Element* QuadElement::Clone() const
{
    return new QuadElement(*this);
}

int QuadElement::GetSpecificMatrix(SparseMatrixType SMT, Eigen::MatrixXd& ReturnMatrix)
{
	return 0;
}

int QuadElement::ComputeShapeFunction(ShapeFunType SFT)
{
	return 0;
}

void QuadElement::GenerateLoacalGaussPointAndWeight(int Order)
{

}

int QuadElement::ComputeStiffnessMatrix(Eigen::MatrixXd& matReturn)
{
	return 0;
}

int QuadElement::SetDOF(int dim)
{
	return 0;
}
