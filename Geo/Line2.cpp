#include "Line2.h"
#include "vertex.h"
#include <iostream>

using namespace std;

Line2::Line2()
{

}

Line2::Line2(int ElementID, int MaterialId,
	ElementType eletype,
	int dim,
	const Eigen::MatrixXi& VertexIdArray) :
	Element(ElementId,MaterialId,eletype,dim,VertexIdArray)
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

int Line2::ComputeShapeFunction()
{
	int VertexNum = VertexIdArray.rows();
	//��Ԫ�϶���ĸ���

	int GaussPointNum = LocalGaussPoint.rows();
	//��˹��ĸ���

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

int Line2::ComputeTMatrix(int dim)
{
	//������ת����

	Eigen::Vector3d XBar(1, 0, 0);

	Eigen::Vector3d X;
	Vertex* First_Ver = VertexVec[0];
	Vertex* Second_Ver = VertexVec[1];

	X(0) = Second_Ver->GetX() - First_Ver->GetX();
	X(1) = Second_Ver->GetY() - First_Ver->GetY();
	X(2) = Second_Ver->GetZ() - First_Ver->GetZ();


	if (dim == 1)
	{
		//1ά�����
		double cosb = X.dot(XBar) / (X.norm()*XBar.norm());
		T.resize(4, 4);
		T.setZero();

		T(0, 0) = cosb;
		T(1, 1) = 1;
		T(2, 2) = cosb;
		T(3, 3) = 1;

		return 1;

	}
	else if (dim == 2)
	{
		double cosb = X.dot(XBar) / (X.norm()*XBar.norm());
		double angle = acos(cosb);

		double crossXBarX = XBar(0)*X(1) - XBar(1)*X(0);
		// >0 ����XBar��ʱ����ת��X�ĽǶ���С��3.1415926��
		// <0 �����3.1415926

		if (crossXBarX <0)
		{
			// <0
			angle -= 2 * 3.1415926;
		}
		
		double sinb = sin(angle);

		T.resize(6, 6);
		T.setZero();

		T(0, 0) = cosb;
		T(0, 1) = sinb;
		T(1, 0) = -sinb;
		T(1, 1) = cosb;
		T(2, 2) = 1;

		T(3, 3) = cosb;
		T(3, 4) = sinb;
		T(4, 3) = -sinb;
		T(4, 4) = cosb;
		T(5, 5) = 1;

		return 1;

	}
	else if (dim == 3)
	{
		return 0;
	}
	else
	{
		return 0;
	}
}

int Line2::ComputeForceMatrixOnEle(const map<int, Eigen::MatrixXd>& Pressure,
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
	Eigen::MatrixXd GPForceMatrix(DOFNumofEle, 1);

	ForceMatrix.setZero();
	GPForceMatrix.setZero();

	map<int, Eigen::MatrixXd>::const_iterator it = Pressure.begin();
	Eigen::MatrixXd LoadMatrix(Pressure.size(), it->second.cols());

	
	//һά��Ԫ
	int Counter = 0;
	for (it = Pressure.begin(); it != Pressure.end(); it++)
	{
		LoadMatrix.row(Counter) = it->second;
		Counter++;
	}

	cout << "LoadMatrix" << endl;
	cout << LoadMatrix << endl;

	Eigen::MatrixXd Jac;
	Eigen::MatrixXd EachGaussLoadMatrix(1, 3);

	if (dim == 1)
	{
		//һ�����ɶ�,x
		Eigen::MatrixXd EachGaussLoadMatrix_(1, 1);
		for (int i = 0; i < GaussPointNum; i++)
		{
			EachGaussLoadMatrix = N.row(i).transpose() * LoadMatrix;
			EachGaussLoadMatrix_(0, 0) = EachGaussLoadMatrix(0, 0);

			ComputeJacMatrix(i, Jac);

			GPForceMatrix.block(0, 0, DOFNumofEle / 2, 1) = EachGaussLoadMatrix_.transpose()* N.row(i)(0, 0);
			GPForceMatrix.block(DOFNumofEle / 2, 0, DOFNumofEle / 2, 1) = EachGaussLoadMatrix_.transpose()* N.row(i)(0, 1);

			ForceMatrix += GPForceMatrix * Jac.determinant() * GaussWeight[i];
		}

		//ForceMatrix *= (ElementLength - 0) / 2.0;

	}
	else if (dim == 2)
	{
		//�������ɶ�,x,y
		Eigen::MatrixXd EachGaussLoadMatrix_(1, 2);
		for (int i = 0; i < GaussPointNum; i++)
		{
			EachGaussLoadMatrix = N.row(i) * LoadMatrix;

			cout << "EachGaussLoadMatrix" << endl;
			cout << EachGaussLoadMatrix << endl;

			EachGaussLoadMatrix_(0, 0) = EachGaussLoadMatrix(0, 0);
			EachGaussLoadMatrix_(0, 1) = EachGaussLoadMatrix(0, 1);

			ComputeJacMatrix(i, Jac);

			/*cout << "Jac" << endl;
			cout << Jac << endl;*/

			GPForceMatrix.block(0, 0, DOFNumofEle / 2, 1) = EachGaussLoadMatrix_.transpose()* N.row(i)(0, 0);
			GPForceMatrix.block(DOFNumofEle / 2, 0, DOFNumofEle / 2, 1) = EachGaussLoadMatrix_.transpose()* N.row(i)(0, 1);

			cout << "GPForceMatrix" << endl;
			cout << GPForceMatrix << endl;

			ForceMatrix += GPForceMatrix * Jac.determinant() * GaussWeight[i];

			cout << "ForceMatrix" << endl;
			cout << ForceMatrix << endl;

			
		}

		/*
		ForceMatrix *= (ElementLength - 0) / 2.0;
		*/
	}
	else if (dim == 3)
	{
		//�������ɶ�,x,y,z
		Eigen::MatrixXd EachGaussLoadMatrix_(1, 3);
		for (int i = 0; i < GaussPointNum; i++)
		{
			EachGaussLoadMatrix = N.row(i).transpose() * LoadMatrix;
			EachGaussLoadMatrix_(0, 0) = EachGaussLoadMatrix(0, 0);
			EachGaussLoadMatrix_(0, 1) = EachGaussLoadMatrix(0, 1);
			EachGaussLoadMatrix_(0, 2) = EachGaussLoadMatrix(0, 2);

			ComputeJacMatrix(i, Jac);

			GPForceMatrix.block(0, 0, DOFNumofEle / 2, 1) = EachGaussLoadMatrix_.transpose()* N.row(i)(0, 0);
			GPForceMatrix.block(DOFNumofEle / 2, 0, DOFNumofEle / 2, 1) = EachGaussLoadMatrix_.transpose()* N.row(i)(0, 1);

			ForceMatrix += GPForceMatrix * Jac.determinant() * GaussWeight[i];
		}
		//ForceMatrix *= (ElementLength - 0) / 2.0;
	}

	std::cout << ForceMatrix << std::endl;
	

	ProduceValidTripleForF(ForceMatrix, tripList);

	
	return 1;
}

void Line2::ComputeJacMatrix(int GaussPointId, Eigen::MatrixXd& Jac)
{
	//�ڵȲ�������Ϊһά��Ԫ,����X����
	Eigen::MatrixXd Coord(2, 1);
	Eigen::MatrixXd EachPointCoord(1, 1);

	for (int i = 0; i < 2; i++)
	{
		Vertex* Ver = VertexVec[i];
		EachPointCoord(0, 0) = Ver->GetX();

		Coord.row(i) = EachPointCoord;
	}

	Jac = dNdxi.block(GaussPointId, 0, 1, 2)*Coord;

}