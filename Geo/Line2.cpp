#include "Line2.h"
#include "vertex.h"

Line2::Line2()
{

}

Line2::Line2(int ElementID, int MaterialId,
	ElementType eletype,
	const Eigen::MatrixXi& VertexIdArray) :
	Element(ElementId,MaterialId,eletype,VertexIdArray)
{

}

Line2::~Line2()
{

}

Line2::Line2(const Line2& that) :Element(that)
{

}

Line2& Line2::operator =(const Line2& that)
{
	if (this != &that)
	{
		Element::operator =(that);
		return *this;
	}
	else
	{
		return *this;
	}

}

ElementType Line2::GetElementType()
{
	return LINE2;
}

Element* Line2::Clone() const
{
	return new Line2(*this);
}

int Line2::GetSpecificMatrix(SparseMatrixType SMT, vector<T_>& tripleList)
{
	return 0;
}

int Line2::SetDOF(int dim)
{
	return 0;
}

int Line2::ComputeShapeFunction(ShapeFunType SFT)
{
	int VertexNum = VertexIdArray.rows();
	//��Ԫ�϶���ĸ���

	int GaussPointNum = LocalGaussPoint.rows();
	//��˹��ĸ���

	if (SFT == Lagrange)
	{
		//����������״����

		N.resize(GaussPointNum, VertexNum);
		dNdxi.resize(GaussPointNum * 1/*�ߵ�Ԫֻ��*/, VertexNum);


		for (int i = 0; i < GaussPointNum; i++)
		{
			Eigen::MatrixXd EachGaussPoint(1, 1);
			Eigen::MatrixXd EachGaussPointShapeFunction(1, VertexNum);

			EachGaussPoint = LocalGaussPoint.row(i);

			double xi = EachGaussPoint(0, 0);
			EachGaussPointShapeFunction(0, 0) = (1 - xi) / 2.0;
			EachGaussPointShapeFunction(0, 1) = (1 + xi) / 2.0;
			N.row(i) = EachGaussPointShapeFunction;


			Eigen::MatrixXd EachGaussPointdNdxi(1, VertexNum);

			EachGaussPointdNdxi(0, 0) = -1.0 / 2.0;
			EachGaussPointdNdxi(0, 1) = 1.0 / 2.0;
			dNdxi.row(i) = EachGaussPointdNdxi;

		}
		return 1;
	}
	else if (SFT == Hermite)
	{
		//Hermite��״����
		return 0;
	}
	else
	{
		return 0;
	}
}


void Line2::GenerateLoacalGaussPointAndWeight(int Order)
{
	if (GaussPointOneDimension.size() != 0 || WeightOneDimension.size() != 0)
	{
		std::vector<double>().swap(GaussPointOneDimension);
		std::vector<double>().swap(WeightOneDimension);
	}

	if (GaussWeight.size() != 0)
	{
		std::vector<double>().swap(GaussWeight);
	}

	OneDimensionGPAndWeight(Order);      //����һά�ĸ�˹���Ȩ��ֵ

	LocalGaussPoint.resize(Order, 1);
	double EachGaussWeight;

	for (int i = 0; i < Order; i++)
	{
		LocalGaussPoint(i, 0) = GaussPointOneDimension[i];
		GaussWeight.push_back(WeightOneDimension[i]);
	}
}


int Line2::ComputeStiffnessMatrix(Eigen::MatrixXd& matReturn)
{
	return 0;
}

int Line2::ComputeElementLength()
{
	//���㵥Ԫ�ĳ���
	if (VertexVec.size() == 0)
	{
		printf("VertexVecΪ��\n");
		return 0;
	}
	else
	{
		if (VertexVec.size() > 2)
		{
			printf("2�ڵ�����Ԫ�洢�ĵ�ĸ�������2��");
		}

		Vertex* FirstOne = VertexVec[0];
		Vertex* SecondOne = VertexVec[1];

		Eigen::Vector3d tmp;

		double FirstXCoord = FirstOne->GetX();
		double SecondXCoord = SecondOne->GetX();
		tmp(0) = FirstXCoord - SecondXCoord;

		double FirstYCoord = FirstOne->GetY();
		double SecondYCoord = SecondOne->GetY();
		tmp(1) = FirstYCoord - SecondYCoord;

		double FirstZCoord = FirstOne->GetZ();
		double SecondZCoord = SecondOne->GetZ();
		tmp(2) = FirstZCoord - SecondZCoord;

		
		ElementLength = tmp.norm();

		return 1;
	}
}