#ifndef __DOFMANAGER_H__
#define __DOFMANAGER_H__



//用于管理点的自由度
//点的自由度不仅跟维度有关，还跟点所在的单元类型有关
//例如：
//2d的平面四边形单元的每个点的自由度是2
//而2dbeam的自由度为3（x，y，theta）

//所以自由度的设定只在单元设置完成后进行
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
	DOF* getDOF(int i) const; //返回排在DOFVec中的第i个元素
	int getDOFSize() const;        //返回DOF的个数

	int addDOF(DOF* dof,bool isVaild);         //增加一个DOF（添加到vec的末尾）
	int deleteDOF(DOF* dof);    //删除一个DOF

	

protected:

	int id;
	int SPCsNum;

	map<DOFVar,DOF*> DOFMap;   //装载DOF的Map，第二个表示是否有效

	
protected:

	bool findSPCValid(DOFVar DF);
	
};


#endif