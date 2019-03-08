#ifndef ABASTRACTELEMENTPROP_H
#define ABASTRACTELEMENTPROP_H

#include <map>
#include <iostream>
#include "EPropvar.h"

using namespace std;

class EProp
{
public:
    EProp(int id);
	virtual ~EProp() = 0;

	int GetId();
	int hasProp(EPropVar EP);
	int GetValue(EPropVar EP, double *Value);

	virtual int SetValue(const std::map<std::string, double>& EPropNameAndValue) = 0;

	

protected:
	int id;      //��Ԫ����ID

	map<EPropVar, double> EPropd;

protected:
	int __SetValue(EPropVar EP, double Value);

};

#endif // ABASTRACTELEMENTPROP_H
