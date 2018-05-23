#include "quadelement.h"
#include "vertex.h"
#include "../TopAbstractClass/abstractmaterial.h"

QuadElement::QuadElement(int ElementId,
                         int MaterialId,
                         ElementType eletype,
						 const Eigen::MatrixXi& VertexIdArray) :
    Element(ElementId,MaterialId,eletype,VertexIdArray)
{
	ComputeShapeFunction();
}

QuadElement::QuadElement()
{

}

QuadElement::~QuadElement()
{

}

QuadElement::QuadElement(const QuadElement& that):Element(that)
{

}

QuadElement& QuadElement::operator =(const QuadElement& that)
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

Element* QuadElement::Clone() const
{
    return new QuadElement(*this);
}

int QuadElement::GetSpecificMatrix(SparseMatrixType SMT, vector<T_>& tripleList)
{
	return 0;
}

int QuadElement::ComputeShapeFunction()
{
	int VertexNum = VertexIdArray.rows();
	//单元顶点的个数

	int GaussPointNum = LocalGaussPoint.rows();
	//高斯点的个数

	
	//拉格朗日形函数
	N.resize(GaussPointNum, VertexNum);
	dNdxi.resize(GaussPointNum * 2/*平面单元，2个自由度*/,
		VertexNum);
		
	for (int i = 0; i < GaussPointNum; i++)
	{
		Eigen::MatrixXd EachGaussPoint(1, 2);
		Eigen::MatrixXd EachGaussPointShapeFunction(1, VertexNum);

		EachGaussPoint = LocalGaussPoint.row(i);

		double xi = EachGaussPoint(0, 0);
		double eta = EachGaussPoint(0, 1);

		EachGaussPointShapeFunction(0, 0) = 0.25*(1 - xi)*(1 - eta);
		EachGaussPointShapeFunction(0, 1) = 0.25*(1 + xi)*(1 - eta);
		EachGaussPointShapeFunction(0, 2) = 0.25*(1 + xi)*(1 + eta);
		EachGaussPointShapeFunction(0, 3) = 0.25*(1 - xi)*(1 + eta);

		N.row(i) = EachGaussPointShapeFunction;

		Eigen::MatrixXd EachGaussPointdNdxi(2, VertexNum);

		EachGaussPointdNdxi(0, 0) = 0.25*(-(1 - eta));
		EachGaussPointdNdxi(0, 1) = 0.25*(1 - eta);
		EachGaussPointdNdxi(0, 2) = 0.25*(1 + eta);
		EachGaussPointdNdxi(0, 3) = 0.25*(-(1 + eta));

		EachGaussPointdNdxi(1, 0) = 0.25*(-(1 - xi));
		EachGaussPointdNdxi(1, 1) = 0.25*(-(1 + xi));
		EachGaussPointdNdxi(1, 2) = 0.25*(1 + xi);
		EachGaussPointdNdxi(1, 3) = 0.25*(1 - xi);

		dNdxi.row(i * 2) = EachGaussPointdNdxi.row(0);
		dNdxi.row(i * 2 + 1) = EachGaussPointdNdxi.row(1);
	}
	return 0;
}

void QuadElement::GenerateLoacalGaussPointAndWeight(int Order)
{
	int dim = 2;
	LocalGaussPoint.resize(Order*Order, dim);
	GaussWeight.reserve(Order*Order);
	int i, j;
	int counter = 0;

	double xCoord = 0.0;
	double yCoord = 0.0;

	Eigen::MatrixXd EachGaussPoint(1, dim);
	EachGaussPoint.setZero(1, dim);

	double EachGaussWeight;

	for (i = 0; i < Order; i++)
	{
		xCoord = GaussPointOneDimension[i];
		EachGaussPoint(0, 0) = xCoord;
		for (j = 0; j < Order; j++)
		{
			yCoord = GaussPointOneDimension[j];
			EachGaussPoint(0, 1) = yCoord;

			LocalGaussPoint.row(counter) = EachGaussPoint;
			counter++;

			EachGaussWeight = WeightOneDimension[i] * WeightOneDimension[j];
			GaussWeight.push_back(EachGaussWeight);
		}
	}
}

int QuadElement::ComputeStiffnessMatrix(vector<T_>& ReturnValue)
{
	//B*D*B*J*h dxideta(-1 -> 1) (-1 -> 1)

	Eigen::MatrixXd Jac;      //雅各比矩阵
	Eigen::MatrixXd Bmat;
	Eigen::MatrixXd Dmat;

	Eigen::MatrixXd Ke(8,8);

	Material->ComputeMatrix(DMatrix, Dmat);

	for (int i = 0; i < LocalGaussPoint.size(); i++)
	{
		ComputeBMatrix(i, Bmat);
		ComputeJacMatrix(i, Jac);
		Ke += Bmat.transpose()*Dmat*Bmat*Jac.determinant()*GaussWeight[i];
	}

	ProduceValidTriple(Ke, ReturnValue);

	return 0;
}

int QuadElement::SetDOF(int dim)
{
	return 0;
}

ElementType QuadElement::GetElementType()
{
	return QUADRILATERAL4;
}

int QuadElement::ComputeBMatrix(int GaussPointId,Eigen::MatrixXd& Bmat)
{
	// [dN/dxi 0    ....;
    //  0     dN/deta    ....;
    // dN/deta dN/dxi    ....]

	int VertexNum = VertexIdArray.rows();
	//单元顶点的个数

	Bmat.resize(3, 2 * VertexNum);

	for (int i = 0; i < VertexNum; i++)
	{
		Bmat(0, i * 2) = dNdxi(GaussPointId*2, i * 2);
		Bmat(2, i * 2 + 1) = dNdxi(GaussPointId * 2, i * 2);

		Bmat(1, i * 2 + 1) = dNdxi(GaussPointId * 2 + 1, i * 2);
		Bmat(2, i * 2) = dNdxi(GaussPointId * 2 + 1, i * 2);
	}
	return 1;
}

void QuadElement::ComputeJacMatrix(int GaussPointId, Eigen::MatrixXd& Jac)
{
	//求雅各比矩阵

	Eigen::MatrixXd Coord(4, 2);
	Eigen::MatrixXd EachPointCoord(1, 2);

	for (int i = 0; i < 4; i++)
	{
		Vertex* Ver = VertexVec[i];
		EachPointCoord(0, 0) = Ver->GetX();
		EachPointCoord(0, 1) = Ver->GetY();

		Coord.row(i) = EachPointCoord;
	}

	Jac = dNdxi.block(GaussPointId * 2, 0, 2, 4)*Coord;

}

int QuadElement::ComputeMassMatrix(vector<T_>& ReturnValue)
{
	return 0;
}

int QuadElement::ComputeForceMatrixOnEle(const map<int, Eigen::MatrixXd>& Pressure, vector<T_>& tripList)
{
	return 0;
}

