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
	//���õ���ɾ�����з�
	Vertex* Ver = FEMInfomation->getVertexById(NodeId);
	if (Ver == NULL)
	{
		printf("�߽���������ʱ��ȡVertex����\n");
		return 0;
	}

	//��ñ�Լ����DOF
	DOF* dof = Ver->getDOFById(DF);
	for (int i = 0; i < dof->getResidualKSize(); i++)
	{
		double NewValueInT_ = -((dof->getResidualK(i)).value() * Value); //���ֵĸ���
		int col = (dof->getResidualK(i)).col();
		int row = (dof->getResidualK(i)).row();

		tripleList.push_back(T_(row, col, NewValueInT_));
	}


}