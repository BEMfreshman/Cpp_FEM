﻿#include "abstractmaterial.h"

/* 材料类最上层的抽象类，
 * 描述所有材料可以提供的方法
 */

Mat::Mat(int id)
{
	this->id = id;
	/*matcate = MatCategory::None;
	mattype = MatType::None;
	matstatus = MatStatus::None;*/
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

//int Mat::GetValue(MatVar SMP,int *Value)
//{
//    std::map<MatVar,int>::iterator it;
//    it = MatPropi.find(SMP);
//    if(it != MatPropi.end())
//    {
//        //找到了
//        *Value = it->second;
//        return 1;
//    }
//    else
//    {
//        *Value = 0;
//        return 0;
//    }
//}


int Mat::GetValue(MatVar SMP, Eigen::MatrixXd &Value)
{
	std::map<MatVar, Eigen::MatrixXd>::iterator it;
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

int Mat::SetValue(const map<string, double>& PropNameAndValue)
{
	map<string, double>::const_iterator it;

	if (PropNameAndValue.size() == 0)
	{
		return 0;
	}

	for (it = PropNameAndValue.begin(); it != PropNameAndValue.end(); it++)
	{
		MatVar matvar;
		if (it->first == "E")
		{
			matvar = E;
		}
		else if (it->first == "Nu")
		{
			matvar = Nu;
		}
		else if (it->first == "G")
		{
			matvar = G;
		}
		else if (it->first == "RHO")
		{
			matvar = RHO;
		}
		else if (it->first == "Ex")
		{
			matvar = Ex;
		}
		else if (it->first == "Ey")
		{
			matvar = Ey;
		}
		else if (it->first == "Ez")
		{
			matvar = Ez;
		}
		else if (it->first == "Gx")
		{
			matvar = Gx;
		}
		else if (it->first == "Gy")
		{
			matvar = Gy;
		}
		else if (it->first == "Gz")
		{
			matvar = Gz;
		}
		else if (it->first == "Nuxy")
		{
			matvar = Nuxy;
		}
		else if (it->first == "Nuxz")
		{
			matvar = Nuxz;
		}
		else if (it->first == "Nuyz")
		{
			matvar = Nuyz;
		}

		__SetValue(matvar, it->second);
	}
	return 1;
}

int Mat::SetDimAndMatStatus(const string& str)
{
	if (str.find("1d") != string::npos)
	{
		dim = 1;
		return 1;
	}
	if (str.find("2d") != string::npos)
	{
		dim = 2;
		if (str.find("PlaneStrain") != string::npos)
		{
			matstatus = PlaneStrain;
		}
		else if (str.find("PlaneStress") != string::npos)
		{
			matstatus = PlaneStress;
		}
		return 1;
	}
	else if (str.find("3d") != string::npos)
	{
		dim = 3;
		return 1;
	}
	else
	{
		printf("未检索到维度\n");
		return 0;
	}
}


int Mat::__SetValue(MatVar SMP, double Value)
{
	//首先检查是否存在此SMP
	if (hasProp(SMP) == 1)
	{
		//存在
		std::map<MatVar, double>::iterator it = MatPropd.find(SMP);
		it->second = Value;
		return 1;
	}
	else
	{
		//不存在
		MatPropd.insert(make_pair(SMP, Value));
		return 1;
	}
	
	//未知错误
	return 0;
}

//int Mat::GetValue(MatVar SMP, Eigen::ArrayXXi &Value)
//{
//    std::map<MatVar,Eigen::ArrayXXi>::iterator it;
//    it = MatPropiarray.find(SMP);
//    if(it != MatPropiarray.end())
//    {
//        //找到了
//        Value = it->second;
//        return 1;
//    }
//    else
//    {
//        Value.resize(1,1);
//        return 0;
//    }
//}

int Mat::hasProp(MatVar SMP)
{
	std::map<MatVar, double>::iterator itd = MatPropd.find(SMP);
	if (itd != MatPropd.end())
	{
		return 1;
	}


	std::map<MatVar, Eigen::MatrixXd>::iterator it = MatPropdarray.find(SMP);
	if (it != MatPropdarray.end())
	{
		return 1;
	}
	return 0;
}

int Mat::IsSolid()
{
	return matcate == Solid;
}

int Mat::IsLiquid()
{
	return matcate == Liquid;
}

int Mat::IsIsoMat()
{
	return mattype == Iso;
}

int Mat::IsOrthMat()
{
	return mattype == Orth;
}

int Mat::IsAnisoMat()
{
	return mattype == Aniso;
}

int Mat::IsPlaneStress()
{
	return (dim == 2) && (matstatus == PlaneStress);
}

int Mat::IsPlaneStrain()
{
	return (dim == 2) && (matstatus == PlaneStrain);
}

MatType Mat::GetMatType()
{
	return this->mattype;
}

MatStatus Mat::GetMatStatus()
{
	return this->matstatus;
}
