#include "point.h"

Point::Point(int ElementId,
             int MaterialId,
             int EPropId,
             ElementType eletype,
			 const Eigen::MatrixXi& VertexIdArray)
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

int Point::GetSpecificMatrix(SparseMatrixType SMT, vector<T_>& tripleList)
{
	return 0;
}

Element* Point::Clone() const
{
    return new Point(*this);
}

int Point::SetDOF(int dim)
{
	return 0;
}

void Point::GenerateLoacalGaussPointAndWeight(int Order)
{
	
}

int Point::ComputeShapeFunction(ShapeFunType SFT)
{
	return 0;
}

ElementType Point::GetElementType()
{
	return POINT;
}
