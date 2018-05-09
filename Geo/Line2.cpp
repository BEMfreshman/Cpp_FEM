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
	//单元上顶点的个数

	int GaussPointNum = LocalGaussPoint.rows();
	//高斯点的个数

	if (SFT == Lagrange)
	{
		//拉格朗日形状函数

		N.resize(GaussPointNum, VertexNum);
		dNdxi.resize(GaussPointNum * 1/*线单元只有*/, VertexNum);


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
		//Hermite形状函数
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

	OneDimensionGPAndWeight(Order);      //生成一维的高斯点和权重值

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
	//计算单元的长度
	if (VertexVec.size() == 0)
	{
		printf("VertexVec为空\n");
		return 0;
	}
	else
	{
		if (VertexVec.size() > 2)
		{
			printf("2节点梁单元存储的点的个数大于2个");
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
	//计算旋转矩阵

	Eigen::Vector3d XBar(1, 0, 0);

	Eigen::Vector3d X;
	Vertex* First_Ver = VertexVec[0];
	Vertex* Second_Ver = VertexVec[1];

	X(0) = Second_Ver->GetX() - First_Ver->GetX();
	X(1) = Second_Ver->GetY() - First_Ver->GetY();
	X(2) = Second_Ver->GetZ() - First_Ver->GetZ();


	if (dim == 1)
	{
		//1维的情况
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
		// >0 则由XBar逆时针旋转至X的角度是小于3.1415926的
		// <0 则大于3.1415926

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