#include "isolinearstrumat.h"

IsoLinearStruMat::IsoLinearStruMat(int dim) :LinearStruMat(dim)
{
	mattype = Iso;
}

IsoLinearStruMat::~IsoLinearStruMat()
{

}
