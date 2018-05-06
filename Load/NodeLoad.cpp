#include "NodeLoad.h"
#include "../TopAbstractClass/feminfo.h"
#include "../Geo/vertex.h"

NodeLoad::NodeLoad(int id, const Eigen::MatrixXi& NodeId,
	const Eigen::MatrixXd Value) :Load(id,NodeId,Value)
{

}

NodeLoad::~NodeLoad()
{

}

int NodeLoad::ComputeForce(FEMinfo* FEMInformation, vector<T_>& tripleList)
{
	if (NodeId.size() == 0 || Value.size() == 0)
	{
		//无载荷
		return 1;
	}
	else if (NodeId.size() != 1)
	{
		printf("数据体不正常\n");
		return 0;
	}
	else
	{
		int id = NodeId(0,0);
		Vertex* Ver = FEMInformation->getVertexById(id);
		vector<int> tmpDOFId;

		for (int i = 0; i < Ver->getDOFSize(); i++)
		{
			DOF* dof = Ver->getDOF(i);
			tmpDOFId.push_back(dof->getVaildTotalDOFId());
		}

		for (size_t i = 0; i < tmpDOFId.size(); i++)
		{
			tripleList.push_back(T_(tmpDOFId[i], 0, Value[i]));
		}
		return 1;
	}
}