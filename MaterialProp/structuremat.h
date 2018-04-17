#ifndef STRUCTUREMAT_H
#define STRUCTUREMAT_H

#include "../TopAbstractClass/abstractmaterial.h"
#include "../TopAbstractClass/matpropvar.h"


class StructureMat:public Mat
{
public:
    StructureMat();
    virtual ~StructureMat() = 0;
};

#endif // STRUCTUREMAT_H
