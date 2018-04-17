#ifndef INPUTITEMNAME_H
#define INPUTITEMNAME_H

enum InputItemName
{
    //记录需要读出来的数据体
    Analysis_SolNum,
    Analysis_SolType,         //Sol的类型，2dPlaneStress,2dPlaneStrain,3d

    Vertex_Id,
    Vertex_CoordX,
    Vertex_CoordY,
    Vertex_CoordZ,
    Vertex_Coord,

    Element_Id,
    Element_Type,
    Element_VertexIdArray,     //组成Element的VertexId的编号
    Element_MatId,             //Element的材料编号
    Element_EPropId,           //Element的单元属性编号

    Mat_Id,
    Mat_LinearOrNot,           //线性还是非线性
    Mat_IsoOrNot,              //各向同性还是各向异性
    Mat_PropNameAndPropValue,

    EProp_Id,
    EProp_ElementName,         //单元属性名称 ---- Beam,Truss,Shell
    EProp_PropNameAndPropValue,

};



#endif // INPUTITEMNAME_H
