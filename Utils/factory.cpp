#include "factory.h"
#include "../Geo/vertex.h"
#include "../Geo/quadelement.h"
#include "../Geo/truss.h"
#include "../Geo/BeamEB2.h"
#include "../MaterialProp/isolinearstrumat.h"
#include "../MaterialProp/orthlinearstrumat.h"
#include "../EleProp/beamprop.h"
#include "../EleProp/trussprop.h"
#include "../Load/NodeLoad.h"
#include "../Load/PressureLoadOnLine.h"
#include "../Constraint/DiricheletBC.h"


Factory::Factory()
{

}

Vertex* Factory::CreateVertex(int VertexId,
                              double x, double y, double z,int SPCsNum)
{
    return new Vertex(VertexId,x,y,z,SPCsNum);
}

Element* Factory::CreateElement(int ElementId,
                                int MaterialId,
                                ElementType eletype,
								const Eigen::MatrixXi& VertexIdArray)
{
    switch(eletype)
    {
        case LINE2:
        {

        }
        case LINE3:
        {

        }
        case TRIANGLE3:
        {

        }
        case TRIANGLE4:
        {

        }
        case TRIANGLE6:
        {

        }
        case QUADRILATERAL4:
        {
            return new QuadElement(ElementId,MaterialId,
                                   eletype,VertexIdArray);
        }
		case QUADRILATERAL8:
        {

        }
		case QUADRILATERAL9:
        {

        }
        case TETRAHEDRON4:
        {

        }
        case HEXAHEDRON8:
        {

        }

    }
    return NULL;
}

Element* Factory::CreateElement(int ElementId,
                                int MaterialId,
                                int EPropId,
                                ElementType eletype,
								const Eigen::MatrixXi& VertexIdArray)
{

    switch(eletype)
    {
        case TRUSS:
        {
            return new Truss(ElementId,MaterialId,
                             EPropId,eletype,VertexIdArray);
        }
        case BEAMEB2:
        {
			return new BeamEB2(ElementId, MaterialId,
				EPropId, eletype, VertexIdArray);
        }
		case BEAMEB3:
		{

		}
		case BEAMT2:
		{

		}
		case BEAMT3:
		{

		}
        case SHELL:
        {

        }
    }
    return NULL;

}

Mat* Factory::CreateMat(int MaterialId, const std::string& LinearOrNot,
	const std::string& IsoOrNot, const std::map<std::string, double> PropNameAndPropValue,
	const std::string& DimAndMatStatus)
{

	Mat *mat;
	if (LinearOrNot == "Linear" && IsoOrNot == "Iso")
	{
		mat = new IsoLinearStruMat(MaterialId);
	}
	else if (LinearOrNot == "Linear" && IsoOrNot == "Orth")
	{
		mat = new OrthLinearStruMat(MaterialId);
	}

	if (mat->SetValue(PropNameAndPropValue) == 0)
	{
		printf("错误：没有设置材料属性项目\n");
	}

	if (mat->SetDimAndMatStatus(DimAndMatStatus) == 0)
	{
		printf("错误：无法设置维度项目\n");
	}
	return mat;
}

EProp* Factory::CreateEProp(int EPropId, const string& ElementPropName,
	const std::map<std::string, double>& PropNameAndPropValue)
{
	EProp* EP;

	if (ElementPropName == "Beam")
	{
		EP = new BeamProp(EPropId);
		
	}
	else if (ElementPropName == "Truss")
	{
		EP = new TrussProp(EPropId);
	}

	EP->SetValue(PropNameAndPropValue);

	return EP;
}

Load* Factory::CreateLoad(int LoadId,
	const Eigen::MatrixXi& NodeId,
	const Eigen::MatrixXd& Value)
{

	int NodeId_ = NodeId(0, 0);
	return new NodeLoad(LoadId,NodeId_,Value);
}

Load* Factory::CreateLoad(int LoadId,const std::string& LoadName,
	int ElementId,
	const Eigen::VectorXi& NodeId,
	const Eigen::MatrixXd& Value)
{
	if (LoadName.find("PressureOnLine") != std::string::npos)
	{
		return new PressureLoadOnLine(LoadId, ElementId, NodeId, Value);
	}
	else
	{

	}
}

Constraint* Factory::CreateConstraint(int ConstraintId, const std::string& ConstraintName,
	int NodeId, DOFVar DF, double Value)
{
	if (ConstraintName == "Dirichelet")
	{
		return new DirichletBC(ConstraintId, NodeId, DF, Value);
	}
}
