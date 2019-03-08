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
		//���غ�
		return 0;
	}
	else
	{
		Vertex* Ver = FEMInformation->getVertexById(NodeId);
		vector<int> tmpDOFId;         //��¼ȫ��DOFId
		vector<int> tmpDOFVarId;     //��¼�ֲ�DOFId

		Ver->getGlobalValidDOFId(tmpDOFId);
		Ver->getLocalDOFVarId(tmpDOFVarId);

		for (size_t i = 0; i < tmpDOFId.size(); i++)
		{
			tripleList.push_back(T_(tmpDOFId[i], 0, Value(0, tmpDOFVarId[i] - 1)));
			//���ɶȴ�1��ʼ���㣬����Ҫ-1
		}

		return 1;
	}
}

LoadType NodeLoad::getLoadType() const
{
	return LoadOnPoint;
}