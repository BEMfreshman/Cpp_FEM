#ifndef __DOFMANAGER_H__
#define __DOFMANAGER_H__

#include "DOFVar.h"

//���ڹ��������ɶ�
//������ɶȲ�����ά���йأ����������ڵĵ�Ԫ�����й�
//���磺
//2d��ƽ���ı��ε�Ԫ��ÿ��������ɶ���2
//��2dbeam�����ɶ�Ϊ3��x��y��theta��

//�������ɶȵ��趨ֻ�ڵ�Ԫ������ɺ����
#include <map>
using namespace std;

class DofManager
{
public:
	DofManager();
	DofManager(int id);

	virtual ~DofManager();

	int getid() const;
	DOFVar getDOF(int i) const; //��������DOFVec�еĵ�i��Ԫ��
	int getDOFSize() const;        //����DOF�ĸ���

	int addDOF(DOFVar dof,bool isVaild);         //����һ��DOF����ӵ�vec��ĩβ��
	int deleteDOF(DOFVar dof);    //ɾ��һ��DOF

	

protected:

	int id;
	map<DOFVar,int> DOFMap;   //װ��DOF��Map���ڶ�����ʾ�Ƿ���Ч
	
};


#endif