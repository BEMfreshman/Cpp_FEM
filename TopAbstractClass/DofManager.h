#ifndef __DOFMANAGER_H__
#define __DOFMANAGER_H__



//���ڹ��������ɶ�
//������ɶȲ�����ά���йأ����������ڵĵ�Ԫ�����й�
//���磺
//2d��ƽ���ı��ε�Ԫ��ÿ��������ɶ���2
//��2dbeam�����ɶ�Ϊ3��x��y��theta��

//�������ɶȵ��趨ֻ�ڵ�Ԫ������ɺ����
#include <map>
#include <vector>
#include "DOFVar.h"
#include "../TopAbstractClass/elementtype.h"
using namespace std;

class DOF;

class DofManager
{
public:
	DofManager();
	DofManager(int id,int SPCsNum);

	virtual ~DofManager();

	int getDofManagerid() const;
	DOF* getDOF(int i) const; //��������DOFVec�еĵ�i��Ԫ��
	DOF* getDOFById(DOFVar DF) const;
	int getDOFSize() const;        //����DOF�ĸ���

	int addDOF(DOF* dof);         //����һ��DOF����ӵ�vec��ĩβ��
	int deleteDOF(DOF* dof);    //ɾ��һ��DOF

	int SetVaildDOFId(int& ValidDOFNum,int& PerscribedDOFNum);

	int getValidDOFIdAndIsValidArray(vector<int>& ValidDOFId, vector<int>& ValidArray) const;

	int getGlobalValidDOFId(vector<int>& GlobalValidDOFId);
	int getLocalDOFVarId(vector<int>& LocalDOFVarId);

	int SetDOF(int dim, ElementType ET);

	void getAnsVec(vector<double>& ansVec);
protected:

	int id;
	int SPCsNum;

	map<DOFVar,DOF*> DOFMap;   

	//vector<DOF*> DOFVec;
	vector<int> SPCDOF;

	
protected:

	int SetSPC();

	bool findSPCValid(DOFVar DF);
	
};


#endif