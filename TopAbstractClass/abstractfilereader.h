#ifndef ABSTRACTFILEREADER_H
#define ABSTRACTFILEREADER_H

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include "../File/inputcard.h"


class AbstractFileReader
{
public:
    enum InputItemType
    {
        AnalysisType,
        Vertex,
        Element,
        Material,
        ElementProp,
        Constraint,
        Load
    };



    virtual ~AbstractFileReader() = 0;

    InputCard* GetInputCard(InputItemType itType);

    void ReadLine(std::string& returnstring);
    std::string GetInputFile() {return InputFilePathAndName;}


protected:
    AbstractFileReader(const std::string& InputPath,const std::string& InputFile);

protected:
    std::string InputFilePathAndName;
    std::ifstream ReadInputFileStream; //读文件流

    InputCard* TitleInputCard;
    InputCard* AnalysisInputCard;
    InputCard* PointInputCard;
    InputCard* ElementInputCard;
    InputCard* MaterialInputCard;
    InputCard* ElementPropInputCard;
    InputCard* ConstraintInputCard;
    InputCard* LoadInputCard;

};

#endif // ABSTRACTFILEREADER_H
