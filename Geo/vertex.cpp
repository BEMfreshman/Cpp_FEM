#include "vertex.h"
#include <vector>
#include "../TopAbstractClass/Dof.h"


Vertex::Vertex(int Id, double x, double y, double z, int SPCsNum) :DofManager(0,SPCsNum)
{
    this->Id = Id;
    this->x = x;
    this->y = y;
    this->z = z;
}

//Vertex::Vertex(const Vertex& vertex):Id(vertex.Id),
//    x(vertex.x),y(vertex.y),z(vertex.z)
//{
//    //拷贝构造
//}

//Vertex& Vertex::operator =(const Vertex& that)
//{
//    if(&that != this)
//    {
//        //首先释放旧资源，这里没有需要delete的资源
//        this->Id = that.Id;
//        this->x = that.x;
//        this->y = that.y;
//        this->z = that.z;
//    }
//    return *this;
//}

//Vertex* Vertex::Clone() const
//{
//    return new Vertex(*this);
//}

double Vertex::GetX() const
{
    return x;
}

double Vertex::GetY() const
{
    return y;
}

double Vertex::GetZ() const
{
    return z;
}

int Vertex::SetDOF(int dim, ElementType ET)
{
	
	if (dim == 1)
	{
		if (ET == BEAMEB2)
		{
			DOF* dof_v = new DOF(1, findSPCValid(v), v);
			DOF* dof_tx = new DOF(2, findSPCValid(tx), tx);

			addDOF(dof_v);
			addDOF(dof_tx);
		}
	}
	else
	{
		if (ET == BEAMEB2)
		{
			DOF* dof_u = new DOF(1, findSPCValid(u), u);
			DOF* dof_v = new DOF(2, findSPCValid(v), v);
			DOF* dof_tx = new DOF(3, findSPCValid(tx), tx);

			addDOF(dof_u);
			addDOF(dof_v);
			addDOF(dof_tx);
		}
	}
	return 1;
}
