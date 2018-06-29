#include "abstractelement.h"
#include "../Geo/vertex.h"
#include "Dof.h"
#include "../TopAbstractClass/abstractmaterial.h"
#include "../TopAbstractClass/abastractelementprop.h"

Element::Element():ElementId(0),MatId(0),
EPropId(0), DOFNumofEle(0)
{

    EleProp = NULL;
    Material = NULL;
}

Element::Element(int ElementId,
                 int MaterialId,
                 ElementType eletype,
				 int dim,
                 const Eigen::MatrixXi& VertexIdArray)
{
    this->ElementId = ElementId;
    this->MatId = MaterialId;
    this->EleType = eletype;
    this->VertexIdArray = VertexIdArray;
	this->DOFNumofEle = 0;
    this->EPropId = 0;
	this->dim = dim;

    EleProp = NULL;
    Material = NULL;

}

Element::Element(int ElementId,
                 int MaterialId,
                 int EPropId,
                 ElementType eletype,
				 int dim,
                 const Eigen::MatrixXi& VertexIdArray)
{
    this->ElementId = ElementId;
    this->MatId = MaterialId;
    this->EPropId = EPropId;
    this->EleType = eletype;
    this->VertexIdArray = VertexIdArray;
	this->DOFNumofEle = 0;
	this->dim = dim;

    EleProp = NULL;
    Material = NULL;
}

Element::Element(const Element& that):ElementId(that.ElementId),
    MatId(that.MatId),
    EPropId(that.EPropId),
	dim(that.dim),
    VertexIdArray(that.VertexIdArray),
    VertexVec(that.VertexVec),
    NeedGauss(that.NeedGauss),
    EleType(that.EleType),
    LocalGaussPoint(that.LocalGaussPoint),
    GaussWeight(that.GaussWeight),
    N(that.N),
    dNdxi(that.dNdxi),
    Material(that.Material),
    EleProp(that.EleProp),
	DOFNumofEle(that.DOFNumofEle)

{

}

Element& Element::operator =(const Element& that)
{
    if(&that != this)
    {
        EleProp = that.EleProp;
        Material=that.Material;
        ElementId = that.ElementId;
        EPropId = that.EPropId;
        MatId=that.MatId;
        VertexIdArray=that.VertexIdArray;
        VertexVec=that.VertexVec;
        NeedGauss=that.NeedGauss;
        EleType=that.EleType;
        LocalGaussPoint=that.LocalGaussPoint;
        GaussWeight=that.GaussWeight;
        N=that.N;
        dNdxi=that.dNdxi;
		DOFNumofEle = that.DOFNumofEle;
    }
    return *this;
}

Element::~Element()
{

}

int Element::GetElementId() const
{
    return ElementId;
}

int Element::GetEPropId() const
{
    return EPropId;
}

int Element::GetMaterialId() const
{
    return MatId;
}

const Eigen::MatrixXi& Element::GetVertexIdArray() const
{
    return VertexIdArray;
}

int Element::GetDOFNumofEle()
{
	if (DOFNumofEle == 0)
	{
		if (VertexVec.size() == 0)
		{
			return 0;
		}
		else
		{
			int res = 0;
			for (size_t i = 0; i < VertexVec.size(); i++)
			{
				res += VertexVec[i]->getDOFSize();
			}
			DOFNumofEle = res;

			return res;
		}
	}
	else
	{
		return DOFNumofEle;
	}
}



void Element::SetEProp(EProp *EleProp)

{
    this->EleProp = EleProp;
}

void Element::SetMat(Mat *Material)
{
    this->Material = Material;
}

void Element::Setdim(int dim)
{
	this->dim = dim;
}

void Element::SetVertex(Vertex* vertex)
{
	this->VertexVec.push_back(vertex);
}

void Element::GenerateGaussPoint(int Order)
{

}

