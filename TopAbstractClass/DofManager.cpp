#include "DofManager.h"
#include "Dof.h"

DofManager::DofManager()
{

}

DofManager::DofManager(int id_) :id(id_)
{

}

DofManager::~DofManager()
{

}

int DofManager::getid() const
{
	return id;
}

DOF* DofManager::getDOF(int i) const
{
	//��0��ʼ
	if (id >= DOFVec.size())
	{
		return NULL;
	}
	else
	{
		return DOFVec[id];
	}
}

DOF* DofManager::getDOFByDOFId(int id) const
{
	int Pos = findPosofDOF(id);
	if (Pos == -1)
	{
		return NULL;
	}
	else
	{
		return DOFVec[Pos];
	}
}

int DofManager::addDOF(DOF* dof)
{
	//���ȱ���Ѱ���Ƿ��Ѿ����ڸ����ɶ�
	if (findPosofDOF(dof) == -1)
	{
		DOFVec.push_back(dof);
		return 1;
	}
	else
	{
		return 0;
	}
}

int DofManager::deleteDOF(int id)
{
	if (findPosofDOF(id) == -1)
	{
		//�����ڴ˵㣬����0
		return 0;
	}
	else
	{
		vector<DOF*>::iterator it;
		for (it = DOFVec.begin(); it != DOFVec.end(); it++)
		{
			if ((*it)->getid() == id)
			{
				break;
			}
		}

		it = DOFVec.erase(it);
		return 1;
	}
}


int DofManager::findPosofDOF(DOF* dof) const
{
	for (int i = 0; i < DOFVec.size(); i++)
	{
		if (DOFVec[i]->getid() == dof->getid())
		{
			return i;
		}
	}

	return -1;
}

int DofManager::findPosofDOF(int id) const
{
	for (int i = 0; i < DOFVec.size(); i++)
	{
		if (DOFVec[i]->getid() == id)
		{
			return i;
		}
	}

	return -1;
}

int DofManager::getDOFSize() const
{
	return DOFVec.size();
}