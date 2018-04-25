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

DOFVar DofManager::getDOF(int i) const
{
	//��0��ʼ
	if (id >= DOFMap.size())
	{
		return UNK;
	}
	else
	{
		map<DOFVar, int>::const_iterator it;
		int iter = 0;
		for (it = DOFMap.begin(); it != DOFMap.end(); it++)
		{
			if (iter != i)
			{
				continue;
			}
			else
			{
				it->first;
			}
		}
	}
}

int DofManager::addDOF(DOFVar dof)
{
	//���ȱ���Ѱ���Ƿ��Ѿ����ڸ����ɶ�
	if (findPosofDOF(dof) == -1)
	{
		DOFMap[dof] = 1;
		return 1;
	}
	else
	{
		return 0;
	}
}

int DofManager::deleteDOF(DOFVar dof)
{
	map<DOFVar, int>::iterator it;
	it = find(DOFMap.begin(), DOFMap.end(), dof);

	if (it == DOFMap.end())
	{
		//�����ڴ˵㣬����0
		return 0;
	}
	else
	{

		DOFMap.erase(dof);
		return 1;
	}
}


int DofManager::getDOFSize() const
{
	return DOFMap.size();
}