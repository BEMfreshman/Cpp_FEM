#include "abstractmaterial.h"

/* 材料类最上层的抽象类，
 * 描述所有材料可以提供的方法
 */

Mat::Mat()
{

}
Mat::~Mat()
{

}

int Mat::GetValue(MatVar SMP, double *Value)
{
    std::map<MatVar,double>::iterator it;
    it = MatPropd.find(SMP);
    if(it != MatPropd.end())
    {
        //找到了
        *Value = it->second;
        return 1;
    }
    else
    {
        //未找到
        *Value = 0.0;
        return 0;
    }
}

int Mat::GetValue(MatVar SMP,int *Value)
{
    std::map<MatVar,int>::iterator it;
    it = MatPropi.find(SMP);
    if(it != MatPropi.end())
    {
        //找到了
        *Value = it->second;
        return 1;
    }
    else
    {
        *Value = 0;
        return 0;
    }
}


int Mat::GetValue(MatVar SMP, Eigen::ArrayXXd &Value)
{
    std::map<MatVar,Eigen::ArrayXXd>::iterator it;
    it = MatPropdarray.find(SMP);
    if(it != MatPropdarray.end())
    {
        //找到了
        Value = it->second;
        return 1;
    }
    else
    {
        Value.resize(1,1);
        return 0;
    }
}

int Mat::GetValue(MatVar SMP, Eigen::ArrayXXi &Value)
{
    std::map<MatVar,Eigen::ArrayXXi>::iterator it;
    it = MatPropiarray.find(SMP);
    if(it != MatPropiarray.end())
    {
        //找到了
        Value = it->second;
        return 1;
    }
    else
    {
        Value.resize(1,1);
        return 0;
    }
}
