#ifndef __DOFMANAGER_H__
#define __DOFMANAGER_H__

//���ڹ��������ɶ�
//������ɶȲ�����ά���йأ����������ڵĵ�Ԫ�����й�
//���磺
//2d��ƽ���ı��ε�Ԫ��ÿ��������ɶ���2
//��2dbeam�����ɶ�Ϊ3��x��y��theta��

//�������ɶȵ��趨ֻ�ڵ�Ԫ������ɺ����
#include <vector>
using namespace std;

class DOF;

class DofManager
{
public:
	DofManager();
	DofManager(int id);

	virtual ~DofManager();

	int getid() const;
	DOF* getDOF(int i) const; //��������DOFVec�еĵ�i��Ԫ��
	DOF* getDOFByDOFId(int id) const;   //����DOFVec��ÿ��DOF��Id������һ��DOF*
	int getDOFSize() const;        //����DOF�ĸ���

	int addDOF(DOF* dof);         //����һ��DOF����ӵ�vec��ĩβ��
	int deleteDOF(int id);    //ɾ��һ��DOF

	

protected:
	int findPosofDOF(DOF* dof) const;
	//����ҵ��򷵻�Pos���Ҳ����򷵻�-1

	int findPosofDOF(int id) const;

private:
	int id;
	vector<DOF*> DOFVec;   //װ��DOF������
	
};


#endif