void Element::OneDimensionGPAndWeight(int Order)
{
	if (Order == 2)
	{
		GaussPointOneDimension.push_back(0.577350269189626);
		GaussPointOneDimension.push_back(-0.577350269189626);

		WeightOneDimension.push_back(1.0);
		WeightOneDimension.push_back(1.0);
	}
	else if (Order == 3)
	{
		GaussPointOneDimension.push_back(0.774596669241483);
		GaussPointOneDimension.push_back(-0.774596669241483);
		GaussPointOneDimension.push_back(0.000000000000000);

		WeightOneDimension.push_back(0.555555555555556);
		WeightOneDimension.push_back(0.555555555555556);
		WeightOneDimension.push_back(0.888888888888889);
	}
	else if (Order == 4)
	{
		GaussPointOneDimension.push_back(0.861134311594053);
		GaussPointOneDimension.push_back(-0.861134311594053);
		GaussPointOneDimension.push_back(0.339981043584856);
		GaussPointOneDimension.push_back(-0.339981043584856);

		WeightOneDimension.push_back(0.347854845137454);
		WeightOneDimension.push_back(0.347854845137454);
		WeightOneDimension.push_back(0.652145154862546);
		WeightOneDimension.push_back(0.652145154862546);
	}
	else if (Order == 5)
	{
		GaussPointOneDimension.push_back(0.906179845938664);
		GaussPointOneDimension.push_back(-0.906179845938664);
		GaussPointOneDimension.push_back(0.538469310105683);
		GaussPointOneDimension.push_back(-0.538469310105683);
		GaussPointOneDimension.push_back(0.000000000000000);

		WeightOneDimension.push_back(0.236926885056189);
		WeightOneDimension.push_back(0.236926885056189);
		WeightOneDimension.push_back(0.478628670499366);
		WeightOneDimension.push_back(0.478628670499366);
		WeightOneDimension.push_back(0.568888888888889);
	}
	else if (Order == 6)
	{
		GaussPointOneDimension.push_back(0.932469514203152);
		GaussPointOneDimension.push_back(-0.932469514203152);
		GaussPointOneDimension.push_back(0.661209386466265);
		GaussPointOneDimension.push_back(-0.661209386466265);
		GaussPointOneDimension.push_back(0.238619186003152);
		GaussPointOneDimension.push_back(-0.238619186003152);

		WeightOneDimension.push_back(0.171324492379170);
		WeightOneDimension.push_back(0.171324492379170);
		WeightOneDimension.push_back(0.360761573048139);
		WeightOneDimension.push_back(0.360761573048139);
		WeightOneDimension.push_back(0.467913934572691);
		WeightOneDimension.push_back(0.467913934572691);
	}
	else if (Order == 7)
	{
		GaussPointOneDimension.push_back(0.949107912342759);
		GaussPointOneDimension.push_back(-0.949107912342759);
		GaussPointOneDimension.push_back(0.741531185599394);
		GaussPointOneDimension.push_back(-0.741531185599394);
		GaussPointOneDimension.push_back(0.405845151377397);
		GaussPointOneDimension.push_back(-0.405845151377397);
		GaussPointOneDimension.push_back(0.000000000000000);

		WeightOneDimension.push_back(0.129484966168870);
		WeightOneDimension.push_back(0.129484966168870);
		WeightOneDimension.push_back(0.279705391489277);
		WeightOneDimension.push_back(0.279705391489277);
		WeightOneDimension.push_back(0.381830050505119);
		WeightOneDimension.push_back(0.381830050505119);
		WeightOneDimension.push_back(0.417959183673469);
	}
	else if (Order == 8)
	{
		GaussPointOneDimension.push_back(0.960289856497536);
		GaussPointOneDimension.push_back(-0.960289856497536);
		GaussPointOneDimension.push_back(0.796666477413627);
		GaussPointOneDimension.push_back(-0.796666477413627);
		GaussPointOneDimension.push_back(0.525532409916329);
		GaussPointOneDimension.push_back(-0.525532409916329);
		GaussPointOneDimension.push_back(0.183434642495650);
		GaussPointOneDimension.push_back(-0.183434642495650);

		WeightOneDimension.push_back(0.101228536290376);
		WeightOneDimension.push_back(0.101228536290376);
		WeightOneDimension.push_back(0.222381034453374);
		WeightOneDimension.push_back(0.222381034453374);
		WeightOneDimension.push_back(0.313706645877887);
		WeightOneDimension.push_back(0.313706645877887);
		WeightOneDimension.push_back(0.362683783378362);
		WeightOneDimension.push_back(0.362683783378362);
	}
}

int Element::GetVertexInEleNum() const
{
	return VertexVec.size();
}

Vertex* Element::GetVertexInEle(int i) const
{
	return (i >= VertexVec.size() ? NULL : VertexVec[i]);
}
void Element::GetValidDOFId(Eigen::VectorXi& ValidTotalDOFIdArray,
	Eigen::VectorXi& IsValidArray)
{
	vector<int> tmpDOFId;
	vector<int> tmpValid;
	for (size_t i = 0; i < VertexVec.size(); i++)
	{
		/*for (int j = 0; j < VertexVec[i]->getDOFSize(); j++)
		{
			DOF* dof = VertexVec[i]->getDOF(j);
			tmpDOFId.push_back(dof->getVaildTotalDOFId());
			tmpValid.push_back(dof->getIsVaild() == true ? 1 : 0);
		}*/
		VertexVec[i]->getValidDOFIdAndIsValidArray(tmpDOFId, tmpValid);
	}

	ValidTotalDOFIdArray.resize(tmpDOFId.size());
	IsValidArray.resize(tmpValid.size());

	for (size_t i = 0; i < tmpDOFId.size(); i++)
	{
		ValidTotalDOFIdArray(i) = tmpDOFId[i];
		IsValidArray(i) = tmpValid[i];
	}
}

