﻿#ifndef FACTORY_H
#define FACTORY_H
#include <Eigen/Eigen>
#include <map>
#include "../TopAbstractClass/abstractelement.h"
#include "../TopAbstractClass/DOFVar.h"

//class Vertex;
//class Element;
//class Mat;
//class EProp;
class Load;
class Constraint;


/*
 * 工厂类
 * 讲abstractreader类的派生类实例投给该类
 * 即可获得所有计算需要的类的实例
 */

class Factory
{
public:
    Factory();
    Vertex* CreateVertex(int VertexId,double x,double y,double z,int SPCsNum);

    Element* CreateElement(int ElementId,
                           int MaterialId,
                           ElementType eletype,
                           const Eigen::MatrixXi& VertexIdArray);
    Element* CreateElement(int ElementId,
                           int MaterialId,
                           int EPropId,
                           ElementType eletype,
                           const Eigen::MatrixXi& VertexIdArray);
/*
    Element* CreateElement(int ElementId,
                           Eigen::ArrayXi& VertexIdArray,
                           Eigen::ArrayXi& VertexConnect);
    //VertexIdArray指的是点Id的数组，表示由这些点组成了此Element
    //VertexConnect指的是点的连接方式，此处采用无向图的连接表示
    //VertexConnect是一个方阵，第i行的第j列元素为1，则代表PointIdArray
    //中的第i个点与第j个点存在连线
    Element* CreateElement(int Elementid,
                           int EPropid,
                           Eigen::ArrayXi& VertexIdArray,
                           Eigen::ArrayXi& VertexConnect);
*/
	Mat* CreateMat(int MaterialId, const std::string& LinearOrNot,
		const std::string& IsoOrNot, const std::map<std::string, double> PropNameAndPropValue,
		const std::string& DimAndMatStatus);
    //2017.10.21 Mat需要更多的创建方式

    EProp* CreateEProp(int EPropId,const std::string& ElementPropName,
		const std::map<std::string,double>& PropNameAndPropValue);
    //创建一个单元截面属性

    Load* CreateLoad(int LoadId,
		const Eigen::MatrixXi& NodeId,
		const Eigen::MatrixXd& Value);
    //创建一个载荷

	Load* CreateLoad(int LoadId, const std::string& LoadName,
		int ElementId,
		const Eigen::VectorXi& NodeId,
		const Eigen::MatrixXd& Value);

    Constraint* CreateConstraint(int ConstraintId,const std::string& ConstraintName,
		int NodeId,DOFVar DF,double Value);
    //创建一个约束
private:



};

#endif // FACTORY_H
