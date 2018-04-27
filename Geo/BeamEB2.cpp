#include "BeamEB2.h"
#include "../TopAbstractClass/abastractelementprop.h"
#include "../TopAbstractClass/abstractmaterial.h"

BeamEB2::BeamEB2()
{

}

BeamEB2::BeamEB2(int ElementId,
	int MaterialId,
	int EPropId,
	ElementType eletype,
	const Eigen::MatrixXi& VertexIdArray) :Line2(ElementId, MaterialId,
	eletype, VertexIdArray)
{
	this->EPropId = EPropId;
}

BeamEB2::~BeamEB2()
{

}

BeamEB2::BeamEB2(const BeamEB2 &that) :Line2(that)
{

}

BeamEB2& BeamEB2::operator=(const BeamEB2& that)
{
	if (this != &that)
	{
		Element::operator= (that);
		return *this;
	}
	else
	{
		return *this;
	}
}

Element* BeamEB2::Clone() const
{
	return new BeamEB2(*this);
}

int BeamEB2::GetSpecificMatrix(SparseMatrixType SMT,
	Eigen::MatrixXd& ReturnMatrix)
{
	//���㵥Ԫ�նȾ�����ߵ�Ԫ��������
	return 0;
}

int BeamEB2::ComputeStiffnessMatrix(Eigen::MatrixXd& matReturn)
{
	//ŷ��������Ŭ����
	//����նȾ���

	//ͨ��������ɶȣ�ȷ���նȾ���Ĵ�С
	
	if (GetDOFNumofEle() == 0)
	{
		printf("�õ�Ԫδ���õ�Ԫ�ڵ�\n");
		return 0;
	}

	matReturn.resize(DOFNumofEle, DOFNumofEle);
	matReturn.setZero();


	if (DOFNumofEle == 4)
	{
		//һά����Ԫ

		if (EleProp->hasProp(Iz) == 0)
		{
			printf("Iz������");
			return 0;
		}
		else if (Material->hasProp(E) == 0 && Material->hasProp(Ex) == 0
			&& Material->hasProp(Ey) == 0 && Material->hasProp(Ez) == 0)
		{
			printf("������E");
			return 0;
		}
		else
		{
			ComputeElementLength();

			if (Material->IsIsoMat() == 1)
			{
				//����ͬ�Բ���
				double EVal,IzVal;
				if (Material->GetValue(E, &EVal) == 0)
				{
					printf("δ�ܳ�ȡ��E\n");
					return 0;
				}

				if (EleProp->GetValue(Iz, &IzVal) == 0)
				{
					printf("δ�ܳ�ȡ��Iz\n");
					return 0;
				}


				double Coeff = EVal*IzVal / (pow(ElementLength, 3));

				matReturn(0, 0) = 12.0;
				matReturn(0, 1) = 6 * ElementLength;
				matReturn(0, 2) = -12.0;
				matReturn(0, 3) = -6 * ElementLength;

				matReturn(1, 0) = matReturn(0, 1);
				matReturn(1, 1) = 4 * pow(ElementLength, 2);
				matReturn(1, 2) = -6 * ElementLength;
				matReturn(1, 3) = 2 * pow(ElementLength, 2);

				matReturn(2, 0) = matReturn(0, 2);
				matReturn(2, 1) = matReturn(1, 2);
				matReturn(2, 2) = 12;
				matReturn(2, 3) = -6 * ElementLength;

				matReturn(3, 0) = matReturn(0, 3);
				matReturn(3, 1) = matReturn(1, 3);
				matReturn(3, 2) = matReturn(2, 3);
				matReturn(3, 3) = 4 * pow(ElementLength, 2);

				matReturn *= Coeff;

			}
		}
	}
	else if (DOFNumofEle == 6)
	{
		//��ά����Ԫ

		if (EleProp->hasProp(Iz) == 0)
		{
			printf("Iz������");
			return 0;
		}
		else if (EleProp->hasProp(Area) == 0)
		{
			printf("Area������");
			return 0;
		}
		else if (Material->hasProp(E) == 0 && Material->hasProp(Ex) == 0
			&& Material->hasProp(Ey) == 0 && Material->hasProp(Ez) == 0)
		{
			printf("������E");
			return 0;
		}
		else
		{
			ComputeElementLength();
			if (Material->IsIsoMat() == 1)
			{
				//����ͬ�Բ���
				double EVal, IzVal, AreaVal;
				if (Material->GetValue(E, &EVal) == 0)
				{
					printf("δ�ܳ�ȡ��E\n");
					return 0;
				}

				if (EleProp->GetValue(Iz, &IzVal) == 0)
				{
					printf("δ�ܳ�ȡ��Iz\n");
					return 0;
				}

				if (EleProp->GetValue(Area, &AreaVal) == 0)
				{
					printf("δ�ܳ�ȡ��Area\n");
					return 0;
				}

				matReturn(0, 0) = EVal*AreaVal / ElementLength;
				matReturn(0, 3) = -EVal*AreaVal / ElementLength;

				matReturn(1, 1) = 12 * EVal*IzVal / pow(ElementLength, 3);
				matReturn(1, 2) = 6 * EVal*IzVal / pow(ElementLength, 2);
				matReturn(1, 4) = -12 * EVal*IzVal / pow(ElementLength, 3);
				matReturn(1, 5) = 6 * EVal*IzVal / pow(ElementLength, 2);

				matReturn(2, 1) = 6 * EVal*IzVal / pow(ElementLength, 2);
				matReturn(2, 2) = 4 * EVal*IzVal / ElementLength;
				matReturn(2, 4) = -6 * EVal*IzVal / pow(ElementLength, 2);
				matReturn(2, 5) = 2 * EVal*IzVal / ElementLength;

				matReturn(3, 0) = matReturn(0, 3);
				matReturn(3, 3) = EVal*AreaVal / ElementLength;

				matReturn(4, 1) = matReturn(1, 4);
				matReturn(4, 2) = matReturn(2, 4);
				matReturn(4, 4) = 12 * EVal*IzVal / pow(ElementLength, 3);
				matReturn(4, 5) = -6 * EVal*IzVal / pow(ElementLength, 2);

				matReturn(5, 1) = matReturn(1, 5);
				matReturn(5, 2) = matReturn(2, 5);
				matReturn(5, 4) = matReturn(4, 5);
				matReturn(5, 5) = 4 * EVal*IzVal / ElementLength;

			}
		}
	}
	else if (DOFNumofEle == 12)
	{
		//��ά����Ԫ
	}

	return 0;
}

