#ifndef INPUTITEM_H
#define INPUTITEM_H

#include <iostream>
#include <string>
#include <vector>
#include "inputitemname.h"
#include "../Utils/utilfunction.h"
#include "Eigen/Eigen"
/*
 * 每次读取一行内容
 * 每行内容均为子关键字加数据体的形式
 * 数据体的格式为：
 * String
 * Int
 * Double
 * Bool
 * 数组（double）,用std::vector返回
 * Matrix
 * 尽可能不要在同一个数据体中存放多种数据格式
 */

class InputItem
{
public:

    InputItem(const std::string& inputitem,int RowId);
    ~InputItem();

    std::string GetKeyWord();

    int GetDataByItemName(int* Data,InputItemName inputitemname); //成功返回1，失败返回0
    int GetDataByItemName(double* Data,InputItemName inputitemname);
    int GetDataByItemName(std::vector<int>& Data,InputItemName inputitemname);
    int GetDataByItemName(std::vector<double>& Data,InputItemName inputitemname);
    int GetDataByItemName(Eigen::MatrixXi& Data,InputItemName inputitemname);
    int GetDataByItemName(Eigen::MatrixXd &Data,InputItemName inputitemname);
    int GetDataByItemName(std::string& Data,InputItemName inputitemname);
    int GetDataByItemName(std::map<std::string,double> Data,InputItemName inputitemname);

    void GetData(bool* Data);


protected:
    const std::string inputitem; // 输入的字符串
    int RowId;            // 目前读取的这一行的行号

    std::string KeyWord;

    std::vector<std::string> splitstr;

    char seperateChar;

    int NumofSplitStr;   //分割后产生的有效输入的个数（可能其中有空格，所以不可直接用splitstr.size()计算）

protected:
    int GetDataI(int pos);       //返回第pos这个位置的单个数据
    double GetDataD(int pos);
    std::string GetDataStr(int pos);


    void GetData(std::vector<int>& Data);    // 返回数组
    void GetData(std::vector<double>& Data); //返回数组

    void GetData(int* Data);           // 返回单个数据

    void GetData(Eigen::MatrixXi& Data);//尽可能用这个函数

    void GetData(Eigen::MatrixXd& Data);//尽可能用这个函数
};

#endif // INPUTITEM_H
