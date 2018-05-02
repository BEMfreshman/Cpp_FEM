﻿#ifndef POINT_H
#define POINT_H

/*
 * 点单元
 */
#include "../TopAbstractClass/abstractelement.h"


class Point: public Element
{
public:
    Point();
    Point(int ElementId,
          int MaterialId,
          int EPropId,
          ElementType eletype,
          const Eigen::MatrixXi& VertexIdArray);

    Point(const Point& that);
    Point& operator=(const Point& that);

    Element* Clone() const;

    ~Point();
	
	int GetSpecificMatrix(SparseMatrixType SMT, vector<T_>& tripleList);
	int SetDOF(int dim);

	virtual ElementType GetElementType();

protected:
	int ComputeStiffnessMatrix(Eigen::MatrixXd& matReturn);

	void GenerateLoacalGaussPointAndWeight(int Order);
	int ComputeShapeFunction(ShapeFunType SFT);

};

#endif // POINT_H
