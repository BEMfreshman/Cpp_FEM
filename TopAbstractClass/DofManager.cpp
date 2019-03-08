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
			it->second = nullptr;
		}
	}
}

int DofManager::getDofManagerid() const
{
	return id;
}

DOF* DofManager::getDOF(int i) const
{
	//
	if (id >= DOFMap.size())
	{
		return nullptr;
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
		return nullptr;
	}
}

DOF* DofManager::getDOFById(DOFVar DF) const
{
	map<DOFVar, DOF*>::const_iterator it;
	it = DOFMap.find(DF);

	return (it == DOFMap.end() ? nullptr : it->second);
}

int DofManager::addDOF(DOF* dof)
{
	//添加DOF
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
		//�����ڴ˵㣬����0
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

int DofManager::SetVaildDOFId(int& ValidDOFNum, int& PerscribedDOFNum)
{
	//for (map<DOFVar, DOF*>::iterator it = DOFMap.begin();
	//	it != DOFMap.end(); it++)
	//{
	//	DOF* dof = it->second;
	//	if (dof->getIsVaild() == true)
	//	{
	//		dof->SetVaildTotalDOFId(ValidDOFNum++);
	//	}
	//	else
	//	{
	//		dof->SetVaildTotalDOFId(--PerscribedDOFNum);
	//	}
	//}

	vector<DOFVar> DOFVarVec = { u, v, w, tx, ty, tz };
	for (int i = 0; i < DOFVarVec.size(); i++)
	{
		DOFVar EachDF = DOFVarVec[i];
		map<DOFVar, DOF*>::iterator it = DOFMap.find(EachDF);
		if (it != DOFMap.end())
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


int DofManager::getGlobalValidDOFId(vector<int>& GlobalValidDOFId)
{
	for (map<DOFVar, DOF*>::const_iterator it = DOFMap.begin();
		it != DOFMap.end();
		it++)
	{
		DOF* dof = it->second;
		if(dof->getIsVaild())
		{
			GlobalValidDOFId.push_back(dof->getVaildTotalDOFId());
		}
	}
	return 1;
}

int DofManager::getLocalDOFVarId(vector<int>& LocalValidDOFId)
{
	for (map<DOFVar, DOF*>::const_iterator it = DOFMap.begin();
		it != DOFMap.end();
		it++)
	{
		DOF* dof = it->second;
		if(dof->getIsVaild())
		{
			LocalValidDOFId.push_back((int)dof->getDOFVar());
		}
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

int DofManager::SetDOF(int dim, ElementType ET)
{

	if (dim == 1)
	{
		if (ET == BEAMEB2)
		{
			DOF* dof_v = new DOF(1, findSPCValid(v), v);
			DOF* dof_tx = new DOF(2, findSPCValid(tz), tz);

			addDOF(dof_v);
			addDOF(dof_tx);
		}
	}
	else if (dim == 2)
	{
		if (ET == BEAMEB2)
		{
			DOF* dof_u = new DOF(1, findSPCValid(u), u);
			DOF* dof_v = new DOF(2, findSPCValid(v), v);
			DOF* dof_tx = new DOF(3, findSPCValid(tz), tz);

			addDOF(dof_u);
			addDOF(dof_v);
			addDOF(dof_tx);
		}
		else if (ET == QUADRILATERAL4 || ET == QUADRILATERAL8 ||
			ET == QUADRILATERAL9)
		{
			DOF* dof_u = new DOF(1, findSPCValid(u), u);
			DOF* dof_v = new DOF(2, findSPCValid(v), v);

			addDOF(dof_u);
			addDOF(dof_v);
		}
	}
	return 1;
}

void DofManager::getAnsVec(vector<double>& ansVec)
{
	map<DOFVar, DOF*>::iterator it;
	vector<DOFVar> DFVec = { u, v, w, tx, ty, tz };

	for (int i = 0; i < DFVec.size(); i++)
	{
		it = DOFMap.find(DFVec[i]);
		if (it != DOFMap.end())
		{
			ansVec.push_back(it->second->getAns());
		}
	}
}