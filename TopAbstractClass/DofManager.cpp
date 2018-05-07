#include "DofManager.h"
#include "Dof.h"

DofManager::DofManager()
{

}

DofManager::DofManager(int id_, int SPCsNum_) :id(id_), SPCsNum(SPCsNum_)
{
	if (SPCsNum != 0)
	{
		int tmp = SPCsNum;
		while (tmp != 0)
		{
			SPCDOF.push_back((tmp % 10));
			tmp = tmp / 10;
		}

	}
}

DofManager::~DofManager()
{
	if (DOFMap.size() != 0)
	{
		for (map<DOFVar, DOF*>::iterator it = DOFMap.begin();
			it != DOFMap.end(); it++)
		{
			delete it->second;
			it->second = NULL;
		}
	}
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
				iter++;
				continue;
			}
			else
			{
				return it->second;
			}
		}
		return NULL;
	}
}

DOF* DofManager::getDOFById(DOFVar DF) const
{
	map<DOFVar, DOF*>::const_iterator it;
	it = DOFMap.find(DF);

	return (it == DOFMap.end() ? NULL : it->second);
}

int DofManager::addDOF(DOF* dof)
{
	//首先遍历寻找是否已经存在该自由度
	if (DOFMap.find(dof->getDOFVar()) == DOFMap.end())
	{
		DOFMap[dof->getDOFVar()] = dof;
		return 1;
	}
	else
	{
		return 0;
	}


	/*vector<DOF*>::iterator it;
	it = find(DOFVec.begin(), DOFVec.end(), dof);
	if (it != DOFVec.end())
	{
		return;
	}
	else
	{
		DOFVec.push_back(dof);
	}*/
}

int DofManager::deleteDOF(DOF* dof)
{
	map<DOFVar, DOF*>::iterator it;
	it = DOFMap.find(dof->getDOFVar());

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
	if (SPCDOF.size() == 0)
	{
		return true;
	}
	else
	{
		return find(SPCDOF.begin(), SPCDOF.end(), (int)DF) == SPCDOF.end();
	}
}

int DofManager::SetVaildDOFId(int& ValidDOFNum, int PerscribedDOFNum)
{
	for (map<DOFVar, DOF*>::iterator it = DOFMap.begin();
		it != DOFMap.end(); it++)
	{
		DOF* dof = it->second;
		if (dof->getIsVaild() == true)
		{
			dof->SetVaildTotalDOFId(ValidDOFNum++);
		}
		else
		{
			dof->SetVaildTotalDOFId(--PerscribedDOFNum);
		}
	}
	return 1;
}

int DofManager::getValidDOFIdAndIsValidArray(vector<int>& ValidDOFId, vector<int>& ValidArray) const
{
	for (map<DOFVar, DOF*>::const_iterator it = DOFMap.begin();
		it != DOFMap.end();
		it++)
	{
		DOF* dof = it->second;
		ValidDOFId.push_back(dof->getVaildTotalDOFId());
		ValidArray.push_back(dof->getIsVaild() == true ? 1 : 0);
	}
	return 1;
}
//int DofManager::SetSPC()
//{
//	if (DOFMap.size() == 0)
//	{
//		return 0;
//	}
//	else
//	{
//		for (int i = 0; i < SPCDOF.size(); i++)
//		{
//			map<DOFVar, DOF*>::iterator it = DOFMap.find((DOFVar)SPCDOF[i]);
//			if (it == DOFMap.end())
//			{
//				return 0;
//			}
//			else
//			{
//				it->second->
//			}
//		}
//		
//	}
//}