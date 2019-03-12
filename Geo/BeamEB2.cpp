#include "BeamEB2.h"
#include "../Geo/vertex.h"
#include "../TopAbstractClass/Dof.h"
#include "../TopAbstractClass/abastractelementprop.h"
#include "../TopAbstractClass/abstractmaterial.h"
#include "../Load/PressureLoadOnLine.h"

#include <math.h>

BeamEB2::BeamEB2()
{

}

BeamEB2::BeamEB2(int ElementId,
	int MaterialId,
	int EPropId,
	ElementType eletype,
	int dim,
	const Eigen::MatrixXi& VertexIdArray) :Line2(ElementId, MaterialId,
	eletype, dim,VertexIdArray)
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
	vector<T_>& ReturnValue)
{
	//

	if (SMT == Stiffness)
	{
		ComputeStiffnessMatrix(ReturnValue);
		return 1;
	}
	else if (SMT == Mass)
	{
		ComputeMassMatrix(ReturnValue);
		return 1;
	}

	printf("Unknown SparseMatrixType\n");
	return 0;
}

int BeamEB2::ComputeStiffnessMatrix(vector<T_>& tripleList)
{
	//计算刚度矩阵

	Eigen::MatrixXd matReturn;
	Eigen::MatrixXd TmatReturnT;
	
	if (GetDOFNumofEle() == 0)
	{
		printf("The Num Of DOF of Ele is zeros\n");
		return 0;
	}

	matReturn.resize(DOFNumofEle, DOFNumofEle);
	matReturn.setZero();

	TmatReturnT.resize(DOFNumofEle, DOFNumofEle);
	TmatReturnT.setZero();


	if (dim == 1)
	{
		//一维

		if (EleProp->hasProp(Iz) == 0)
		{
			printf("Value of Iz is missing\n");
			return 0;
		}
		else if (Material->hasProp(E) == 0 && Material->hasProp(Ex) == 0
			&& Material->hasProp(Ey) == 0 && Material->hasProp(Ez) == 0)
		{
			printf("Value of E is missing\n");
			return 0;
		}
		else
		{
			ComputeElementLength();

			if (Material->IsIsoMat())
			{
				//各向同性材料
				double EVal,IzVal;
				if (Material->GetValue(E, &EVal) == 0)
				{
					printf("Value of E is missing\n");
					return 0;
				}

				if (EleProp->GetValue(Iz, &IzVal) == 0)
				{
					printf("Value of Iz is missing\n");
					return 0;
				}


				double Coeff = EVal*IzVal / (pow(ElementLength, 3));


				matReturn(0, 0) = 12.0;
				matReturn(0, 1) = 6 * ElementLength;
				matReturn(0, 2) = -12.0;
				matReturn(0, 3) = 6 * ElementLength;

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

				ComputeTMatrix(1);

				TmatReturnT = T.transpose()*matReturn*T;



				ProduceValidTriple(TmatReturnT, tripleList);

			}
		}
	}
	else if (dim == 2)
	{
		//2维梁

		if (EleProp->hasProp(Iz) == 0)
		{
			printf("Value of Iz is missing\n");
			return 0;
		}
		else if (EleProp->hasProp(Area) == 0)
		{
			printf("Value of Area is missing\n");
			return 0;
		}
		else if (Material->hasProp(E) == 0 && Material->hasProp(Ex) == 0
			&& Material->hasProp(Ey) == 0 && Material->hasProp(Ez) == 0)
		{
			printf("Value of E is missing\n");
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
					printf("Value of E is missing\n");
					return 0;
				}

				if (EleProp->GetValue(Iz, &IzVal) == 0)
				{
					printf("Value of Iz is missing\n");
					return 0;
				}

				if (EleProp->GetValue(Area, &AreaVal) == 0)
				{
					printf("Value of Area is missing\n");
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

				ComputeTMatrix(2);

				TmatReturnT = T.transpose()*matReturn*T;

				ProduceValidTriple(TmatReturnT, tripleList);

			}
		}
	}
	else if (dim == 3)
	{
		//三维梁
	}

	return 0;
}

