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
	//从0开始
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

int DofManager::addDOF(DOFVar dof,bool isVaild)
{
	//首先遍历寻找是否已经存在该自由度
	if (DOFMap.find(dof) == DOFMap.end())
	{
		DOFMap[dof] = (int)(isVaild == true);
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
		//不存在此点，返回0
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