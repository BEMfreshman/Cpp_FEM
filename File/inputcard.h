#ifndef INPUTCARD_H
#define INPUTCARD_H
#include "inputitem.h"
#include <vector>

/*
 * InputCard为某种Inputitem的集合，
 * 用std::vector<InputItem *>组织起来
 */




class InputCard
{
public:
    InputCard();
    ~InputCard();

public:

    void addInputItem(InputItem* inputitem);
    size_t sizeofInputCard();
    InputItem* GetInputItem(int id);

private:
    std::vector<InputItem *> inputcard;
};

#endif // INPUTCARD_H