DOF* Element::GetDOFInEleByTotalDOFId(int TotalDOFId) const
{
	for (size_t i = 0; i < VertexVec.size(); i++)
	{
		Vertex* Ver = VertexVec[i];
		for (int j = 0; j < Ver->getDOFSize(); j++)
		{
			if (Ver->getDOF(j)->getVaildTotalDOFId() == TotalDOFId)
			{
				return Ver->getDOF(j);
			}
		}
	}

	return NULL;
}

void Element::ProduceValidTriple(const Eigen::MatrixXd& mat,
	vector<T_>& TripleList)
{
	Eigen::VectorXi ValidTotalDOFIdArray;
	Eigen::VectorXi IsValidArray;

	GetValidDOFId(ValidTotalDOFIdArray, IsValidArray);

	/*cout << "ValidTotalDofIdArray is " << endl;
	cout << ValidTotalDOFIdArray << endl;

	cout << "IsValidArray is " << endl;
	cout << IsValidArray << endl;*/

	for (int i = 0; i < ValidTotalDOFIdArray.size(); i++)
	{
		for (int j = 0; j < ValidTotalDOFIdArray.size(); j++)
		{
			if (abs(IsValidArray(i)) > EPS && abs(IsValidArray(j)) > EPS)
				//IsValidArray(i) != 0 && IsValidArray(j) != 0
			{
				TripleList.push_back(T_(ValidTotalDOFIdArray(i),
					ValidTotalDOFIdArray(j),
					mat(i, j)));
			}
			else if (abs(IsValidArray(i)) < EPS && abs(IsValidArray(j)) > EPS)
				//IsValidArray(i) == 0 && IsValidArray(j) != 0
			{
				GetDOFInEleByTotalDOFId(ValidTotalDOFIdArray(i))
					->addresidualK(T_(IsValidArray(j), 0, mat(i, j)));

			}
			else
				//IsValidArray(i) == 0 && IsValidArray(j) == 0
				//IsValidArray(i) != 0 && IsValidArray(j) == 0
			{
				continue;
			}
		}
	}
}

void Element::ProduceValidTripleForF(const Eigen::MatrixXd& mat,
	vector<T_>& TripleList)
{
	Eigen::VectorXi ValidTotalDOFIdArray;
	Eigen::VectorXi IsValidArray;

	GetValidDOFId(ValidTotalDOFIdArray, IsValidArray);

	/*cout << "ValidTotalDofIdArray is " << endl;
	cout << ValidTotalDOFIdArray << endl;

	cout << "IsValidArray is " << endl;
	cout << IsValidArray << endl;*/

	for (int i = 0; i < ValidTotalDOFIdArray.size(); i++)
	{
		if (abs(IsValidArray(i)) > EPS)
			//IsValidArray(i) != 0 && IsValidArray(j) != 0
		{
			TripleList.push_back(T_(ValidTotalDOFIdArray(i),
				0,
				mat(i, 0)));
		}
		else
			//IsValidArray(i) == 0 && IsValidArray(j) == 0
			//IsValidArray(i) != 0 && IsValidArray(j) == 0
		{
			continue;
		}
		
	}
}

