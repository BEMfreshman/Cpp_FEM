#include "DofManager.h"
#include "Dof.h"

DofManager::DofManager()
{

}

DofManager::DofManager(int id_, int SPCsNum_) :id(id_), SPCsNum(SPCsNum)
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
	//从0开始
	if (id >= DOFMap.size())
	{
		return NULL;
	}
	else
	{
		map<DOFVar, DOF*>::const_iterator it;
		int iter = 0;
		for (it = DOFMap.begin(); it != DOFMap.end(); it++)
		{
			if (iter != i)
			{
				continue;
			}
			else
			{
				it->second;
			}
		}
	}
}

int DofManager::addDOF(DOF* dof,bool isVaild)
{
	//首先遍历寻找是否已经存在该自由度
	if (DOFMap.find(dof->getDOFVar()) == DOFMap.end())
	{
		dof->SetVaild(isVaild);
		DOFMap[dof->getDOFVar()] = dof;
		return 1;
	}
	else
	{
		return 0;
	}
}

int DofManager::deleteDOF(DOF* dof)
{
	map<DOFVar, DOF*>::iterator it;
	it = find(DOFMap.begin(), DOFMap.end(), dof->getDOFVar());

	if (it == DOFMap.end())
	{
		//不存在此点，返回0
		return 0;
	}
	else
	{

		DOFMap.erase(dof->getDOFVar());
		return 1;
	}
}


int DofManager::getDOFSize() const
{
	return DOFMap.size();
}


bool DofManager::findSPCValid(DOFVar DF)
{
	if (DOFMap.size() == 0)
	{
		return true;
	}
	else
	{
		return find(DOFMap.begin(), DOFMap.end(), DF)->second->getIsVaild();
	}
}