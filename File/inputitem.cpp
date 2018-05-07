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
            seperateChar = ' ';
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

    /*NumofSplitStr = 0;
    for(int i = 0; i < splitstr.size();i++)
    {
        if(splitstr[i] != "")
        {
            NumofSplitStr++;
        }
    }*/

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
	//从0开始
	int ReturnValue;
	std::stringstream sstr;
	sstr << splitstr[pos];  
	sstr >> ReturnValue;
	return ReturnValue;
}

double InputItem::GetDataD(int pos)
{
	double ReturnValue;
	std::stringstream sstr;
	sstr << splitstr[pos];  //从0开始
	sstr >> ReturnValue;
	return ReturnValue;
}

std::string InputItem::GetDataStr(int pos)
{
	return splitstr[pos];   //从0开始
}

int InputItem::GetDataByItemName(std::map<std::string,double>& Data,InputItemName inputitemname)
{
    switch(inputitemname)
    {
        case Mat_PropNameAndPropValue:
        {
            //从第5个开始，字符串和数字交替
            std::string PropName;
            double PropValue;
            int Counter = 0;
			for (size_t i = 4; i < splitstr.size(); i++)
            {
                if(i % 2 == 0)
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
					//读两个数据
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
			for (size_t i = 3; i < splitstr.size(); i++)
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
		default:
		{
			return 0;
		}
    }
}



int InputItem::GetDataByItemName(std::string& Data,InputItemName inputitemname)
{
    switch(inputitemname)
    {
        case Analysis_SolType:
        {
            Data = GetDataStr(2);
            return 1;
        }
        case Element_Type:
        {
            Data = GetDataStr(2);
            return 1;
        }
        case Mat_LinearOrNot:
        {
            Data = GetDataStr(2);
            return 1;
        }
        case Mat_IsoOrNot:
        {
			Data = GetDataStr(3);
			return 1;
        }
        case EProp_ElementName:
        {
            Data = GetDataStr(2);
            return 1;
        }
		case Load_Name:
		{
			Data = GetDataStr(2);
			return 1;
		}
		case Constraint_Name:
		{
			Data = GetDataStr(2);
			return 1;
		}
		default:
		{
			return 0;
		}
    }
}

int InputItem::GetDataByItemName(int* Data,InputItemName inputitemname)
{
    switch (inputitemname)
    {
        case Analysis_SolNum:
        {
            (*Data) = GetDataI(1);
            return 1;
        }
        case Vertex_Id:
        {
            (*Data) = GetDataI(1);
            return 1;
        }
		case SPC:
		{
			int Pos = GetValidPostion("SPC");
			if (Pos == -1)
			{
				//无此关键字
				(*Data) = 0;
			}
			else
			{
				(*Data) = GetDataI(Pos + 1);
			}
			return 1;
		}
        case Element_Id:
        {
            (*Data) = GetDataI(1);
            return 1;
        }
        case Element_MatId:
        {
            std::string EleType;
            GetDataByItemName(EleType,Element_Type);
            if(EleType == "LINE2" ||
                    EleType == "TRUSS" ||
                    EleType == "BEAMEB2" || EleType == "BEAMEB3" ||
					EleType == "BEAMT2" || EleType == "BEAMT3")
            {
                (*Data) = GetDataI(5);
                return 1;
            }
            else if(EleType == "LINE3" ||
                    EleType == "TRIANGLE3")
            {
                (*Data) = GetDataI(6);
                return 1;
            }
            else if(EleType == "TRIANGLE4" ||
                    EleType == "QUAD4" ||
                    EleType == "TET4" ||
                    EleType == "SHELL")
            {
                (*Data) = GetDataI(7);
                return 1;
            }
            else if(EleType == "TRIANGLE6")
            {
                (*Data) = GetDataI(9);
                return 1;
            }
            else if(EleType == "QUAD8" ||
                    EleType == "HEX8")
            {
                (*Data) = GetDataI(11);
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
			if (EleType == "TRUSS" || EleType == "BEAMEB2" || EleType == "BEAMEB3" ||
				EleType == "BEAMT2" || EleType == "BEAMT3")
            {
                (*Data) = GetDataI(6);
                return 1;
            }
            else if(EleType == "SHELL")
            {
                (*Data) = GetDataI(8);
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
            (*Data) = GetDataI(1);
            return 1;
        }
        case EProp_Id:
        {
            (*Data) = GetDataI(1);
            return 1;
        }
		case Load_Id:
		{
			(*Data) = GetDataI(1);
			return 1;
		}
		case Constraint_Id:
		{
			(*Data) = GetDataI(1);
			return 1;
		}
		case Constraint_DOFVarI:
		{
			(*Data) = GetDataI(4);
			return 1;
		}
		case Constraint_NodeId:
		{
			(*Data) = GetDataI(3);
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
			if (GetDataStr(2) == "")
			{
				(*Data) = 0.0;
				return 1;
			}
			else
			{
				(*Data) = GetDataD(2);
				return 1;
			}
            
        }
        case Vertex_CoordY:
        {
			if (GetDataStr(3) == "")
			{
				(*Data) = 0.0;
				return 1;
			}
			else
			{
				(*Data) = GetDataD(3);
				return 1;
			}
        }
        case Vertex_CoordZ:
        {
			if (splitstr.size() > 4)
			{
				if (GetDataStr(4) == "")
				{
					(*Data) = 0.0;
					return 0;
				}
				else
				{
					(*Data) = GetDataD(4);
					return 1;
				}
			}
			else
			{
				(*Data) = 0.0;
				return 0;
			}
			
        }
		case Constraint_Value:
		{
			(*Data) = GetDataD(5);
			return 1;
		}
		default:
		{
				(*Data) = 0.0;
				return 0;
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

            if(EleType == "LINE2" || EleType == "BEAMEB2" || EleType == "BEAMT2")
            {

                Data.resize(1,2);

                for(int i = 3,tmp = 0; i < 5;i++,tmp++)
                {
                    //取第3个和第4个数据
                    VertexId = GetDataI(i);
                    Data(0,tmp) =  VertexId;
                }
                return 1;
            }
            else if(EleType == "LINE3" || EleType == "TRIANGLE3" || EleType == "BEAMEB3" ||
				EleType == "BEAMT3")
            {
                Data.resize(1,3);

                for(int i = 3,tmp = 0; i < 6;i++,tmp++)
                {
                    //取第4,5,6个数据
                    VertexId = GetDataI(i);
                    Data(0,tmp) = VertexId;
                }
                return 1;
            }
            else if(EleType == "TRIANGLE4" || EleType == "QUQD4" ||
				EleType == "TET4")
            {
                Data.resize(1,4);

                for(int i = 3,tmp = 0; i < 7;i++,tmp++)
                {
                    //取第3,4,5,6个数据
                    VertexId = GetDataI(i);
                    Data(0,tmp) =  VertexId;
                }
                return 1;
            }
            else if(EleType == "TRIANGLE6")
            {
                Data.resize(1,6);

                for(int i = 3,tmp = 0; i < 9;i++,tmp++)
                {
                    //取第3,4,5,6,7,8个数据
                    VertexId = GetDataI(i);
                    Data(0,tmp) = VertexId;
                }
                return 1;
            }
            else if(EleType == "QUAD8" || EleType == "HEX8")
            {
                Data.resize(1,8);
                for(int i = 3,tmp = 0; i < 11;i++,tmp++)
                {
                    //取第3,4,5,6,7,8,9,10个数据
                    VertexId = GetDataI(i);
                    Data(0,tmp) = VertexId;
                }
                return 1;
            }
            else
            {
                Data.resize(1,1);
				Data(0, 0) = 0;
                return 0;
            }

        }
		case Load_NodeId:
		{
			std::string LoadName;
			GetDataByItemName(LoadName, Load_Name);
			if (LoadName == "NodeLoad")
			{
				//集中载荷
				Data.resize(1, 1);
				Data(0, 0) = GetDataI(3);
				return 1;

			}
			else if (LoadName == "Pressure")
			{
				//分布载荷
				return 0;
			}
		}
		default:
		{
			Data.resize(1, 1);
			Data(0, 0) = 0;
			return 0;
		}
    }
}

int InputItem::GetDataByItemName(Eigen::MatrixXd &Data,InputItemName inputitemname)
{
	switch (inputitemname)
	{
		case Load_Value:
		{
			std::string LoadName;
			GetDataByItemName(LoadName, Load_Name);
			if (LoadName == "NodeLoad")
			{
				//集中载荷
				std::vector<double> tmp;
				for (int i = 4; i < splitstr.size(); i++)
				{
					tmp.push_back(GetDataD(i));
				}

				Data.resize(1, tmp.size());
				for (int i = 0; i < tmp.size(); i++)
				{
					Data(0, i) = tmp[i];
				}

			}
			else if (LoadName == "Pressure")
			{
				//分布载荷
			}
		}
	}

	return 0;
}

int InputItem::GetValidPostion(const std::string& KeyWordInItem)
{
	for (size_t i = 0; i < splitstr.size(); i++)
	{
		if (splitstr[i] == KeyWordInItem)
		{
			return i;   //Pos从0开始
		}
	}
	return -1;
}
