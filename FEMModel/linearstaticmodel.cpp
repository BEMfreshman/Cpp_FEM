#include "linearstaticmodel.h"
#include "../TopAbstractClass/Dof.h"
#include "../TopAbstractClass/abstractelement.h"
#include "../TopAbstractClass/abstractload.h"
#include "../TopAbstractClass/abstractconstraint.h"
#include "../Geo/vertex.h"

LinearStaticModel::LinearStaticModel(FEMinfo* FEMInformation)
:abstractFEMModel(FEMInformation)
{

}

LinearStaticModel::~LinearStaticModel()
{

}

void LinearStaticModel::Solve()
{
	PreProcess();
	BuildKMatrix();
	BuildfMatrix();

	Eigen::SparseLU<Eigen::SparseMatrix<double>> solver;
	solver.compute(K);
	if (solver.info() != Eigen::Success)
	{
		printf("求解(分解时)失败\n");
		return;
	}

	ansVector = solver.solve(f);
	if (solver.info() != Eigen::Success)
	{
		printf("求解(计算时)失败\n");
		return;
	}

	/*-----------将解存入自由度的ans变量中-----------------*/
	for (int i = 0; i < ValidDOFNum; i++)
	{
		DOF* dof = FemInformation->getDOFByTotalDOFId(i);
		dof->SetAns(ansVector(i));
	}

	for (int i = 1; i <= FemInformation->getConstraintNum(); i++)
	{
		Constraint* ct = FemInformation->getConstraintById(i);
		if (ct->getBCType() == Dirichelet)
		{
			int NodeId = ct->getNodeId();
			DOFVar DFV = ct->getDOFVar();
			double Value = ct->getValue();

			Vertex* Ver = FemInformation->getVertexById(NodeId);
			DOF* dof = Ver->getDOFById(DFV);
			dof->SetAns(Value);
		}
	}

	vector<double> ansVec;
	for (int i = 1; i <= FemInformation->getVertexNum(); i++)
	{
		Vertex* Ver = FemInformation->getVertexById(i);
		Ver->getAnsVec(ansVec);
	}

	ansVector.resize(ansVec.size());

	for (int i = 0; i < ansVec.size(); i++)
	{
		ansVector(i) = ansVec[i];
	}
}

int LinearStaticModel::BuildKMatrix()
{
	//组建K矩阵
	typedef Eigen::Triplet<double> T;
	vector<T> tripleList;

	Eigen::MatrixXd EleStiffnessMatrix;
	int EleNum = FemInformation->getElementNum();
	for (int id = 1; id <= EleNum; id++)
	{
		Element* Ele = FemInformation->getElementById(id);

		Ele->GetSpecificMatrix(Stiffness, tripleList);
		//计算单元刚度矩阵


		//Eigen::VectorXi ValidTotalDOFIdArray;
		//Eigen::VectorXi IsValidArray;

		//Ele->GetValidDOFId(ValidTotalDOFIdArray, IsValidArray);

		//for (int i = 0; i < ValidTotalDOFIdArray.size(); i++)
		//{
		//	for (int j = 0; j < ValidTotalDOFIdArray.size(); j++)
		//	{
		//		if (abs(IsValidArray(i)) > EPS && abs(IsValidArray(j)) > EPS) 
		//			//IsValidArray(i) != 0 && IsValidArray(j) != 0
		//		{
		//			tripleList.push_back(T(ValidTotalDOFIdArray(i),
		//				ValidTotalDOFIdArray(j),
		//				EleStiffnessMatrix(i,j)));
		//		}
		//		else if (abs(IsValidArray(i)) < EPS && abs(IsValidArray(j)) > EPS)
		//			//IsValidArray(i) == 0 && IsValidArray(j) != 0
		//		{
		//			Ele->GetDOFInEleByTotalDOFId(ValidTotalDOFIdArray(i))
		//				->addresidualK(T(IsValidArray(j), 0, EleStiffnessMatrix(i, j)));
		//		}
		//		else 
		//			//IsValidArray(i) == 0 && IsValidArray(j) == 0
		//			//IsValidArray(i) != 0 && IsValidArray(j) == 0
		//		{
		//			continue;
		//		}
		//	}
		//}
	}

	//组装K
	K.setFromTriplets(tripleList.begin(), tripleList.end());

	cout << "KMatrix" << endl;
	cout << K << endl;
	return 1;
}

int LinearStaticModel::BuildfMatrix()
{
	//组建f矩阵
	typedef Eigen::Triplet<double> T;
	vector<T> tripleList;

	int LoadNum = FemInformation->getLoadNum();
	for (int i = 1; i <= LoadNum; i++)
	{
		Load* ld = FemInformation->getLoadById(i);
		ld->ComputeForce(FemInformation, tripleList);
	}

	int ConstraintNum = FemInformation->getConstraintNum();
	for (int i = 1; i <= ConstraintNum; i++)
	{
		Constraint* ct = FemInformation->getConstraintById(i);
		ct->ModifyForceMatrix(FemInformation, tripleList);
	}

	//组装f
	f.setFromTriplets(tripleList.begin(), tripleList.end());

	cout << "fMatrix" << endl;
	cout << f << endl;


	return 1;
}

int LinearStaticModel::BuildMMatrix()
{
	return 0;
}
