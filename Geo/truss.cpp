#include "truss.h"
#include "../Geo/vertex.h"
#include "../TopAbstractClass/Dof.h"
#include "../TopAbstractClass/abastractelementprop.h"
#include "../TopAbstractClass/abstractmaterial.h"

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
	if (SMT == Stiffness)
	{
		ComputeStiffnessMatrix(tripleList);
		return 1;
	}
	else if (SMT == Mass)
	{
		ComputeMassMatrix(tripleList);
		return 1;
	}
	printf("不可识别的SparseMatrixType\n");
	return 0;
}

int Truss::ComputeStiffnessMatrix(vector<T_>& tripleList)
{
	//计算刚度矩阵

	Eigen::MatrixXd matReturn;
	Eigen::MatrixXd TmatReturnT;

	if (GetDOFNumofEle() == 0)
	{
		printf("该单元未设置单元节点\n");
		return 0;
	}

	matReturn.resize(DOFNumofEle, DOFNumofEle);
	matReturn.setZero();

	TmatReturnT.resize(DOFNumofEle, DOFNumofEle);
	TmatReturnT.setZero();

	if (dim == 1)
	{
		if (EleProp->hasProp(Area) == 0)
		{
			printf("Area不存在\n");
			return 0;
		}
		else if (Material->hasProp(E) == 0 && Material->hasProp(Ex) == 0
			&& Material->hasProp(Ey) == 0 && Material->hasProp(Ez) == 0)
		{
			printf("不存在E\n");
			return 0;
		}
		else
		{
			ComputeElementLength();
			if (Material->IsIsoMat())
			{
				double EVal, AreaVal;
				if (Material->GetValue(E, &EVal) == 0)
				{
					printf("未能抽取到E\n");
					return 0;
				}

				if (EleProp->GetValue(Area, &AreaVal) == 0)
				{
					printf("未能抽取到Area\n");
					return 0;
				}

				double Coeff = EVal*AreaVal / ElementLength;

				matReturn(0, 0) = 1;
				matReturn(0, 1) = -1;
				matReturn(1, 0) = -1;
				matReturn(1, 1) = 1;

				matReturn *= Coeff;

				ComputeTMatrix(1);

				TmatReturnT = T.transpose() * matReturn * T;
			
				ProduceValidTriple(TmatReturnT, tripleList);
			}
		}
	}


	return 0;
}

int Truss::ComputeMassMatrix(vector<T_>& tripleList)
{
	//计算质量矩阵
	return 0;
}

ElementType Truss::GetElementType()
{
	return TRUSS;
}