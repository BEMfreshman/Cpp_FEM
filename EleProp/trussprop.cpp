#include "trussprop.h"

TrussProp::TrussProp():id(0),Area(0),L(0),J(0)
{
    mat = NULL;
}

TrussProp::TrussProp(int id,double Area,double L,Mat* mat)
{
    this->id = id;
    this->Area = Area;
    this->L = L;
    this->mat = mat;
}

void TrussProp::SetJ(double J)
{
    this->J = J;
}

bool TrussProp::IsIsoMat()
{
    Mat::MatType mattype = mat->GetMatType();

    if(mattype != Mat::Iso)
    {
        return false;
    }
    else
    {
        return true;
    }
}

int TrussProp::GetId()
{
    return id;
}

double TrussProp::GetArea()
{
    return Area;
}

double TrussProp::GetJ()
{
    return J;
}

double TrussProp::GetL()
{
    return L;
}

Mat* TrussProp::GetMat()
{
    return mat;
}
