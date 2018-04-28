#ifndef ABSTRACTELEMENT_H
#define ABSTRACTELEMENT_H
#include <Eigen/Eigen>
#include "elementtype.h"
#include "sparsematrixtype.h"
#include "ShapeFunction.h"

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
class DOF;

class Element
{
public: 
    

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
	int GetDOFNumofEle();
	//const Eigen::MatrixXi GetAllDOF();


    void SetVertex(Vertex* vertex);
    void SetEProp(EProp* EleProp);
    void SetMat(Mat* Material);
	virtual int SetDOF(int dim) = 0;         //设置自由度，根据各单元不同而不同
	virtual ElementType GetElementType() = 0;

	int GetVertexInEleNum() const;  //获得单元中点的数目
	Vertex* GetVertexInEle(int i) const;
	DOF* GetDOFInEleByTotalDOFId(int TotalDOFId) const;

	void GetValidDOFId(Eigen::VectorXi& ValidTotalDOFIdArray, Eigen::VectorXi& IsValidArray);
public:
    // 网格内高斯积分点的生成
	// 所有的网格都需要高斯积分点，即使是beam和truss,也需要
	// 使用GaussPoint组装分布力形成阵列载荷矩阵
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

	std::vector<Vertex*> VertexVec;

	int DOFNumofEle;

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

	std::vector<double> GaussPointOneDimension;
	std::vector<double> WeightOneDimension;



protected:
    virtual void GenerateLoacalGaussPointAndWeight(int Order) = 0;
    virtual int ComputeShapeFunction(ShapeFunType SFT) = 0;
    //计算形函数

protected:
	void OneDimensionGPAndWeight(int Order);



};

#endif // ABSTRACTELEMENT_H
