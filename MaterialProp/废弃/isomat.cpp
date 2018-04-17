#include "isomat.h"

IsoMat::IsoMat()
{
    *E = 0.0;
    *Nu = 0.0;
    *G = 0.0;
    *Rho = 0.0;
    id = 0;

    mattype = Iso;
}

void IsoMat::CaculateG()
{
    *G = (*E) / (2.0 * (1 + (*Nu)));
    this->GNum = 1;
}

void IsoMat::CaculateE()
{
    *E = 2.0 * (*G) * (1 + (*Nu));
    this->ENum = 1;
}

void IsoMat::CaculateNu()
{
    *Nu = (*E) / (2.0 * (*G)) - 1;
    this->NuNum = 1;
}

void IsoMat::InitialEandNu(double* E,double* Nu)
{
    this->E = E;
    this->Nu = Nu;
    CaculateG();

    this->ENum = 1;
    this->NuNum = 1;

}

void IsoMat::InitialEandG(double* E,double* G)
{
    this->E = E;
    this->G = G;
    CaculateNu();

    this->ENum = 1;
    this->GNum = 1;
}

void IsoMat::InitialNuandG(double* Nu,double* G)
{
    this->Nu = Nu;
    this->G = G;
    CaculateE();

    this->NuNum = 1;
    this->GNum = 1;
}





IsoMat2d::IsoMat2d()
{
    dim = Two;
}

IsoMat2d::~IsoMat2d()
{

}

void IsoMat2d::ComputeDMatrix(MatrixXd& Dmat)
{
    Dmat.resize(3,3);
    Dmat.setZero(3,3);

    double EVal = GetE();
    double NuVal = GetNu();

    if(type == PlaneStress)
    {
        double Coff = EVal / (1.0 - pow(NuVal,2));
        Dmat << 1.0,NuVal,0.0,
                NuVal,1.0,0.0,
                0,0,(1-NuVal)/2.0;
        Dmat *= Coff;
    }
    else if(type == PlaneStrain)
    {
        double Coff = EVal*(1-NuVal)/((1+NuVal)*(1-2*NuVal));
        Dmat << 1.0,NuVal/(1-NuVal),0.0,
                NuVal/(1-NuVal),1.0,0.0,
                0.0,0.0,(1-2*NuVal)/(2*(1-NuVal));
        Dmat *= Coff;
    }
}

void IsoMat2d::InitialType(StressOrStrain type)
{
    this->type = type;
}

IsoMat3d::IsoMat3d()
{

}

IsoMat3d::~IsoMat3d()
{

}

void IsoMat3d::ComputeDMatrix(MatrixXd& Dmat)
{
    Dmat.resize(6,6);
    Dmat.resize(6,6);

    double EVal = GetE();
    double NuVal = GetNu();

    double Coff = EVal*(1-NuVal)/((1+NuVal)*(1-2*NuVal));
    Dmat << 1.0,NuVal/(1-NuVal),NuVal/(1-NuVal),0.0,0.0,0.0,
            NuVal/(1-NuVal),1.0,NuVal/(1-NuVal),0.0,0.0,0.0,
            NuVal/(1-NuVal),NuVal/(1-NuVal),1.0,0.0,0.0,0.0,
            0.0,0.0,0.0,(1-2*NuVal)/(2*(1-NuVal)),0.0,0.0,
            0.0,0.0,0.0,0.0,(1-2*NuVal)/(2*(1-NuVal)),0.0,
            0.0,0.0,0.0,0.0,0.0,(1-2*NuVal)/(2*(1-NuVal));

    Dmat *= Coff;
}
