//
// Created by 杨文露 on 2019-03-12.
//

#ifndef CPP_FEM_ABSTRACTBEAM_H
#define CPP_FEM_ABSTRACTBEAM_H

#include <Eigen/Eigen>

using namespace Eigen;

class abstractBeam
{
public:
    abstractBeam(const MatrixXi& VertexId);
    virtual ~abstractBeam() = 0;


private:

};


#endif //CPP_FEM_ABSTRACTBEAM_H
