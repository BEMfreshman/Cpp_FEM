﻿#include "quadelement.h"
#include "Line2.h"
#include "vertex.h"
#include "../TopAbstractClass/abstractmaterial.h"
#include <iostream>

QuadElement::QuadElement(int ElementId,
                         int MaterialId,
                         ElementType eletype,
						 int dim,
						 const Eigen::MatrixXi& VertexIdArray) :
    Element(ElementId,MaterialId,eletype,dim,VertexIdArray)
{
	int Order = 2;
	GenerateLoacalGaussPointAndWeight(Order);
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
	return 1;
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
	return 1;
}

void QuadElement::GenerateLoacalGaussPointAndWeight(int Order)
{

	LocalGaussPoint.resize(Order*Order, dim);
	GaussWeight.reserve(Order*Order);
	OneDimensionGPAndWeight(Order);


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
	Ke.setZero();

	Material->ComputeMatrix(DMatrix, Dmat);


	

	for (int i = 0; i < LocalGaussPoint.rows(); i++)
	{
		cout << "LoadGaussPoint" << endl;
		cout << LocalGaussPoint.row(i) << endl;


		ComputeJacMatrix(i, Jac);
		ComputeBMatrix(i, Jac,Bmat);
		
		Ke += Bmat.transpose()*Dmat*Bmat*Jac.determinant()*GaussWeight[i];

		cout << "Bmat" << endl;
		cout << Bmat << endl;

		cout << "Dmat" << endl;
		cout << Dmat << endl;

		cout << "Jac" << endl;
		cout << Jac << endl;

		

		cout << "Bmat.transpose()*Dmat*Bmat*Jac.determinant()*GaussWeight[i]" << endl;
		cout << Bmat.transpose()*Dmat*Bmat*Jac.determinant()*GaussWeight[i] << endl;

		cout << "Ke" << endl;
		cout << Ke << endl;

		cout << endl;
		cout << endl;
		cout << endl;
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

int QuadElement::ComputeBMatrix(int GaussPointId,
	const Eigen::MatrixXd& Jac,
	Eigen::MatrixXd& Bmat)
{
	// [dN/dxi 0    ....;
    //  0     dN/deta    ....;
    // dN/deta dN/dxi    ....]

	int VertexNum = VertexIdArray.rows();
	//单元顶点的个数

	Bmat.resize(3, 2 * VertexNum);
	Bmat.setZero();

	cout << "dNdxi\n" << endl;
	cout << dNdxi << endl;

	Eigen::MatrixXd dNdxi_Each(2, 1);
	Eigen::MatrixXd dNdx_Each(2, 1);
	Eigen::MatrixXd InvJac(Jac.rows(), Jac.cols());

	InvJac(0, 0) = Jac(1, 1);
	InvJac(1, 1) = Jac(0, 0);
	InvJac(1, 0) = -Jac(1, 0);
	InvJac(0, 1) = -Jac(0, 1);

	InvJac *= 1 / Jac.determinant();


	for (int i = 0; i < VertexNum; i++)
	{

		dNdxi_Each(0, 0) = dNdxi(GaussPointId * 2, i);
		dNdxi_Each(1, 0) = dNdxi(GaussPointId * 2 + 1, i);

		//计算公式《有限单元法基础及MATLAB编程》P195
		//将形函数对局部坐标的偏导数转为对全局坐标的偏导数

		dNdx_Each = InvJac * dNdxi_Each;



		Bmat(0, i * 2) = dNdx_Each(0,0);
		Bmat(2, i * 2 + 1) = dNdx_Each(0, 0);

		Bmat(1, i * 2 + 1) = dNdx_Each(1, 0);
		Bmat(2, i * 2) = dNdx_Each(1, 0);
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

int QuadElement::ComputeForceMatrixOnEle(const map<int, Eigen::MatrixXd>& Pressure,
	const LoadType LT,
	vector<T_>& tripList)
{
	//《有限元方法基础教程》第三版 P314

	if (GetDOFNumofEle() == 0)
	{
		printf("该单元未设置单元节点\n");
		return 0;
	}

	int Order = 6;

	if (LT == LoadOnLine)
	{
		Eigen::MatrixXi LineVertexIdArray(Pressure.size(), 1);

		int Counter = 0;
		vector<Vertex*> VertextmpVec;
		for (map<int, Eigen::MatrixXd>::const_iterator it = Pressure.begin();
			it != Pressure.end();
			it++)
		{
			int NodeId = it->first;
			LineVertexIdArray(Counter, 0) = NodeId;

			Counter++;
		}

		Element* LineEle = CreateLine2Element(LineVertexIdArray);


		LineEle->ComputeForceMatrixOnEle(Pressure, LT, tripList);
		delete LineEle;
	}

	return 1;
}


Element* QuadElement::CreateLine2Element(const Eigen::MatrixXi& LineVertexIdArray)
{
	vector<Vertex*> VertextmpVec;
	Element* subEle = new Line2(++subEleCounter, MatId, LINE2, dim, LineVertexIdArray);
	

	for (int i = 0; i < LineVertexIdArray.rows(); i++)
	{
		Vertex* Ver = GetVertexInEleById(LineVertexIdArray(i, 0));
		if (Ver != nullptr)
		{
			VertextmpVec.push_back(Ver);
		}
	}

	for (int i = 0; i < VertextmpVec.size(); i++)
	{
		subEle->SetVertex(VertextmpVec[i]);
	}

	return subEle;

}

