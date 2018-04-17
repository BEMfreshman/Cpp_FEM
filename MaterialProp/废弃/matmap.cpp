#include "matmap.h"

MatMap::MatMap()
{

}

MatMap::~MatMap()
{
    if(!(matmap.empty()))
    {
        matmap.clear();
    }
}

int MatMap::MatNum()
{
    return matmap.size();
}

void MatMap::addMat(Mat *material)
{
    int MatId = material->GetId();
    matmap.insert(std::map<int,Mat*>::value_type(MatId,material));
}

void MatMap::delMat(int MatId)
{
    int ierr = matmap.erase(MatId);
    if(ierr == 0)
    {
        printf("材料删除失败");
        exit(1);
    }
}


Mat* MatMap::GetMat(int MatId)
{
    std::map<int,Mat*>::iterator it;
    it = matmap.find(MatId);
    if(it !=matmap.end())
    {
        return it->second;
    }
    else
    {
        return NULL;
    }
}
