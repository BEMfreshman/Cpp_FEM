#ifndef __DOFMANAGER_H__
#define __DOFMANAGER_H__

//用于管理点的自由度
//点的自由度不仅跟维度有关，还跟点所在的单元类型有关
//例如：
//2d的平面四边形单元的每个点的自由度是2
//而2dbeam的自由度为3（x，y，theta）

//所以自由度的设定只在单元设置完成后进行
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
	DOF* getDOF(int i) const; //返回排在DOFVec中的第i个元素
	DOF* getDOFByDOFId(int id) const;   //根据DOFVec中每个DOF的Id，返回一个DOF*

	int addDOF(DOF* dof);         //增加一个DOF（添加到vec的末尾）
	int deleteDOF(int id);    //删除一个DOF


private:
	int findPosofDOF(DOF* dof) const;
	//如果找到则返回Pos，找不到则返回-1

	int findPosofDOF(int id) const;

private:
	int id;
	vector<DOF*> DOFVec;   //装载DOF的容器
	
};


#endif