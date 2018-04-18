#include "inputitem.h"

InputItem::InputItem(const std::string& inputitemReadFromFile,int RowIdReadFromFile)
    :inputitem(inputitemReadFromFile),RowId(RowIdReadFromFile)
{
    /*
    SeperateKeyWordAndData(KeyWord,DataStr);
    DataStrUseToSeperate = DataStr;
    */

    size_t pos = 0;
    size_t sizeofstr = inputitem.size();
    pos = inputitem.find(",");
    if(pos != std::string::npos)
    {
        //表示找到，说明文本中有","
        seperateChar = ',';
    }
    else
    {
        pos = inputitem.find(" ");
        if(pos != std::string::npos)
        {
            seperateChar = ',';
        }
        else
        {
            std::cout <<"错误：输入文件中第" << RowId <<"行有错误" <<std::endl;
            std::cout <<"程序退出" << std::endl;
            exit(1);
        }
    }

    SplitString(inputitem,seperateChar,splitstr);

    KeyWord = GetDataStr(1);

    NumofSplitStr = 0;
    for(int i = 0; i < splitstr.size();i++)
    {
        if(splitstr[i] != "")
        {
            NumofSplitStr++;
        }
    }

}

InputItem::~InputItem()
{

}

std::string InputItem::GetKeyWord()
{
    return KeyWord;
}

int InputItem::GetDataI(int pos)
{
    for(int i = 0,validValueCounter = 0;i < splitstr.size();i++)
    {
        if(splitstr[i] != "")
        {
            validValueCounter++;
        }

        if(validValueCounter == pos)
        {
            int ReturnValue;
            std::stringstream sstr;
            sstr << splitstr[i];
            sstr >> ReturnValue;
            return ReturnValue;
        }
    }
}

double InputItem::GetDataD(int pos)
{
    for(int i = 0,validValueCounter = 0;i < splitstr.size();i++)
    {
        if(splitstr[i] != "")
        {
            validValueCounter++;
        }

        if(validValueCounter == pos)
        {
            double ReturnValue;
            std::stringstream sstr;
            sstr << splitstr[i];
            sstr >> ReturnValue;
            return ReturnValue;
        }
    }
}

std::string InputItem::GetDataStr(int pos)
{
    for(int i = 0,validValueCounter = 0;i < splitstr.size();i++)
    {
        if(splitstr[i] != "")
        {
            validValueCounter++;
        }

        if(validValueCounter == pos)
        {
            return splitstr[i];
        }
    }
}

int InputItem::GetDataByItemName(std::map<std::string,double> Data,InputItemName inputitemname)
{
    switch(inputitemname)
    {
        case Mat_PropNameAndPropValue:
        {
            //从第5个开始，字符串和数字交替
            std::string PropName;
            double PropValue;
            int Counter = 0;
            for(int i = 5 ; i <= NumofSplitStr;i++)
            {
                if(i % 2 == 1)
                {
                    PropName = GetDataStr(i);
                    Counter++;
                }
                else
                {
                    PropValue = GetDataD(i);
                    Counter++;
                }

                if(Counter % 2 == 0 && Counter != 0)
                {
                    Data[PropName] = PropValue;
                }
            }
			return 1;

        }
        case EProp_PropNameAndPropValue:
        {
            //从第4个开始，字符串和数字交替
            std::string PropName;
            double PropValue;
            int Counter = 0;
            for(int i = 4 ; i <= NumofSplitStr;i++)
            {
                if(i % 2 == 1)
                {
                    PropName = GetDataStr(i);
                    Counter++;
                }
                else
                {
                    PropValue = GetDataD(i);
                    Counter++;
                }

                if(Counter % 2 == 0 && Counter != 0)
                {
                    Data[PropName] = PropValue;
                }
            }
			return 1;
        }
    }
}



int InputItem::GetDataByItemName(std::string& Data,InputItemName inputitemname)
{
    switch(inputitemname)
    {
        case Analysis_SolType:
        {
            Data = GetDataStr(3);
            return 1;
        }
        case Element_Type:
        {
            Data = GetDataStr(3);
            return 1;
        }
        case Mat_LinearOrNot:
        {
            Data = GetDataStr(3);
            return 1;
        }
        case Mat_IsoOrNot:
        {
        Data = GetDataStr(4);
        return 1;
        }
        case EProp_ElementName:
        {
            Data = GetDataStr(3);
            return 1;
        }
    }
}

