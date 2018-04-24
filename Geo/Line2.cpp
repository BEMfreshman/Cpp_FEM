#include "Line2.h"
#include "vertex.h"

Line2::Line2()
{

}

Line2::Line2(int ElementID, int MaterialId,
	Element::ElementType eletype,
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

Element* Line2::Clone() const
{
	return new Line2(*this);
}

int Line2::GetSpecificMatrix(SparseMatrixType SMT, Eigen::MatrixXd& ReturnMatrix)
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
	}
	else if (SFT == Hermite)
	{
		//Hermite形状函数
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
		double SecondXCoord = SecondOne->GetY();
		tmp(0) = FirstXCoord - SecondXCoord;

		double FirstYCoord = FirstOne->GetY();
		double SecondYCoord = SecondOne->GetY();
		tmp(1) = FirstYCoord - SecondYCoord;

		double FirstZCoord = FirstOne->GetZ();
		double SecondZCoord = SecondOne->GetZ();
		tmp(2) = FirstZCoord - SecondZCoord;

		
		ElementLength = tmp.squaredNorm();

		return 1;
	}
}