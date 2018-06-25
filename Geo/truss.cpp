﻿#include "truss.h"

Truss::Truss(int ElementId,
             int MaterialId,
             int EPropId,
             ElementType eletype,
			 int dim,
			 const Eigen::MatrixXi& VertexIdArray)
            :Line2(ElementId,MaterialId,
                     eletype,dim,VertexIdArray)
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

int Truss::GetSpecificMatrix(SparseMatrixType SMT,
	const LoadType LT, 
	vector<T_>& tripleList)
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

ElementType Truss::GetElementType()
{
	return TRUSS;
}