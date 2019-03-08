#include "abstractfilereader.h"
#include "../File/inputitem.h"
AbstractFileReader::AbstractFileReader(const std::string& InputPath,
                                       const std::string& InputFile)
{
    //记录输入文件的位置与名称，打开输入流
    InputFilePathAndName = InputPath + "\\" + InputFile;
    ReadInputFileStream.open(InputFilePathAndName.c_str(),std::ios::in);
    if(!ReadInputFileStream.is_open())
    {
        std::cerr << "错误，未能打开文件" << InputFile << std::endl;
        exit(1);
    }
}

AbstractFileReader::~AbstractFileReader()
{
    ReadInputFileStream.close();
}

InputCard* AbstractFileReader::GetInputCard(InputItemType itType)
{
    switch (itType)
    {
    case AnalysisType:
        return AnalysisInputCard;
        break;
    case Vertex:
        return PointInputCard;
        break;
    case Element:
        return ElementInputCard;
        break;
    case Material:
        return MaterialInputCard;
        break;
    case ElementProp:
        return ElementPropInputCard;
        break;
    case Constraint:
        return ConstraintInputCard;
        break;
    case Load:
        return LoadInputCard;
        break;
    default:
        std::cout << "未知关键字\n" << std::endl;
        return nullptr;
    }
}
