#include "BeamEB2.h"
#include "../TopAbstractClass/abastractelementprop.h"
#include "../TopAbstractClass/abstractmaterial.h"

BeamEB2::BeamEB2()
{

}

BeamEB2::BeamEB2(int ElementId,
	int MaterialId,
	int EPropId,
	Element::ElementType eletype,
	const Eigen::MatrixXi& VertexIdArray) :Line2(ElementId, MaterialId,
	eletype, VertexIdArray)
{
	this->EPropId = EPropId;
}

BeamEB2::~BeamEB2()
{

}

BeamEB2::BeamEB2(const BeamEB2 &that) :Line2(that)
{

}

BeamEB2& BeamEB2::operator=(const BeamEB2& that)
{
	if (this != &that)
	{
		Element::operator= (that);
		return *this;
	}
	else
	{
		return *this;
	}
}

Element* BeamEB2::Clone() const
{
	return new BeamEB2(*this);
}

int BeamEB2::GetSpecificMatrix(SparseMatrixType SMT,
	Eigen::MatrixXd& ReturnMatrix)
{
	//计算单元刚度矩阵或者单元质量矩阵
	return 0;
}

int BeamEB2::ComputeStiffnessMatrix(Eigen::MatrixXd& matReturn)
{
	//欧拉——伯努利梁
	//计算刚度矩阵

	//通过点的自由度，确定刚度矩阵的大小
	
	if (GetDOFNumofEle() == 0)
	{
		printf("该单元未设置单元节点\n");
		return 0;
	}

	matReturn.resize(DOFNumofEle, DOFNumofEle);
	matReturn.setZero();


	if (DOFNumofEle == 4)
	{
		//一维梁单元

		if (EleProp->hasProp(Iz) == 0)
		{
			printf("Iz不存在");
			return 0;
		}
		else if (Material->hasProp(E) == 0 && Material->hasProp(Ex) == 0
			&& Material->hasProp(Ey) == 0 && Material->hasProp(Ez) == 0)
		{
			printf("不存在E");
			return 0;
		}
		else
		{
			ComputeElementLength();

			if (Material->IsIsoMat() == 1)
			{
				//各向同性材料
				double EVal,IzVal;
				if (Material->GetValue(E, &EVal) == 0)
				{
					printf("未能抽取到E\n");
					return 0;
				}

				if (EleProp->GetValue(Iz, &IzVal) == 0)
				{
					printf("未能抽取到Iz\n");
					return 0;
				}


				double Coeff = EVal*IzVal / (pow(ElementLength, 3));

				matReturn(0, 0) = 12.0;
				matReturn(0, 1) = 6 * ElementLength;
				matReturn(0, 2) = -12.0;
				matReturn(0, 3) = -6 * ElementLength;

				matReturn(1, 0) = matReturn(0, 1);
				matReturn(1, 1) = 4 * pow(ElementLength, 2);
				matReturn(1, 2) = -6 * ElementLength;
				matReturn(1, 3) = 2 * pow(ElementLength, 2);

				matReturn(2, 0) = matReturn(0, 2);
				matReturn(2, 1) = matReturn(1, 2);
				matReturn(2, 2) = 12;
				matReturn(2, 3) = -6 * ElementLength;

				matReturn(3, 0) = matReturn(0, 3);
				matReturn(3, 1) = matReturn(1, 3);
				matReturn(3, 2) = matReturn(2, 3);
				matReturn(3, 3) = 4 * pow(ElementLength, 2);

				matReturn *= Coeff;

			}
		}
	}
	else if (DOFNumofEle == 6)
	{
		//二维梁单元

		if (EleProp->hasProp(Iz) == 0)
		{
			printf("Iz不存在");
			return 0;
		}
		else if (EleProp->hasProp(Area) == 0)
		{
			printf("Area不存在");
			return 0;
		}
		else if (Material->hasProp(E) == 0 && Material->hasProp(Ex) == 0
			&& Material->hasProp(Ey) == 0 && Material->hasProp(Ez) == 0)
		{
			printf("不存在E");
			return 0;
		}
		else
		{
			ComputeElementLength();
			if (Material->IsIsoMat() == 1)
			{
				//各向同性材料
				double EVal, IzVal, AreaVal;
				if (Material->GetValue(E, &EVal) == 0)
				{
					printf("未能抽取到E\n");
					return 0;
				}

				if (EleProp->GetValue(Iz, &IzVal) == 0)
				{
					printf("未能抽取到Iz\n");
					return 0;
				}

				if (EleProp->GetValue(Area, &AreaVal) == 0)
				{
					printf("未能抽取到Area\n");
					return 0;
				}

				matReturn(0, 0) = EVal*AreaVal / ElementLength;
				matReturn(0, 3) = -EVal*AreaVal / ElementLength;

				matReturn(1, 1) = 12 * EVal*IzVal / pow(ElementLength, 3);
				matReturn(1, 2) = 6 * EVal*IzVal / pow(ElementLength, 2);
				matReturn(1, 4) = -12 * EVal*IzVal / pow(ElementLength, 3);
				matReturn(1, 5) = 6 * EVal*IzVal / pow(ElementLength, 2);

				matReturn(2, 1) = 6 * EVal*IzVal / pow(ElementLength, 2);
				matReturn(2, 2) = 4 * EVal*IzVal / ElementLength;
				matReturn(2, 4) = -6 * EVal*IzVal / pow(ElementLength, 2);
				matReturn(2, 5) = 2 * EVal*IzVal / ElementLength;

				matReturn(3, 0) = matReturn(0, 3);
				matReturn(3, 3) = EVal*AreaVal / ElementLength;

				matReturn(4, 1) = matReturn(1, 4);
				matReturn(4, 2) = matReturn(2, 4);
				matReturn(4, 4) = 12 * EVal*IzVal / pow(ElementLength, 3);
				matReturn(4, 5) = -6 * EVal*IzVal / pow(ElementLength, 2);

				matReturn(5, 1) = matReturn(1, 5);
				matReturn(5, 2) = matReturn(2, 5);
				matReturn(5, 4) = matReturn(4, 5);
				matReturn(5, 5) = 4 * EVal*IzVal / ElementLength;

			}
		}
	}
	else if (DOFNumofEle == 12)
	{
		//三维梁单元
	}

	return 0;
}

int BeamEB2::ComputeMassMatrix(Eigen::MatrixXd& matReturn)
{
	return 0;
}

int BeamEB2::SetDOF(int dim)
{
	return 0;
}

