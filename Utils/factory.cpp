#include "factory.h"
#include "../Geo/vertex.h"
#include "../Geo/quadelement.h"
#include "../Geo/truss.h"


Factory::Factory()
{

}

Vertex* Factory::CreateVertex(int VertexId,
                              double x,double y)
{
    return new Vertex(VertexId,x,y);
}

Vertex* Factory::CreateVertex(int VertexId,
                              double x, double y, double z)
{
    return new Vertex(VertexId,x,y,z);
}

Element* Factory::CreateElement(int ElementId,
                                int MaterialId,
                                Element::ElementType eletype,
                                Eigen::MatrixXi VertexIdArray)
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
            break;
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
                                Eigen::MatrixXi VertexIdArray)
{

    switch(eletype)
    {
        case Element::Truss:
        {
            return new Truss(ElementId,MaterialId,
                             EPropId,eletype,VertexIdArray);
            break;
        }
        case Element::Beam:
        {

        }
        case Element::Shell:
        {

        }
    }
    return NULL;

}
