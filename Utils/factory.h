#ifndef FACTORY_H
#define FACTORY_H
#include <Eigen/Eigen>
#include <map>
#include "../TopAbstractClass/abstractelement.h"

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
    Vertex* CreateVertex(int VertexId,double x,double y);
    Vertex* CreateVertex(int VertexId,double x,double y,double z);

    Element* CreateElement(int ElementId,
                           int MaterialId,
                           Element::ElementType eletype,
                           Eigen::MatrixXi VertexIdArray);
    Element* CreateElement(int ElementId,
                           int MaterialId,
                           int EPropId,
                           Element::ElementType eletype,
                           Eigen::MatrixXi VertexIdArray);
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
    Mat* CreateMat(int MaterialId);
    //2017.10.21 Mat需要更多的创建方式

    EProp* CreateEProp(int EPropId);
    //创建一个单元截面属性

    Load* CreateLoad(int LoadId);
    //创建一个载荷

    Constraint* CreateConstraint(int ConstraintId);
    //创建一个约束
private:



};

#endif // FACTORY_H
