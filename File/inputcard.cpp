#include "inputcard.h"


InputCard::InputCard()
{

}


InputCard::~InputCard()
{
    size_t Vecsize = inputcard.size();
    if(Vecsize != 0)
    {
        std::vector<InputItem*>::iterator it;
        for(it = inputcard.begin();it!=inputcard.end();it++)
        {
            delete (*it);
            (*it) = NULL;
        }
    }
}


void InputCard::addInputItem(InputItem * inputitem)
{
    inputcard.push_back(inputitem);
}

size_t InputCard::sizeofInputCard()
{
    return inputcard.size();
}

InputItem* InputCard::GetInputItem(int id)
{
    return inputcard[id];
}
