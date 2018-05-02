#ifndef TRUSS_H
#define TRUSS_H
//#include "../TopAbstractClass/abstractelement.h"
#include "Line2.h"

/*
 * 杆单元
 */

class Truss:public Line2
{
public:
    Truss();
    Truss(int ElementId,
          int MaterialId,
          int EPropId,
          ElementType eletype,
		  const Eigen::MatrixXi& VertexIdArray);

    ~Truss();

    Truss(const Truss& that);
    Truss& operator=(const Truss& that);

    Element* Clone() const;

	int GetSpecificMatrix(SparseMatrixType SMT, vector<T_>& tripleList);
	
	int SetDOF(int dim);

	ElementType GetElementType();

protected:
	int ComputeStiffnessMatrix(Eigen::MatrixXd& matReturn);
	int ComputeMassMatrix(Eigen::MatrixXd& matReturn);

};

#endif // TRUSS_H