int BeamEB2::ComputeMassMatrix(Eigen::MatrixXd& matReturn)
{
	if (GetDOFNumofEle() == 0)
	{
		printf("�õ�Ԫδ���õ�Ԫ�ڵ�\n");
		return 0;
	}

	matReturn.resize(DOFNumofEle, DOFNumofEle);
	matReturn.setZero();

	if (DOFNumofEle == 4)
	{
		//һά����Ԫ

		if (Material->hasProp(RHO) == 0)
		{
			printf("ȱ���ܶ�\n");
			return 0;
		}
		
		if (EleProp->hasProp(Area) == 0)
		{
			printf("ȱ�ٽ������\n");
			return 0;
		}

		ComputeElementLength();

		double RHOVal, AreaVal;

		if (Material->GetValue(RHO, &RHOVal) == 0)
		{
			printf("δ�ܳ�ȡ���ܶ�ֵ\n");
			return 0;
		}

		if (EleProp->GetValue(Area, &AreaVal) == 0)
		{
			printf("δ�ܳ�ȡ�����\n");
			return 0;
		}

		double Coeff = RHOVal*AreaVal*ElementLength / 420.0;

		matReturn(0, 0) = 156;
		matReturn(0, 1) = 22 * ElementLength;
		matReturn(0, 2) = 54;
		matReturn(0, 3) = -13 * ElementLength;

		matReturn(1, 0) = matReturn(0, 1);
		matReturn(1, 1) = 4 * pow(ElementLength, 2);
		matReturn(1, 2) = 13 * ElementLength;
		matReturn(1, 3) = -3 * pow(ElementLength, 2);

		matReturn(2, 0) = matReturn(0, 2);
		matReturn(2, 1) = matReturn(1, 2);
		matReturn(2, 2) = 156;
		matReturn(2, 3) = -22 * ElementLength;

		matReturn(3, 0) = matReturn(0, 3);
		matReturn(3, 1) = matReturn(1, 3);
		matReturn(3, 2) = matReturn(2, 3);
		matReturn(3, 3) = 4 * pow(ElementLength, 2);

		matReturn *= Coeff;
	}
	else if (DOFNumofEle == 6)
	{
		//��ά����Ԫ

		if (Material->hasProp(RHO) == 0)
		{
			printf("ȱ���ܶ�\n");
			return 0;
		}

		if (EleProp->hasProp(Area) == 0)
		{
			printf("ȱ�ٽ������\n");
			return 0;
		}

		ComputeElementLength();

		double RHOVal, AreaVal;

		if (Material->GetValue(RHO, &RHOVal) == 0)
		{
			printf("δ�ܳ�ȡ���ܶ�ֵ\n");
			return 0;
		}

		if (EleProp->GetValue(Area, &AreaVal) == 0)
		{
			printf("δ�ܳ�ȡ�����\n");
			return 0;
		}

		double Coeff = RHOVal*AreaVal*ElementLength / 420.0;

		matReturn(0, 0) = 140;
		matReturn(0, 3) = 70;

		matReturn(1, 1) = 156;
		matReturn(1, 2) = 22 * ElementLength;
		matReturn(1, 4) = 54;
		matReturn(1, 5) = -13 * ElementLength;

		matReturn(2, 1) = matReturn(1, 2);
		matReturn(2, 2) = 4 * pow(ElementLength, 2);
		matReturn(2, 4) = 13 * ElementLength;
		matReturn(2, 5) = -3 * pow(ElementLength, 2);

		matReturn(3, 0) = matReturn(0, 3);
		matReturn(3, 3) = 140;

		matReturn(4, 1) = matReturn(1, 4);
		matReturn(4, 2) = matReturn(2, 4);
		matReturn(4, 4) = 156;
		matReturn(4, 5) = -22 * ElementLength;

		matReturn(5, 1) = matReturn(1, 5);
		matReturn(5, 2) = matReturn(2, 5);
		matReturn(5, 4) = matReturn(4, 5);
		matReturn(5, 5) = 4 * pow(ElementLength, 2);

		matReturn *= Coeff;
	}
	else if (DOFNumofEle == 12)
	{
		//��ά����Ԫ
	}

	return 0;
}

int BeamEB2::SetDOF(int dim)
{
	return 0;
}

