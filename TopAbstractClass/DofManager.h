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
using namespace std;

class DOF;

class DofManager
{
public:
	DofManager();
	DofManager(int id,int SPCsNum);

	virtual ~DofManager();

	int getid() const;
	DOF* getDOF(int i) const; //��������DOFVec�еĵ�i��Ԫ��
	int getDOFSize() const;        //����DOF�ĸ���

	int addDOF(DOF* dof,bool isVaild);         //����һ��DOF����ӵ�vec��ĩβ��
	int deleteDOF(DOF* dof);    //ɾ��һ��DOF

	

protected:

	int id;
	int SPCsNum;

	map<DOFVar,DOF*> DOFMap;   //װ��DOF��Map���ڶ�����ʾ�Ƿ���Ч

	
protected:

	bool findSPCValid(DOFVar DF);
	
};


#endif