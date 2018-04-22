#ifndef ABSTRACTELEMENT_H
#define ABSTRACTELEMENT_H
#include <Eigen/Eigen>
#include "sparsematrixtype.h"

/* 抽象Element
 * 向下继承为
 * 点单元
 * 杆单元（二维，三维）
 * 梁单元（二维，三维）
 * 壳单元
 * 平面应变单元（三角形，四边形）
 * 平面应力单元（三角形，四边形）
 * 四面体单元
 * 六面体单元
 * ....
 */


class Vertex;
class EProp;
class Mat;

class Element
{
public: 
    enum ElementType
    {
        //等参单元形状
        Line2 = 1,             //线单元
        Line3,
        Triangle3,         //三角形
        Triangle4,
        Triangle6,
        Quadrilateral4,    //四边形
        Quadrilateral8,
        Quadrilateral9,
        Tetrahedron4,      //四面体
        Hexahedron8,       //六面体

        Truss,                //杆单元
        BeamEB2,              //欧拉——伯努利梁单元（2节点）
		BeamEB3,              //欧拉——伯努利梁单元（3节点）
		BeamT2,               //铁木辛柯梁单元（2节点）
		BeamT3,               //铁木辛柯梁单元（3节点）
        Shell                 //壳单元
    };

    Element();

    Element(int ElementId,
            int MaterialId,
            ElementType eletype,
            const Eigen::MatrixXi& VertexIdArray);
    Element(int ElementId,
            int MaterialId,
            int EPropId,
            ElementType eletype,
            const Eigen::MatrixXi& VertexIdArray);

    Element(const Element& that);
    Element& operator=(const Element& that);
    virtual Element* Clone() const = 0;


    virtual ~Element() = 0;
    //抽象类，本身不可被实例化

    int GetElementId() const;
    int GetEPropId() const;
    int GetMaterialId() const;
    const Eigen::MatrixXi& GetVertexIdArray() const;
    //Eigen::ArrayXXi& GetVertexConnect();

    void SetVertexCoord(Eigen::MatrixXd& VertexCoord);
    void SetEProp(EProp* EleProp);
    void SetMat(Mat* Material);

public:
    // 网格内高斯积分点的生成
    void GenerateGaussPoint(int Order);
    //Order代表积分阶次

public:
    virtual int GetSpecificMatrix(SparseMatrixType SMT,Eigen::MatrixXd& ReturnMatrix) = 0;

/*
 * 暂时不考虑边界单元的功能
public:
    // 作为边界单元的功能
    void GetBoundaryLoad();
*/

protected:
    int ElementId;
    int EPropId;         //单元属性Id
    int MatId;           //材料Id
    Eigen::MatrixXi VertexIdArray;
    //Eigen::ArrayXXi VertexConnect;
    //VertexIdArray指的是点Id的数组，表示由这些点组成了此Element
    //VertexConnect指的是点的连接方式，此处采用无向图的连接表示
    //VertexConnect是一个方阵，第i行的第j列元素为1，则代表PointIdArray
    //中的第i个点与第j个点存在连线


    /*
     * 注意此处的Id排列顺序并不是随意的
     * 总体编号的排列需要参照等参单元中顶点的排列
     *
     * 线性2点
     * 1-----------2
     *
     * 线性3点
     * 1-----2-----3
     *
     * 三角形3点
     *         3
     *        / \
     *       /   \
     *      1-----2
     *
     * 三角形4点
     *         3
     *        / \
     *       /   \
     *      /  4  \
     *     /       \
     *    1 ------- 2
     *
     * 三角形6点
     *         3
     *        / \
     *       /   \
     *      6     5
     *     /       \
     *    /         \
     *   1 ----4---- 2
     *
     * 四边形4点
     * 4-----------3
     * |           |
     * |           |
     * |           |
     * |           |
     * 1-----------2
     *
     * 四边形8点
     * 4-----7-----3
     * |           |
     * |           |
     * 8           6
     * |           |
     * |           |
     * 1-----5-----2
     *
     * 四边形9点
     * 4-----7-----3
     * |           |
     * |           |
     * 8     9     6
     * |           |
     * |           |
     * 1-----5-----2
     *
     * 四面体4点
     *         4
     *        /|\
     *       / | \
     *      /  |  \
     *     /   |   \
     *    1 ---|--- 3
     *       \ 2 /
     *
     * 六面体8点
     *                 8
     *              /    \
     *           /          \
     *        /                \
     *     5                     \
     *     |\                     7
     *     |   \                / |
     *     |     \     4    /     |
     *     |        \    /        |
     *     |           6          |
     *     1           |          |
     *      \          |          3
     *         \       |        /
     *           \     |     /
     *              \  |  /
     *
     *                 2
     */


    EProp* EleProp;
    Mat*   Material;

    Eigen::MatrixXd VertexCoord;
    //顶点坐标

    bool NeedGauss;
    ElementType EleType;
    //描述单元性质

    Eigen::MatrixXd LocalGaussPoint;
    //等参单元局部坐标下的高斯点坐标
    //用处：
    //1.形函数的生成



    std::vector<double> GaussWeight;
    //高斯点权重

    Eigen::MatrixXd N;
    //形函数

    Eigen::MatrixXd dNdxi;
    //形函数的导数



protected:
    void GenerateLoacalGaussPointAndWeight(int Order);
    void ComputeShapeFunction();
    //计算形函数



};

#endif // ABSTRACTELEMENT_H
