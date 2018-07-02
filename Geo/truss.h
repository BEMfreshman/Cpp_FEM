﻿#ifndef TRUSS_H
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
		  int dim,
		  const Eigen::MatrixXi& VertexIdArray);

    ~Truss();

    Truss(const Truss& that);
    Truss& operator=(const Truss& that);

    Element* Clone() const;

	int GetSpecificMatrix(SparseMatrixType SMT,
		const LoadType LT,
		vector<T_>& tripleList);
	
	int SetDOF(int dim);

	ElementType GetElementType();

protected:
	int ComputeStiffnessMatrix(vector<T_>& tripleList);
	int ComputeMassMatrix(vector<T_>& tripleList);

};

#endif // TRUSS_H
