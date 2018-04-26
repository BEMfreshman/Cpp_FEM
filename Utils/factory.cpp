#include "factory.h"
#include "../Geo/vertex.h"
#include "../Geo/quadelement.h"
#include "../Geo/truss.h"
#include "../Geo/BeamEB2.h"
#include "../MaterialProp/isolinearstrumat.h"
#include "../MaterialProp/orthlinearstrumat.h"
#include "../EleProp/beamprop.h"
#include "../EleProp/trussprop.h"


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
                                Element::ElementType eletype,
								const Eigen::MatrixXi& VertexIdArray)
{
    switch(eletype)
    {
        case Element::Line2:
        {

        }
        case Element::Line3:
        {

        }
        case Element::Triangle3:
        {

        }
        case Element::Triangle4:
        {

        }
        case Element::Triangle6:
        {

        }
        case Element::Quadrilateral4:
        {
            return new QuadElement(ElementId,MaterialId,
                                   eletype,VertexIdArray);
        }
        case Element::Quadrilateral8:
        {

        }
        case Element::Quadrilateral9:
        {

        }
        case Element::Tetrahedron4:
        {

        }
        case Element::Hexahedron8:
        {

        }

    }
    return NULL;
}

Element* Factory::CreateElement(int ElementId,
                                int MaterialId,
                                int EPropId,
                                Element::ElementType eletype,
								const Eigen::MatrixXi& VertexIdArray)
{

    switch(eletype)
    {
        case Element::Truss:
        {
            return new Truss(ElementId,MaterialId,
                             EPropId,eletype,VertexIdArray);
        }
        case Element::BeamEB2:
        {
			return new BeamEB2(ElementId, MaterialId,
				EPropId, eletype, VertexIdArray);
        }
		case Element::BeamEB3:
		{

		}
		case Element::BeamT2:
		{

		}
		case Element::BeamT3:
		{

		}
        case Element::Shell:
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
