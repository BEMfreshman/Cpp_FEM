#include "DiricheletBC.h"
#include "../TopAbstractClass/feminfo.h"
#include "../Geo/vertex.h"
#include "../TopAbstractClass/DofManager.h"
#include "../TopAbstractClass/Dof.h"
#include "../TopAbstractClass/DOFVar.h"


DirichletBC::DirichletBC(int id, int NodeId, DOFVar DF, double Value) 
:Constraint(id,NodeId,DF,Value)
{
	BCT = Dirichelet;
}

DirichletBC::~DirichletBC()
{

}

BCType DirichletBC::getBCType() const
{
	return BCT;
}

int DirichletBC::ModifyForceMatrix(FEMinfo* FEMInfomation, std::vector<T_>& tripleList)
{
	//采用的是删除行列法
	Vertex* Ver = FEMInfomation->getVertexById(NodeId);
	if (Ver == NULL)
	{
		printf("边界条件处理时抽取Vertex有误\n");
		return 0;
	}

	//获得被约束的DOF
	DOF* dof = Ver->getDOFById(DF);
	for (int i = 0; i < dof->getResidualKSize(); i++)
	{
		double NewValueInT_ = -((dof->getResidualK(i)).value() * Value); //数字的负数
		int col = (dof->getResidualK(i)).col();
		int row = (dof->getResidualK(i)).row();

		tripleList.push_back(T_(row, col, NewValueInT_));
	}


}