#include "linearstaticmodel.h"
#include "../TopAbstractClass/Dof.h"
#include "../TopAbstractClass/abstractelement.h"
#include "../TopAbstractClass/abstractload.h"
#include "../TopAbstractClass/abstractconstraint.h"

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
