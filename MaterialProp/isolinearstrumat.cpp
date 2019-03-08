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
	if (matmatrix == DMatrix)
	{
		if (IsPlaneStrain())
		{
			if (hasProp(E) == 0 || hasProp(Nu) == 0)
			{
				printf("��������\n");
				return 0;
			}
			matReturn.resize(3, 3);
			matReturn.setZero();

			double EVal, NuVal;

			GetValue(E, &EVal);
			GetValue(Nu, &NuVal);

			double coeff = EVal / ((1 + NuVal)*(1 - 2 * NuVal));
			matReturn << 1 - NuVal, NuVal, 0,
				NuVal , 1 - NuVal, 0,
				0, 0, (1 - 2 * NuVal) / 2;

			matReturn *= coeff;
		}
		else if (IsPlaneStress())
		{
			if (hasProp(E) == 0 || hasProp(Nu) == 0)
			{
				printf("��������\n");
				return 0;
			}
			matReturn.resize(3, 3);
			matReturn.setZero();
			
			double EVal, NuVal;

			GetValue(E, &EVal);
			GetValue(Nu, &NuVal);

			double coeff = EVal / (1 - pow(NuVal, 2));
			matReturn << 1, NuVal, 0,
				NuVal, 1, 0,
				0, 0, (1 - NuVal) / 2;
			matReturn *= coeff;


		}
		else
		{
			printf("Ӧ��״̬\n");
			return 0;
		}
	}

	return 1;
}