int BeamEB2::ComputeMassMatrix(vector<T_>& tripleList)
{
	if (GetDOFNumofEle() == 0)
	{
		printf("The Number of DOF of Ele is zero\n");
		return 0;
	}

	Eigen::MatrixXd matReturn;
	Eigen::MatrixXd TmatReturnT;

	matReturn.resize(DOFNumofEle, DOFNumofEle);
	matReturn.setZero();

	TmatReturnT.resize(DOFNumofEle, DOFNumofEle);
	TmatReturnT.setZero();



	if (dim == 1)
	{
		//һά����Ԫ

		if (Material->hasProp(RHO) == 0)
		{
			printf("Value of RHO is missing\n");
			return 0;
		}
		
		if (EleProp->hasProp(Area) == 0)
		{
			printf("Value of Area is missing\n");
			return 0;
		}

		ComputeElementLength();

		double RHOVal, AreaVal;

		if (Material->GetValue(RHO, &RHOVal) == 0)
		{
			printf("Value of RHO is missing\n");
			return 0;
		}

		if (EleProp->GetValue(Area, &AreaVal) == 0)
		{
			printf("Value of Area is missing\n");
			return 0;
		}

		double Coeff = RHOVal*AreaVal*ElementLength / 420.0;

		matReturn(0, 0) = 156;
		matReturn(0, 1) = 22 * ElementLength;
		matReturn(0, 2) = 54;
		matReturn(0, 3) = -13 * ElementLength;

		matReturn(1, 0) = matReturn(0, 1);
		matReturn(1, 1) = 4 * pow(ElementLength, 2);
		matReturn(1, 2) = 13 * ElementLength;
		matReturn(1, 3) = -3 * pow(ElementLength, 2);

		matReturn(2, 0) = matReturn(0, 2);
		matReturn(2, 1) = matReturn(1, 2);
		matReturn(2, 2) = 156;
		matReturn(2, 3) = -22 * ElementLength;

		matReturn(3, 0) = matReturn(0, 3);
		matReturn(3, 1) = matReturn(1, 3);
		matReturn(3, 2) = matReturn(2, 3);
		matReturn(3, 3) = 4 * pow(ElementLength, 2);

		matReturn *= Coeff;

		ComputeTMatrix(1);

		TmatReturnT = T.transpose()*matReturn*T;


		ProduceValidTriple(TmatReturnT, tripleList);
	}
	else if (dim == 2)
	{
		//��ά����Ԫ

		if (Material->hasProp(RHO) == 0)
		{
			printf("ȱ���ܶ�\n");
			return 0;
		}

		if (EleProp->hasProp(Area) == 0)
		{
			printf("ȱ�ٽ������\n");
			return 0;
		}

		ComputeElementLength();

		double RHOVal, AreaVal;

		if (Material->GetValue(RHO, &RHOVal) == 0)
		{
			printf("δ�ܳ�ȡ���ܶ�ֵ\n");
			return 0;
		}

		if (EleProp->GetValue(Area, &AreaVal) == 0)
		{
			printf("δ�ܳ�ȡ�����\n");
			return 0;
		}

		double Coeff = RHOVal*AreaVal*ElementLength / 420.0;

		matReturn(0, 0) = 140;
		matReturn(0, 3) = 70;

		matReturn(1, 1) = 156;
		matReturn(1, 2) = 22 * ElementLength;
		matReturn(1, 4) = 54;
		matReturn(1, 5) = -13 * ElementLength;

		matReturn(2, 1) = matReturn(1, 2);
		matReturn(2, 2) = 4 * pow(ElementLength, 2);
		matReturn(2, 4) = 13 * ElementLength;
		matReturn(2, 5) = -3 * pow(ElementLength, 2);

		matReturn(3, 0) = matReturn(0, 3);
		matReturn(3, 3) = 140;

		matReturn(4, 1) = matReturn(1, 4);
		matReturn(4, 2) = matReturn(2, 4);
		matReturn(4, 4) = 156;
		matReturn(4, 5) = -22 * ElementLength;

		matReturn(5, 1) = matReturn(1, 5);
		matReturn(5, 2) = matReturn(2, 5);
		matReturn(5, 4) = matReturn(4, 5);
		matReturn(5, 5) = 4 * pow(ElementLength, 2);

		matReturn *= Coeff;

		ComputeTMatrix(2);

		TmatReturnT = T.transpose()*matReturn*T;


		ProduceValidTriple(matReturn, tripleList);
	}
	else if (dim == 3)
	{
		//3 dim
	}

	return 0;
}

