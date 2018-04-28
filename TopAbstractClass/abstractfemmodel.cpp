#include "abstractfemmodel.h"
#include "../Geo/vertex.h"
#include "Dof.h"
#include "abstractelement.h"
#include "Eigen/SparseCore"

#define EPS 1e-10


abstractFEMModel::abstractFEMModel(FEMinfo* FEMInformation_)
:FemInformation(FEMInformation_), ValidDOFNum(0), PerscribedDOFNum(0)
{
    
	
}

abstractFEMModel::~abstractFEMModel()
{
    
}

int abstractFEMModel::PreProcess()
{
	//前操作
	//为每个单元赋予材料属性、单元属性和点的指针
	//确定总的自由度个数，SPC的自由度直接删除，不计入总数

	if (FemInformation->FinallyCompulsorySet() == 0)
	{
		printf("单元Mat、EProp和Vertex指针设置失败\n");
		return 0;
	}

	
	int VertexNum = FemInformation->getVertexNum();
	for (int id = 1; id <= VertexNum; id++)
	{
		Vertex* Ver = FemInformation->getVertexById(id);
		if (Ver == NULL)
		{
			printf("警告：点的编号不连续，DOF编号可能出错\n");
			continue;
		}

		Ver->SetVaildDOFId(ValidDOFNum, PerscribedDOFNum);
	}


	if (ValidDOFNum == 0)
	{
		printf("自由度为0\n");
		return 0;
	}

	K.resize(ValidDOFNum, ValidDOFNum);
	M.resize(ValidDOFNum, ValidDOFNum);
	f.resize(ValidDOFNum, 1);
	return 1;
}

int abstractFEMModel::BuildKMatrix()
{
	//组建K矩阵
	typedef Eigen::Triplet<double> T;
	vector<T> tripleList;

	Eigen::MatrixXd EleStiffnessMatrix;
	int EleNum = FemInformation->getElementNum();
	for (int id = 1; id <= EleNum; id++)
	{
		Element* Ele = FemInformation->getElementById(id);

		Ele->GetSpecificMatrix(Stiffness, EleStiffnessMatrix);
		//计算单元刚度矩阵


		Eigen::VectorXi ValidTotalDOFIdArray;
		Eigen::VectorXi IsValidArray;

		Ele->GetValidDOFId(ValidTotalDOFIdArray, IsValidArray);

		for (int i = 0; i < ValidTotalDOFIdArray.size(); i++)
		{
			for (int j = 0; j < ValidTotalDOFIdArray.size(); j++)
			{
				if (abs(IsValidArray(i)) > EPS && abs(IsValidArray(j)) > EPS) 
					//IsValidArray(i) != 0 && IsValidArray(j) != 0
				{
					tripleList.push_back(T(ValidTotalDOFIdArray(i),
						ValidTotalDOFIdArray(j),
						EleStiffnessMatrix(i,j)));
				}
				else if (abs(IsValidArray(i)) < EPS && abs(IsValidArray(j)) > EPS)
					//IsValidArray(i) == 0 && IsValidArray(j) != 0
				{
					Ele->GetDOFInEleByTotalDOFId(ValidTotalDOFIdArray(i))
						->addresidualK(T(IsValidArray(j), 0, EleStiffnessMatrix(i, j)));
				}
				else 
					//IsValidArray(i) == 0 && IsValidArray(j) == 0
					//IsValidArray(i) != 0 && IsValidArray(j) == 0
				{
					continue;
				}
			}
		}
	}

	//组装K
	K.setFromTriplets(tripleList.begin(), tripleList.end());

	cout << "KMatrix" << endl;
	cout << K << endl;
	return 1;
}
