#include "isolinearstrumat.h"

IsoLinearStruMat::IsoLinearStruMat(int dim) :LinearStruMat(dim)
{
	mattype = Iso;
}

IsoLinearStruMat::~IsoLinearStruMat()
{

}

int IsoLinearStruMat::ComputeMatrix(MatMatrix matmatrix, Eigen::MatrixXd& matReturn)
{
	return 1;
}
