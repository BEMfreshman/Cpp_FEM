#include "truss.h"

Truss::Truss(int ElementId,
             int MaterialId,
             int EPropId,
             Element::ElementType eletype,
			 const Eigen::MatrixXi& VertexIdArray)
            :Line2(ElementId,MaterialId,
                     eletype,VertexIdArray)
{
	this->EPropId = EPropId;
}

Truss::Truss()
{

}

Truss::~Truss()
{

}

Truss::Truss(const Truss &that) :Line2(that)
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

int Truss::SetDOF(int dim)
{
	return 0;
}

int Truss::GetSpecificMatrix(SparseMatrixType SMT, Eigen::MatrixXd& ReturnMatrix)
{
	return 0;
}

int Truss::ComputeStiffnessMatrix(Eigen::MatrixXd& matReturn)
{
	//欧拉——伯努利梁
	//计算刚度矩阵
	return 0;
}

int Truss::ComputeMassMatrix(Eigen::MatrixXd& matReturn)
{
	return 0;
}