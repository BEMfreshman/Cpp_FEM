#ifndef MATMAP_H
#define MATMAP_H

/*
 * 采用STL中的map处理数据体
 * key --- 材料ID
 * value --- Mat*
 */

#include <map>
#include <algorithm>
#include "mat.h"

class MatMap
{
public:
    MatMap();

    ~MatMap();

    void addMat(Mat* material);
    void delMat(int MatId);
    int MatNum(); // 返回Material的总个数

    Mat* GetMat(int MatId);

private:
    std::map<int,Mat*> matmap;
};

#endif // MATMAP_H
