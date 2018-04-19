#ifndef ABSTRACTMATERIAL_H
#define ABSTRACTMATERIAL_H

#include "matpropvar.h"
#include "Eigen/Eigen"
#include <map>

#include <stdio.h>
#include <string>


using namespace std;

class Mat
{
public:
    Mat(int id);
    virtual ~Mat() = 0;

	int hasProp(MatVar SMP);

    int GetValue(MatVar SMP,double *Value);
    //int GetValue(MatVar SMP,int *Value);

	int GetValue(MatVar SMP, Eigen::MatrixXd& Value);
    //int GetValue(MatVar SMP,Eigen::ArrayXXi& Value);

	int SetValue(const map<string, double>& PropNameAndValue);
	int SetDimAndMatStatus(const string& str);
	

    virtual int ComputeMatrix(MatMatrix matmatrix,Eigen::MatrixXd& matReturn) = 0;

	int IsSolid();
	int IsLiquid();

	int IsIsoMat();
	int IsOrthMat();
	int IsAnisoMat();

	int IsPlaneStress();
	int IsPlaneStrain();

	MatType GetMatType();
	MatStatus GetMatStatus();

public:



protected:
	int __SetValue(MatVar SMP, double Value);


protected:
	int id;
	int dim;     //Î¬¶È
	

	MatCategory matcate;
	MatType mattype;
	MatStatus matstatus;


    std::map<MatVar,double> MatPropd;
    //std::map<MatVar,int>    MatPropi;

    std::map<MatVar,Eigen::MatrixXd> MatPropdarray;
    //std::map<MatVar,Eigen::ArrayXXi> MatPropiarray;

};

#endif // ABSTRACTMATERIAL_H
