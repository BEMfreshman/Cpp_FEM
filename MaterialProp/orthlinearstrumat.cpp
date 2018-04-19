#include "orthlinearstrumat.h"

OrthLinearStruMat::OrthLinearStruMat(int dim) :LinearStruMat(dim)
{
	mattype = Orth;
}

OrthLinearStruMat::~OrthLinearStruMat()
{

}

int OrthLinearStruMat::ComputeMatrix(MatMatrix matmatrix, Eigen::MatrixXd& matReturn)
{
	return 0;
}
