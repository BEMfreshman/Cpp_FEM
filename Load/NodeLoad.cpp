#include "NodeLoad.h"
#include "../TopAbstractClass/feminfo.h"
#include "../Geo/vertex.h"

NodeLoad::NodeLoad(int id, int NodeId_,
	const Eigen::MatrixXd Value_) :Load(id), NodeId(NodeId_), Value(Value_)
{

}

NodeLoad::~NodeLoad()
{

}

int NodeLoad::ComputeForce(FEMinfo* FEMInformation, vector<T_>& tripleList)
{
	if (NodeId == 0 || Value.size() == 0)
	{
		//无载荷
		return 0;
	}
	else
	{
		Vertex* Ver = FEMInformation->getVertexById(NodeId);
		vector<int> tmpDOFId;         //记录全局DOFId
		vector<int> tmpDOFVarId;     //记录局部DOFId

		Ver->getGlobalValidDOFId(tmpDOFId);
		Ver->getLocalDOFVarId(tmpDOFVarId);

		for (size_t i = 0; i < tmpDOFId.size(); i++)
		{
			tripleList.push_back(T_(tmpDOFId[i], 0, Value(0, tmpDOFVarId[i] - 1)));
			//自由度从1开始计算，所以要-1
		}

		return 1;
	}
}

LoadType NodeLoad::getLoadType() const
{
	return LoadOnPoint;
}