/*
void Element::GenerateLoacalGaussPointAndWeight(int Order)
{
    std::vector<double> GaussPointOneDimension;
    std::vector<double> WeightOneDimension;

    if(Order == 2)
    {
        GaussPointOneDimension.push_back(0.577350269189626);
        GaussPointOneDimension.push_back(-0.577350269189626);

        WeightOneDimension.push_back(1.0);
        WeightOneDimension.push_back(1.0);
    }
    else if(Order == 3)
    {
        GaussPointOneDimension.push_back(0.774596669241483);
        GaussPointOneDimension.push_back(-0.774596669241483);
        GaussPointOneDimension.push_back(0.000000000000000);

        WeightOneDimension.push_back(0.555555555555556);
        WeightOneDimension.push_back(0.555555555555556);
        WeightOneDimension.push_back(0.888888888888889);
    }
    else if(Order == 4)
    {
        GaussPointOneDimension.push_back( 0.861134311594053);
        GaussPointOneDimension.push_back(-0.861134311594053);
        GaussPointOneDimension.push_back( 0.339981043584856);
        GaussPointOneDimension.push_back(-0.339981043584856);

        WeightOneDimension.push_back(0.347854845137454);
        WeightOneDimension.push_back(0.347854845137454);
        WeightOneDimension.push_back(0.652145154862546);
        WeightOneDimension.push_back(0.652145154862546);
    }
    else if(Order == 5)
    {
        GaussPointOneDimension.push_back( 0.906179845938664);
        GaussPointOneDimension.push_back(-0.906179845938664);
        GaussPointOneDimension.push_back( 0.538469310105683);
        GaussPointOneDimension.push_back(-0.538469310105683);
        GaussPointOneDimension.push_back( 0.000000000000000);

        WeightOneDimension.push_back(0.236926885056189);
        WeightOneDimension.push_back(0.236926885056189);
        WeightOneDimension.push_back(0.478628670499366);
        WeightOneDimension.push_back(0.478628670499366);
        WeightOneDimension.push_back(0.568888888888889);
    }
    else if(Order == 6)
    {
        GaussPointOneDimension.push_back( 0.932469514203152);
        GaussPointOneDimension.push_back(-0.932469514203152);
        GaussPointOneDimension.push_back( 0.661209386466265);
        GaussPointOneDimension.push_back(-0.661209386466265);
        GaussPointOneDimension.push_back( 0.238619186003152);
        GaussPointOneDimension.push_back(-0.238619186003152);

        WeightOneDimension.push_back(0.171324492379170);
        WeightOneDimension.push_back(0.171324492379170);
        WeightOneDimension.push_back(0.360761573048139);
        WeightOneDimension.push_back(0.360761573048139);
        WeightOneDimension.push_back(0.467913934572691);
        WeightOneDimension.push_back(0.467913934572691);
    }
    else if(Order == 7)
    {
        GaussPointOneDimension.push_back(  0.949107912342759);
        GaussPointOneDimension.push_back( -0.949107912342759);
        GaussPointOneDimension.push_back(  0.741531185599394);
        GaussPointOneDimension.push_back( -0.741531185599394);
        GaussPointOneDimension.push_back(  0.405845151377397);
        GaussPointOneDimension.push_back( -0.405845151377397);
        GaussPointOneDimension.push_back(  0.000000000000000);

        WeightOneDimension.push_back(0.129484966168870);
        WeightOneDimension.push_back(0.129484966168870);
        WeightOneDimension.push_back(0.279705391489277);
        WeightOneDimension.push_back(0.279705391489277);
        WeightOneDimension.push_back(0.381830050505119);
        WeightOneDimension.push_back(0.381830050505119);
        WeightOneDimension.push_back(0.417959183673469);
    }
    else if(Order == 8)
    {
        GaussPointOneDimension.push_back(  0.960289856497536);
        GaussPointOneDimension.push_back( -0.960289856497536);
        GaussPointOneDimension.push_back(  0.796666477413627);
        GaussPointOneDimension.push_back( -0.796666477413627);
        GaussPointOneDimension.push_back(  0.525532409916329);
        GaussPointOneDimension.push_back( -0.525532409916329);
        GaussPointOneDimension.push_back(  0.183434642495650);
        GaussPointOneDimension.push_back( -0.183434642495650);

        WeightOneDimension.push_back(0.101228536290376);
        WeightOneDimension.push_back(0.101228536290376);
        WeightOneDimension.push_back(0.222381034453374);
        WeightOneDimension.push_back(0.222381034453374);
        WeightOneDimension.push_back(0.313706645877887);
        WeightOneDimension.push_back(0.313706645877887);
        WeightOneDimension.push_back(0.362683783378362);
        WeightOneDimension.push_back(0.362683783378362);
    }

    //上面的计算得出的是一维情况下GaussPoint和权重的分布，用于四边形和六面体中的GaussPoint生成

    if(GaussWeight.size() != 0)
    {
        GaussWeight.clear();
    }


    if(EleType >= Triangle3 &&
            EleType <= Triangle6)
    {
        //如果为三角形
        if(Order < 0)
        {
            printf("Order不能为0,程序退出\n");
            exit(1);
        }

        if(Order > 7)
        {
            printf("划分Triangle,Order数目过大,自动重置为7\n");
            Order = 7;
        }

        if(Order == 1)
        {
            LocalGaussPoint.resize(1,2);
            LocalGaussPoint << 0.3333333333333, 0.333333333333;
            GaussWeight.push_back(1.0/2);
        }
        else if(Order == 2)
        {
            LocalGaussPoint.resize(3,2);
            LocalGaussPoint << 0.1666666666667, 0.1666666666667,
                    0.6666666666667, 0.1666666666667,
                    0.1666666666667, 0.6666666666667;

            GaussWeight.push_back(0.3333333333333/2);
            GaussWeight.push_back(0.3333333333333/2);
            GaussWeight.push_back(0.3333333333333/2);
        }
        else if(Order == 3 || Order == 4 ||Order == 5)
        {
            LocalGaussPoint.resize(7,2);
            LocalGaussPoint << 0.1012865073235, 0.1012865073235,
                    0.7974269853531, 0.1012865073235,
                    0.1012865073235, 0.7974269853531,
                    0.4701420641051, 0.0597158717898,
                    0.4701420641051, 0.4701420641051,
                    0.0597158717898, 0.4701420641051,
                    0.3333333333333, 0.3333333333333;

            GaussWeight.push_back(0.1259391805448/2);
            GaussWeight.push_back(0.1259391805448/2);
            GaussWeight.push_back(0.1259391805448/2);
            GaussWeight.push_back(0.1323941527885/2);
            GaussWeight.push_back(0.1323941527885/2);
            GaussWeight.push_back(0.1323941527885/2);
            GaussWeight.push_back(0.2250000000000/2);
        }
        else
        {
            LocalGaussPoint.resize(13,2);
            LocalGaussPoint << 0.0651301029022, 0.0651301029022,
                    0.8697397941956, 0.0651301029022,
                    0.0651301029022, 0.8697397941956,
                    0.3128654960049, 0.0486903154253,
                    0.6384441885698, 0.3128654960049,
                    0.0486903154253, 0.6384441885698,
                    0.6384441885698, 0.0486903154253,
                    0.3128654960049, 0.6384441885698,
                    0.0486903154253, 0.3128654960049,
                    0.2603459660790, 0.2603459660790,
                    0.4793080678419, 0.2603459660790,
                    0.2603459660790, 0.4793080678419,
                    0.3333333333333, 0.3333333333333;

            GaussWeight.push_back(0.0533472356088/2);
            GaussWeight.push_back(0.0533472356088/2);
            GaussWeight.push_back(0.0533472356088/2);
            GaussWeight.push_back(0.0771137608903/2);
            GaussWeight.push_back(0.0771137608903/2);
            GaussWeight.push_back(0.0771137608903/2);
            GaussWeight.push_back(0.0771137608903/2);
            GaussWeight.push_back(0.0771137608903/2);
            GaussWeight.push_back(0.0771137608903/2);
            GaussWeight.push_back(0.1756152576332/2);
            GaussWeight.push_back(0.1756152576332/2);
            GaussWeight.push_back(0.1756152576332/2);
            GaussWeight.push_back(-0.1495700444677/2);
        }
    }
    else if(EleType>= Quadrilateral4 &&
            EleType <=Quadrilateral9)
    {
        //如果为四边形
        int dim = 2; //二维问题

        LocalGaussPoint.resize(Order*Order,dim);
        GaussWeight.reserve(Order*Order);
        int i,j;
        int counter = 0;

        double xCoord = 0.0;
        double yCoord = 0.0;

        Eigen::MatrixXd EachGaussPoint(1,dim);
        EachGaussPoint.setZero(1,dim);

        double EachGaussWeight;

        for(i = 0; i < Order;i++)
        {
            xCoord = GaussPointOneDimension[i];
            EachGaussPoint(0,0) = xCoord;
            for(j = 0;j < Order;j++)
            {
                yCoord = GaussPointOneDimension[j];
                EachGaussPoint(0,1) = yCoord;

                LocalGaussPoint.row(counter) = EachGaussPoint;
                counter++;

                EachGaussWeight = WeightOneDimension[i] * WeightOneDimension[j];
                GaussWeight.push_back(EachGaussWeight);
            }
        }
    }
    else if(EleType == Tetrahedron4)
    {
        //如果为四面体

        if(Order >3)
        {
            printf("划分Tetrahdron,Order的数目过大,Order将被重置为3\n");
            Order = 3;
        }

        if(Order == 1)
        {
            LocalGaussPoint.resize(1,3);
            LocalGaussPoint(0,0) = 0.25;
            LocalGaussPoint(0,1) = 0.25;
            LocalGaussPoint(0,2) = 0.25;

            GaussWeight.push_back(1.0/6);

        }
        else if(Order == 2)
        {
            LocalGaussPoint.resize(4,3);
            LocalGaussPoint <<  0.58541020,  0.13819660,  0.13819660,
                                0.13819660,  0.58541020,  0.13819660,
                                0.13819660,  0.13819660,  0.58541020,
                                0.13819660,  0.13819660,  0.13819660;

            GaussWeight.push_back(0.25/6);
            GaussWeight.push_back(0.25/6);
            GaussWeight.push_back(0.25/6);
            GaussWeight.push_back(0.25/6);
        }
        else if(Order == 3)
        {
            LocalGaussPoint.resize(5,3);
            LocalGaussPoint << 0.25,0.25,0.25,
                                1/2.0,1/6.0,1/6.0,
                                1/6.0,1/2.0,1/6.0,
                                1/6.0,1/6.0,1/2.0,
                                1/6.0,1/6.0,1/6.0;

            GaussWeight.push_back(-4/5.0/6);
            GaussWeight.push_back(9/20.0/6);
            GaussWeight.push_back(9/20.0/6);
            GaussWeight.push_back(9/20.0/6);
            GaussWeight.push_back(9/20.0/6);
        }
    }
    else if(EleType == Hexahedron8)
    {
        //如果为六面体

        int dim = 3; //三维问题
        LocalGaussPoint.resize(Order*Order*Order,dim);
        GaussWeight.reserve(Order*Order*Order);

        int i,j,k;
        int counter = 0;

        double xCoord = 0.0;
        double yCoord = 0.0;
        double zCoord = 0.0;

        Eigen::MatrixXd EachGaussPoint(1,dim);
        EachGaussPoint.setZero(1,dim);

        double EachGaussWeight;

        for(i = 0;i < Order;i++)
        {
            xCoord = GaussPointOneDimension[i];
            EachGaussPoint(0,0) = xCoord;
            for(j = 0;j < Order;j++)
            {
                yCoord = GaussPointOneDimension[j];
                EachGaussPoint(0,1) = yCoord;
                for(k = 0; k < Order;k++)
                {
                    zCoord = GaussPointOneDimension[k];
                    EachGaussPoint(0,2) = zCoord;

                    LocalGaussPoint.row(counter) = EachGaussPoint;
                    counter++;
                    EachGaussWeight = WeightOneDimension[i]*
                            WeightOneDimension[j]*
                            WeightOneDimension[k];
                    GaussWeight.push_back(EachGaussWeight);
                }
            }
        }
    }
}

void Element::ComputeShapeFunction()
{
    //计算形函数以及形函数的导数

	if (EleType == Truss || EleType == BeamEB2 || EleType == BeamEB3 ||
		EleType == BeamT2 || EleType == BeamT3 || EleType == Shell)
    {
        printf("不需要划分高斯积分点\n");
        return;
    }

    int VertexNum = VertexIdArray.rows();
    //单元上顶点的个数

    int GaussPointNum = LocalGaussPoint.rows();
    //高斯点的个数

    int dim = LocalGaussPoint.cols();
    //维数

    N.resize(VertexNum,GaussPointNum);

    int i = 0;

    switch (EleType)
    {
    case Line2:
    {
        //线单元 两点
        //一维单元 形函数只对一个坐标做偏导数
        dNdxi.resize(VertexNum,GaussPointNum);
        for (i = 0 ;i < GaussPointNum;i++)
        {

            Eigen::MatrixXd EachGaussPoint(1,dim);
            Eigen::MatrixXd EachGaussPointShapeFunction(VertexNum,1);
            // VertexNum = 2
            EachGaussPoint = LocalGaussPoint.row(i);

            double xi = EachGaussPoint(0,0);
            EachGaussPointShapeFunction(0,0) = (1.0-xi)/2.0;
            EachGaussPointShapeFunction(1,0) = (1.0+xi)/2.0;

            N.col(i) = EachGaussPointShapeFunction;



            //dNdxi

            Eigen::MatrixXd EachGaussPointdNdxi(VertexNum,1);
            //此处的1，是因为一维单元中只有xi参与形函数计算
            //故只对其有导数，如果为2维单元或者3维单元，则相应改为2或者3

            EachGaussPointdNdxi(0,0) = -1.0/2;
            EachGaussPointdNdxi(1,0) = 1.0/2;

            dNdxi.col(i) = EachGaussPointdNdxi;

        }
        break;
    }
    case Line3:
    {
        //线单元 三点
        dNdxi.resize(VertexNum,GaussPointNum);
        for (i = 0 ;i < GaussPointNum;i++)
        {

            Eigen::MatrixXd EachGaussPoint(1,dim);
            Eigen::MatrixXd EachGaussPointShapeFunction(VertexNum,1);
            // VertexNum = 3
            EachGaussPoint = LocalGaussPoint.row(i);

            double xi = EachGaussPoint(0,0);
            EachGaussPointShapeFunction(0,0) = -(1.0-xi)*xi/2.0;
            EachGaussPointShapeFunction(1,0) = (1.0+xi)*xi/2.0;
            EachGaussPointShapeFunction(2,0) = 1.0 - pow(xi,2);

            N.col(i) = EachGaussPointShapeFunction;

            //dNdxi

            Eigen::MatrixXd EachGaussPointdNdxi(VertexNum,1);
            //此处的1，是因为一维单元中只有xi参与形函数计算
            //故只对其有导数，如果为2维单元或者3维单元，则相应改为2或者3

            EachGaussPointdNdxi(0,0) = xi - 0.5;
            EachGaussPointdNdxi(1,0) = xi + 0.5;
            EachGaussPointdNdxi(2,0) = -2 * xi;

            dNdxi.col(i) = EachGaussPointdNdxi;
        }
        break;
    }
    case Triangle3:
    {
        //二维单元，在dNdxi中，形函数对每个高斯点的偏导数是两个
        dNdxi.resize(VertexNum,GaussPointNum * 2);
        for (i = 0 ;i < GaussPointNum;i++)
        {
            Eigen::MatrixXd EachGaussPoint(1,dim);
            Eigen::MatrixXd EachGaussPointShapeFunction(VertexNum,1);

            double xi = EachGaussPoint(0,0);
            double eta = EachGaussPoint(0,1);

            EachGaussPointShapeFunction(0,0) = 1.0-eta-xi;
            EachGaussPointShapeFunction(0,1) = xi;
            EachGaussPointShapeFunction(0,2) = eta;


            N.col(i) = EachGaussPointShapeFunction;
            //dNdxi

            Eigen::MatrixXd EachGaussPointdNdxi(VertexNum,2);
            EachGaussPointdNdxi << -1.0,-1.0,
                                    1.0,0.0,
                                    0.0,1.0;
            dNdxi.col(2*i) = EachGaussPointdNdxi.col(0);
            dNdxi.col(2*i+1) = EachGaussPointdNdxi.col(1);
        }
        break;
    }
    case Triangle4:
    {
        dNdxi.resize(VertexNum,GaussPointNum * 2);
        for (i = 0 ;i < GaussPointNum;i++)
        {
            Eigen::MatrixXd EachGaussPoint(1,dim);
            Eigen::MatrixXd EachGaussPointShapeFunction(VertexNum,1);

            double xi = EachGaussPoint(0,0);
            double eta = EachGaussPoint(0,1);

            EachGaussPointShapeFunction(0,0) = 1.0-eta-xi-3.0*eta*xi;
            EachGaussPointShapeFunction(0,1) = xi*(1-3*eta);
            EachGaussPointShapeFunction(0,2) = eta*(1-3*xi);
            EachGaussPointShapeFunction(0,3) = 9*xi*eta;


            N.col(i) = EachGaussPointShapeFunction;
            //dNdxi

            Eigen::MatrixXd EachGaussPointdNdxi(VertexNum,2);
            EachGaussPointdNdxi << -1.0-3*eta,-1.0-3*xi,
                                    1.0-3*eta,-3*xi,
                                    -3*eta,1.0-3*xi,
                                    9*eta,9*xi;
            dNdxi.col(2*i) = EachGaussPointdNdxi.col(0);
            dNdxi.col(2*i+1) = EachGaussPointdNdxi.col(1);
        }
        break;
    }
    case Triangle6:
    {
        dNdxi.resize(VertexNum,GaussPointNum * 2);
        for (i = 0 ;i < GaussPointNum;i++)
        {
            Eigen::MatrixXd EachGaussPoint(1,dim);
            Eigen::MatrixXd EachGaussPointShapeFunction(VertexNum,1);

            double xi = EachGaussPoint(0,0);
            double eta = EachGaussPoint(0,1);

            EachGaussPointShapeFunction(0,0) = 1-3*(xi+eta)+4*xi*eta+
                    2*(pow(xi,2)+pow(eta,2));
            EachGaussPointShapeFunction(0,1) = xi*(2*xi-1);
            EachGaussPointShapeFunction(0,2) = eta*(2*eta-1);
            EachGaussPointShapeFunction(0,3) = 4*xi*(1-xi-eta);
            EachGaussPointShapeFunction(0,4) = 4*xi*eta;
            EachGaussPointShapeFunction(0,5) = 4*eta*(1-xi-eta);


            N.col(i) = EachGaussPointShapeFunction;
            //dNdxi

            Eigen::MatrixXd EachGaussPointdNdxi(VertexNum,2);
            EachGaussPointdNdxi << 4*(xi+eta)-3,4*(xi+eta)-3,
                                    4*xi-1,0,
                                    0,4*eta-1,
                                    4*(1-eta-2*xi),-4*xi,
                                    4*eta,4*xi,
                                    -4*eta,4*(1-xi-2*eta);
            dNdxi.col(2*i) = EachGaussPointdNdxi.col(0);
            dNdxi.col(2*i+1) = EachGaussPointdNdxi.col(1);
        }
        break;
    }
    case Quadrilateral4:
    {
        //二维四边形

        dNdxi.resize(VertexNum,GaussPointNum * 2);
        for (i = 0 ;i < GaussPointNum;i++)
        {
            Eigen::MatrixXd EachGaussPoint(1,dim);
            Eigen::MatrixXd EachGaussPointShapeFunction(VertexNum,1);

            double xi = EachGaussPoint(0,0);
            double eta = EachGaussPoint(0,1);

            EachGaussPointShapeFunction <<  1/4*(1-xi)*(1-eta),
                                            1/4*(1+xi)*(1-eta),
                                            1/4*(1+xi)*(1+eta),
                                            1/4*(1-xi)*(1+eta);


            N.col(i) = EachGaussPointShapeFunction;
            //dNdxi

            Eigen::MatrixXd EachGaussPointdNdxi(VertexNum,2);
            EachGaussPointdNdxi << -(1-eta)*1/4,-(1-xi)*1/4,
                                        (1-eta)*1/4, -(1+xi)*1/4,
                                        (1+eta)*1/4,(1+xi)*1/4,
                                       -(1+eta)*1/4,(1-xi)*1/4;
            dNdxi.col(2*i) = EachGaussPointdNdxi.col(0);
            dNdxi.col(2*i+1) = EachGaussPointdNdxi.col(1);
        }
        break;
    }
    case Quadrilateral8:
    {
        //尚未完成
    }
    case Quadrilateral9:
    {
        dNdxi.resize(VertexNum,GaussPointNum * 2);
        for (i = 0 ;i < GaussPointNum;i++)
        {
            Eigen::MatrixXd EachGaussPoint(1,dim);
            Eigen::MatrixXd EachGaussPointShapeFunction(VertexNum,1);

            double xi = EachGaussPoint(0,0);
            double eta = EachGaussPoint(0,1);

            EachGaussPointShapeFunction <<  xi*eta*(xi-1)*(eta-1)*1/4,
                                            xi*eta*(xi+1)*(eta-1)*1/4,
                                            xi*eta*(xi+1)*(eta+1)*1/4,
                                            xi*eta*(xi-1)*(eta+1)*1/4,
                                           -2*eta*(xi+1)*(xi-1)*(eta-1)*1/4,
                                           -2*xi*(xi+1)*(eta+1)*(eta-1)*1/4,
                                           -2*eta*(xi+1)*(xi-1)*(eta+1)*1/4,
                                           -2*xi*(xi-1)*(eta+1)*(eta-1)*1/4;


            N.col(i) = EachGaussPointShapeFunction;
            //dNdxi

            Eigen::MatrixXd EachGaussPointdNdxi(VertexNum,2);
            EachGaussPointdNdxi << eta*(2*xi-1)*(eta-1),xi*(xi-1)*(2*eta-1),
                                    eta*(2*xi+1)*(eta-1)*1/4,xi*(xi+1)*(2*eta-1)*1/4,
                                    eta*(2*xi+1)*(eta+1)*1/4,xi*(xi+1)*(2*eta+1)*1/4,
                                    eta*(2*xi-1)*(eta+1)*1/4,xi*(xi-1)*(2*eta+1)*1/4,
                                    -4*xi*eta*(eta-1)*1/4,-2*(xi+1)*(xi-1)*(2*eta-1)*1/4,
                                    -2*(2*xi+1)*(eta+1)*(eta-1)*1/4,-4*xi*eta*(xi+1)*1/4,
                                    -4*xi*eta*(eta+1)*1/4,-2*(xi+1)*(xi-1)*(2*eta+1)*1/4,
                                    -2*(2*xi-1)*(eta+1)*(eta-1)*1/4,-4*xi*eta*(xi-1)*1/4,
                                    8*xi*(pow(eta,2)-1)*1/4,8*eta*(pow(xi,2)-1)*1/4;
            dNdxi.col(2*i) = EachGaussPointdNdxi.col(0);
            dNdxi.col(2*i+1) = EachGaussPointdNdxi.col(1);
        }
        break;
    }
    case Tetrahedron4:
    {
        // 3维单元
        dNdxi.resize(VertexNum,GaussPointNum * 3);
        for (i = 0 ;i < GaussPointNum;i++)
        {
            Eigen::MatrixXd EachGaussPoint(1,dim);
            Eigen::MatrixXd EachGaussPointShapeFunction(VertexNum,1);

            double xi = EachGaussPoint(0,0);
            double eta = EachGaussPoint(0,1);
            double zeta = EachGaussPoint(0,2);

            EachGaussPointShapeFunction << 1-xi-eta-zeta,
                                                    xi,
                                                   eta,
                                                  zeta;
            N.col(i) = EachGaussPointShapeFunction;

            Eigen::MatrixXd EachGaussPointdNdxi(VertexNum,3);

            EachGaussPointdNdxi << -1,-1,-1,
                                    1,0,0,
                                    0,1,0,
                                    0,0,1;
            dNdxi.col(3*i) = EachGaussPointdNdxi.col(0);
            dNdxi.col(3*i+1) = EachGaussPointdNdxi.col(1);
            dNdxi.col(3*i+2) = EachGaussPointdNdxi.col(2);
        }
        break;
    }
    case Hexahedron8:
    {
        //尚未完成
    }
    default:
    {
        //表示不需要做数值积分
        N.resize(1,1);
        N(0,0) = 0.0;
        dNdxi.resize(1,1);
        dNdxi(0,0) = 0.0;
        break;
    }
    }
}

*/
