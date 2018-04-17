#include "mat.h"

Mat::Mat()
{

}


void Mat::SetDensity(double Rho)
{
    *(this->Rho) = Rho;
}

void Mat::SetId(int id)
{
    this->id = id;
}

int Mat::GetENum()
{
    return ENum;
}

int Mat::GetGNum()
{
    return GNum;
}

int Mat::GetNuNum()
{
    return NuNum;
}

int Mat::GetId()
{
    return id;
}

Mat::MatType Mat::GetMatType()
{
    return mattype;
}

double* Mat::GetE()
{
    return E;
}

double* Mat::GetNu()
{
    return Nu;
}

double* Mat::GetG()
{
    return G;
}