int BeamEB2::SetDOF(int dim)
{
	return 0;
}

ElementType BeamEB2::GetElementType()
{
	return BEAMEB2;
}

int BeamEB2::ComputeShapeFunction()
{
	//Hermite插值
	ComputeElementLength();

	Line2::ComputeShapeFunction();
	//计算形函数
	dNdxi.setZero();

	Eigen::MatrixXd GaussPoint(LocalGaussPoint.rows(), LocalGaussPoint.cols());
	//�˴���GaussPoint����[0��ElementLength]����ֱ���ϵĸ�˹��ֲ�

	Eigen::MatrixXd ElementCoord(2, 1);
	ElementCoord << 0, ElementLength;
	for (int i = 0; i < LocalGaussPoint.rows(); i++)
	{
		GaussPoint.row(i) = N.row(i)* ElementCoord;
	}

	N.setZero();
	N.resize(GaussPoint.rows(),4);

	
	for (int i = 0; i < GaussPoint.rows(); i++)
	{
		double epsilon = (GaussPoint(i, 0) - 0) / ElementLength;
		N(i, 0) = 1 - 3 * pow(epsilon, 2) + 2 * pow(epsilon, 2);
		N(i, 1) = (epsilon - 2 * pow(epsilon, 2) + pow(epsilon, 3))*ElementLength;
		N(i, 2) = 3 * pow(epsilon, 2) - 2 * pow(epsilon, 3);
		N(i, 3) = (-pow(epsilon, 2) + pow(epsilon, 3))*ElementLength;
	}
	
	return 1;

}

int BeamEB2::ComputeForceMatrixOnEle(const map<int, Eigen::MatrixXd>& Pressure,
	const LoadType LT,
	vector<T_>& tripList)
{
	if (LT != LoadOnLine)
	{
		printf("�غ�ʩ������\n");
		return 0;
	}

	if (GetDOFNumofEle() == 0)
	{
		printf("�õ�Ԫδ���õ�Ԫ�ڵ�\n");
		return 0;
	}
	
	int Order = 6;
	GenerateLoacalGaussPointAndWeight(Order);
	
	int GaussPointNum = LocalGaussPoint.rows();

	ComputeShapeFunction();
	ComputeElementLength();

	Eigen::MatrixXd ForceMatrix(DOFNumofEle, 1);
	Eigen::MatrixXd TForceMatrix(DOFNumofEle, 1);

	ForceMatrix.setZero();
	TForceMatrix.setZero();

	if (dim == 1)
	{
		//һά��Ԫ
		double FP_y = 0, SP_y = 0;

		map<int, Eigen::MatrixXd>::const_iterator it;

		it = Pressure.find(VertexVec[0]->GetId());
		if (it == Pressure.end())
		{
			return 0;
		}
		else
		{
			FP_y = (it->second)(0, 1);
		}

		it = Pressure.find(VertexVec[1]->GetId());
		if (it == Pressure.end())
		{
			return 0;
		}
		else
		{
			SP_y = (it->second)(0, 1);
		}

		
		if (abs(FP_y - SP_y) < EPS)
		{
			//��������

			Eigen::MatrixXd Jac;
			double EachGaussLoad = FP_y;

			for (int i = 0; i < GaussPointNum; i++)
			{
				ComputeJacMatrix(i, Jac);
				ForceMatrix += EachGaussLoad * N.row(i).transpose() * Jac.determinant() *	GaussWeight[i];
			}

			//ForceMatrix *= (ElementLength - 0) / 2.0;

			cout << "ForceMatrix is " << endl;
			cout << ForceMatrix << endl;
			
		}
		else
		{
			//���Ժ���
		}

		ComputeTMatrix(dim);
		TForceMatrix = T.transpose()*ForceMatrix;

		ProduceValidTripleForF(TForceMatrix, tripList);

	}
	else if (dim == 2)
	{
		//二维梁单元
	}
	else if (dim == 3)
	{
		//三维梁单元
	}
}

