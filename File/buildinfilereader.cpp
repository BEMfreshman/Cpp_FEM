#include "buildinfilereader.h"

BuildInFileReader::BuildInFileReader(const std::string& InputPath,
                                     const std::string& InputFile):
    AbstractFileReader(InputPath,InputFile)
{
    std::string line;
    std::getline(ReadInputFileStream,line);

    TitleInputCard       = new InputCard();
    AnalysisInputCard    = new InputCard();
    PointInputCard       = new InputCard();
    ElementInputCard     = new InputCard();
    MaterialInputCard    = new InputCard();
    ElementPropInputCard = new InputCard();
    ConstraintInputCard  = new InputCard();
    LoadInputCard        = new InputCard();

    int RowId = 0;
    bool FirstReadKeyWordFlag = false;
    //是否是首次读到该数据体
    BuildinKeyWord ControlNum;
    //ControlNum用于控制读入过程
    while(ReadInputFileStream)
    {
        /* 读入一行文本
         * 没有读到文件尾则一直读入
         */
        char FirstChar = line[0];
        //用来判断是否为注释语言或者为关键字开头
        if(FirstChar == '#')
        {
            std::getline(ReadInputFileStream,line);
            RowId++;
            continue;
        }

        if(line.empty())
        {
            //空字符串
            std::getline(ReadInputFileStream,line);
            RowId++;
            continue;
        }

        //内建输入文件InputCard关键字开头
        BuildinKeyWord kw = SwitchFromKeyWordToEnum(line);

        //2017.10.11 下面将按照MyEFGCpp中读文件的方式完成
        //每次读到一句话就进行一次关键字判定，如果有关键字，
        //则按照相关的处理进行，如果没有，则按照上一次的处理规则进行

        if(kw != None)
        {
            ControlNum = kw;
            FirstReadKeyWordFlag = true;
            //如果是AnalysisType,Point...等关键字中的任意一个
            //即更新ControlNum中的值
        }
        else
        {
            FirstReadKeyWordFlag = false;
        }

        /*
         * 关键字的写法有两种：
         * 一种是单一keyword，单一值
         * 例如：
         * *Analysis 103
         * 这种采用
         *
         * 第二种是Element，Point，ElementProp，Material等多行
         * 参数体，例如：
         * *Element
         * Beam3 1 2 ....
         */







        switch (ControlNum)
        {
        case AnalysisType:
        {
            InputItem* inputitem = new InputItem(line,RowId);
            AnalysisInputCard->addInputItem(inputitem);
            break;
        }
        case Vertex:
        {
            //多行数据体
            if(FirstReadKeyWordFlag == true)
            {
                std::getline(ReadInputFileStream,line);
                RowId++;
            }
            std::string newline = "Vertex," + line;
            InputItem* inputitem = new InputItem(newline,RowId);
            PointInputCard->addInputItem(inputitem);
            break;
        }
        case Element:
        {
            //多行数据体
            if(FirstReadKeyWordFlag == true)
            {
                std::getline(ReadInputFileStream,line);
                RowId++;
            }
            //单元的每一行的第一个词语就是其关键字
            //以下的情况同理
            std::string newline = "Element," + line;
            InputItem* inputitem = new InputItem(newline,RowId);
            ElementInputCard->addInputItem(inputitem);
            break;
        }
        case Material:
        {
            if(FirstReadKeyWordFlag == true)
            {
                std::getline(ReadInputFileStream,line);
                RowId++;
            }
            //材料每行的关键字是其属性（各向同性，各向异性等等）
            std::string newline = "Material," + line;
            InputItem* inputitem = new InputItem(newline,RowId);
            MaterialInputCard->addInputItem(inputitem);
            break;
        }
        case ElementProp:
        {
            if(FirstReadKeyWordFlag == true)
            {
                std::getline(ReadInputFileStream,line);
                RowId++;
            }
            //单元属性每行的关键字是单元种类（梁单元，杆单元，壳单元等等）
            std::string newline = "ElementProp," + line;
            InputItem* inputitem = new InputItem(newline,RowId);
            ElementPropInputCard->addInputItem(inputitem);
            break;
        }
        case Constraint:
        {
            if(FirstReadKeyWordFlag == true)
            {
                std::getline(ReadInputFileStream,line);
                RowId++;
            }
            //约束每行关键字是约束的种类（单点约束，多点约束等等）
            std::string newline = "Constraint," + line;
            InputItem* inputitem = new InputItem(newline,RowId);
            ConstraintInputCard->addInputItem(inputitem);
            break;
        }
        case Load:
        {
            if(FirstReadKeyWordFlag == true)
            {
                std::getline(ReadInputFileStream,line);
                RowId++;
            }




            // 尚未想好


            std::string newline = "Load," + line;
            InputItem* inputitem = new InputItem(newline,RowId);
            LoadInputCard->addInputItem(inputitem);
            break;
        }
        }
        std::getline(ReadInputFileStream,line);
        RowId++;
    }
    //读文件完成，
    //文件中的数据字段均存放在各自的容器中

    //将该类的实例投给Factory类，自动生成所有计算需要用到的类的实例
}


BuildinKeyWord BuildInFileReader::SwitchFromKeyWordToEnum(const std::string& keyword)
{
    std::string::size_type idx;

    if((idx = keyword.find("*Analysis")) != std::string::npos)
    {
        return AnalysisTypeKW;
    }
    else if((idx = keyword.find("*Point")) != std::string::npos)
    {
        return PointKW;
    }
    else if((idx = keyword.find("*Element")) != std::string::npos)
    {
        return ElementKW;
    }
    else if((idx = keyword.find("*ElementProp")) != std::string::npos)
    {
        return ElementPropKW;
    }
    else if((idx = keyword.find("*Material")) != std::string::npos)
    {
        return MaterialKW;
    }
    else if((idx = keyword.find("*Constraint")) != std::string::npos)
    {
        return ConstraintKW;
    }
    else if((idx = keyword.find("*Load")) != std::string::npos)
    {
        return LoadKW;
    }
    else
    {
        return None;
    }

}