int InputItem::GetDataByItemName(int* Data,InputItemName inputitemname)
{
    switch (inputitemname)
    {
        case Analysis_SolNum:
        {
            (*Data) = GetDataI(2);
            return 1;
        }
        case Vertex_Id:
        {
            (*Data) = GetDataI(2);
            return 1;
        }
        case Element_Id:
        {
            (*Data) = GetDataI(2);
            return 1;
        }
        case Element_MatId:
        {
            std::string EleType;
            GetDataByItemName(EleType,Element_Type);
            if(EleType == "Line2" ||
                    EleType == "Truss" ||
                    EleType == "Beams")
            {
                (*Data) = GetDataI(6);
                return 1;
            }
            else if(EleType == "Line3" ||
                    EleType == "Triagnle3")
            {
                (*Data) = GetDataI(7);
                return 1;
            }
            else if(EleType == "Triangle4" ||
                    EleType == "Quad4" ||
                    EleType == "Tet4" ||
                    EleType == "Shell")
            {
                (*Data) = GetDataI(8);
                return 1;
            }
            else if(EleType == "Triangle6")
            {
                (*Data) = GetDataI(10);
                return 1;
            }
            else if(EleType == "Quad8" ||
                    EleType == "Hex8")
            {
                (*Data) = GetDataI(12);
                return 1;
            }
            else
            {
                (*Data) = 0;
                return 0;
            }

        }
        case Element_EPropId:
        {
            std::string EleType;
            GetDataByItemName(EleType,Element_Type);
            if(EleType == "Truss" || EleType == "Beam")
            {
                (*Data) = GetDataI(7);
                return 1;
            }
            else if(EleType == "Shell")
            {
                (*Data) = GetDataI(9);
                return 1;
            }
            else
            {
                (*Data) = 0;
                return 0;
            }
        }
        case Mat_Id:
        {
            (*Data) = GetDataI(2);
            return 1;
        }
        case EProp_Id:
        {
            (*Data) = GetDataI(2);
            return 1;
        }
        default:
        {
            (*Data) = 0;
            return 1;
        }
    }
}

int InputItem::GetDataByItemName(double* Data,InputItemName inputitemname)
{
    switch (inputitemname)
    {
        case Vertex_CoordX:
        {
            (*Data) = GetDataD(3);
            return 1;
        }
        case Vertex_CoordY:
        {
            (*Data) = GetDataD(4);
            return 1;
        }
        case Vertex_CoordZ:
        {
            if(NumofSplitStr<5)
            {
                //没有Z坐标
                (*Data) = 0.0;
                return 0;
            }
            else
            {
                (*Data) = GetDataD(5);
                return 1;
            }
        }
    }
}

int InputItem::GetDataByItemName(std::vector<int>& Data,InputItemName inputitemname)
{
	return 0;
}

int InputItem::GetDataByItemName(std::vector<double>& Data,InputItemName inputitemname)
{
	return 0;
}

int InputItem::GetDataByItemName(Eigen::MatrixXi& Data,InputItemName inputitemname)
{
    int VertexId;     //记录单元顶点的坐标
    switch (inputitemname)
    {
        case Element_VertexIdArray:
        {
            std::string EleType;
            GetDataByItemName(EleType,Element_Type);

            if(EleType == "Line2")
            {

                Data.resize(1,2);

                for(int i = 4; i < 6;i++)
                {
                    //取第4个和第5个数据
                    VertexId = GetDataI(i);
                    Data << VertexId;
                }
                return 1;
            }
            else if(EleType == "Line3" || EleType == "Triangle3")
            {
                Data.resize(1,3);

                for(int i = 4; i < 7;i++)
                {
                    //取第4,5,6个数据
                    VertexId = GetDataI(i);
                    Data << VertexId;
                }
                return 1;
            }
            else if(EleType == "Triangle4" || EleType == "Quad4" || EleType == "Tet4")
            {
                Data.resize(1,4);

                for(int i = 4; i < 8;i++)
                {
                    //取第4,5,6,7个数据
                    VertexId = GetDataI(i);
                    Data << VertexId;
                }
                return 1;
            }
            else if(EleType == "Triangle6")
            {
                Data.resize(1,6);

                for(int i = 4; i < 10;i++)
                {
                    //取第4,5,6,7,8,9个数据
                    VertexId = GetDataI(i);
                    Data << VertexId;
                }
                return 1;
            }
            else if(EleType == "Quad8" || EleType == "Hex8")
            {
                Data.resize(1,8);
                for(int i = 4; i < 12;i++)
                {
                    //取第4,5,6,7,8,9,10,11个数据
                    VertexId = GetDataI(i);
                    Data << VertexId;
                }
                return 1;
            }
            else
            {
                Data.resize(1,1);
                return 0;
            }

        }
    }
}

int InputItem::GetDataByItemName(Eigen::MatrixXd &Data,InputItemName inputitemname)
{
	return 0;
}
