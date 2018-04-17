#ifndef BUILDINKEYWORD_H
#define BUILDINKEYWORD_H

enum BuildinKeyWord
{
    //一级关键字，控制输入卡片
    AnalysisTypeKW,
    PointKW,
    ElementKW,
    MaterialKW,
    ElementPropKW,
    ConstraintKW,
    LoadKW,

    None, // 并不是关键字
};

//在某种输入卡片之下
//控制更小的输入项目

enum ElementKeyWord
{

    //Element项目下：
    Truss,
    Beam,
    Triangle,
    Quad,
    Shell,
    //Element项目可以后续添加
};


#endif // BUILDINKEYWORD_H
