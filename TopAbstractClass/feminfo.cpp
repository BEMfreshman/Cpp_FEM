#include "feminfo.h"
#include "../Utils/factory.h"

#include "abstractfilereader.h"
#include "../Geo/vertex.h"
#include "abstractelement.h"
#include "abstractmaterial.h"
#include "abastractelementprop.h"
#include "abstractload.h"
#include "abstractconstraint.h"

#include "elementtype.h"
/*
 * include "abstractMat.h"
 * include "abstractEProp.h"
 * include "abstractLoad.h"
 * include "abstractConstraint.h"
 */


FEMinfo::FEMinfo(int FEMinfoId,AbstractFileReader *FileReader)
{
    this->FEMinfoId = FEMinfoId;

    Factory* fac = new Factory();

    //实例化数据类
    //根据不同的类型Get到不同的InputCard
    //所有的InputCard都由InputItem构成
    //读取InputItem（分为关键字和数据体两种）实例化类
    //首先获得AnalysisType
    InputCard *analysistypeinputcard =
            FileReader->GetInputCard(AbstractFileReader::AnalysisType);

    InputItem* EachInputItem =
            analysistypeinputcard->GetInputItemAccordtoID(0);

    EachInputItem->GetDataByItemName(&AnalysisTypeData,Analysis_SolNum);

	std::string DimAndMatStatus;
	EachInputItem->GetDataByItemName(DimAndMatStatus, Analysis_SolType);

	if (DimAndMatStatus.find("1d") != string::npos)
	{
		dim = 1;
	}
	else if (DimAndMatStatus.find("2d") != string::npos)
	{
		dim = 2;
	}
	else if (DimAndMatStatus.find("3d") != string::npos)
	{
		dim = 3;
	}



    //实例化Vertex
    InputCard *VertexInputCard =
            FileReader->GetInputCard(AbstractFileReader::Vertex);

    for(size_t i = 0; i < VertexInputCard->sizeofInputCard();i++)
    {
        InputItem* EachInputItem =
                VertexInputCard->GetInputItemAccordtoID(i);
        int id;
		int SPCsNum;                         //单点约束
        double CoordX = 0.0,CoordY = 0.0,CoordZ = 0.0;

        EachInputItem->GetDataByItemName(&id,Vertex_Id);
        EachInputItem->GetDataByItemName(&CoordX,Vertex_CoordX);
        EachInputItem->GetDataByItemName(&CoordY,Vertex_CoordY);
        EachInputItem->GetDataByItemName(&CoordZ,Vertex_CoordZ);
		EachInputItem->GetDataByItemName(&SPCsNum, SPC);

		Vertex* vertex = fac->CreateVertex(id, CoordX, CoordY, CoordZ,SPCsNum);
		VertexMap[id] = vertex;

    }
    //实例化Element

    InputCard* EleInputCard =
            FileReader->GetInputCard(AbstractFileReader::Element);

    for(size_t i = 0;i < EleInputCard->sizeofInputCard();i++)
    {
        InputItem* EachInputItem =
                EleInputCard->GetInputItemAccordtoID(i);

        int id;
        int MaterialId;
        int EPropId;
        std::string EleTypeStr;
        ElementType EleType;
        Eigen::MatrixXi VertexIdArray;

        EachInputItem->GetDataByItemName(&id,Element_Id);
        EachInputItem->GetDataByItemName(EleTypeStr,Element_Type);
        EachInputItem->GetDataByItemName(VertexIdArray,Element_VertexIdArray);
        EachInputItem->GetDataByItemName(&MaterialId,Element_MatId);


        if(EleTypeStr == "LINE2")
        {
            EleType = LINE2;
        }
        else if(EleTypeStr == "LINE3")
        {
            EleType = LINE3;
        }
        else if(EleTypeStr == "TRIANGLE3")
        {
            EleType = TRIANGLE3;
        }
        else if(EleTypeStr == "TRIANGLE4")
        {
			EleType = TRIANGLE4;
        }
        else if(EleTypeStr == "QUAD4")
        {
            EleType = QUADRILATERAL4;
        }
        else if(EleTypeStr == "QUAD8")
        {
			EleType = QUADRILATERAL8;
        }
        else if(EleTypeStr == "QUAD9")
        {
			EleType = QUADRILATERAL9;
        }
        else if(EleTypeStr == "TET4")
        {
            EleType = TETRAHEDRON4;
        }
        else if(EleTypeStr == "HEX8")
        {
            EleType = HEXAHEDRON8;
        }
        else if(EleTypeStr == "TRUSS")
        {
            EleType = TRUSS;
        }
        else if(EleTypeStr == "BEAMEB2")
        {
            EleType = BEAMEB2;
        }
		else if (EleTypeStr == "BEAMEB3")
		{
			EleType = BEAMEB3;
		}
		else if (EleTypeStr == "BEAMT2")
		{
			EleType = BEAMT2;
		}
		else if (EleTypeStr == "BEAMT3")
		{
			EleType = BEAMT3;
		}
        else if(EleTypeStr == "SHELL")
        {
            EleType = SHELL;
        }


        int SuccessFlag =
                EachInputItem->GetDataByItemName(&EPropId,Element_EPropId);

        if(SuccessFlag == 0)
        {
            //不存在单元属性
            Element* Ele = fac->CreateElement(id,MaterialId,
                                              EleType,VertexIdArray);

			EleMap[id] = Ele;
        }
        else
        {
            Element* Ele = fac->CreateElement(id,MaterialId,EPropId,
                                              EleType,VertexIdArray);
			EleMap[id] = Ele;
        }
    }

    // 实例化材料类
    // 目前只针对固体材料而言，
    // 固体材料一般具有 密度，杨氏弹性模量，泊松比，剪切刚度（可通过E和Nu得出结果）
    
	InputCard* MatInputCard =
		FileReader->GetInputCard(AbstractFileReader::Material);

	InputItem* AnalysisInputItem =
		analysistypeinputcard->GetInputItemAccordtoID(0);

	AnalysisInputItem->GetDataByItemName(DimAndMatStatus, Analysis_SolType);


	for (size_t i = 0; i < MatInputCard->sizeofInputCard(); i++)
	{
		InputItem* MatInputItem = MatInputCard->GetInputItemAccordtoID(i);

		int id;
		std::string LinearOrNot;
		std::string IsoOrNot;
		std::map<std::string, double> PropNameAndPropValue;

		MatInputItem->GetDataByItemName(&id, Mat_Id);
		MatInputItem->GetDataByItemName(LinearOrNot, Mat_LinearOrNot);
		MatInputItem->GetDataByItemName(IsoOrNot, Mat_IsoOrNot);
		MatInputItem->GetDataByItemName(PropNameAndPropValue, Mat_PropNameAndPropValue);

		Mat* mat = fac->CreateMat(id,LinearOrNot,IsoOrNot,PropNameAndPropValue,DimAndMatStatus);

		MatMap[id] = mat;

	}

	//实例化单元属性
	//注意，可能完全没有单元属性（例如实体单元）

	InputCard* ElePropInputCard =
		FileReader->GetInputCard(AbstractFileReader::ElementProp);
	
	for (size_t i = 0; i < ElePropInputCard->sizeofInputCard(); i++)
	{
		InputItem* EPropInputItem = ElePropInputCard->GetInputItemAccordtoID(i);
		
		int id;
		std::string ElementPropName;   //Beam,Truss等
		std::map<std::string, double> PropNameAndPropValue;

		EPropInputItem->GetDataByItemName(&id, EProp_Id);
		EPropInputItem->GetDataByItemName(ElementPropName, EProp_ElementName);
		EPropInputItem->GetDataByItemName(PropNameAndPropValue, EProp_PropNameAndPropValue);

		EProp* EP = fac->CreateEProp(id, ElementPropName, PropNameAndPropValue);

		EPropMap[id] = EP;
	}



    delete fac;
}

FEMinfo::FEMinfo()
{
    FEMinfoId = 0;
}

FEMinfo::FEMinfo(int FEMinfoId)
{
    this->FEMinfoId = FEMinfoId;
}

FEMinfo::~FEMinfo()
{
	for (map<int, Vertex*>::iterator it = VertexMap.begin(); it != VertexMap.end(); it++)
	{
		delete it->second;
	}

	for (map<int, Element*>::iterator it = EleMap.begin(); it != EleMap.end(); it++)
	{
		delete it->second;
	}

	for (map<int, Mat*>::iterator it = MatMap.begin(); it != MatMap.end(); it++)
	{
		delete it->second;
	}

	for (map<int, EProp*>::iterator it = EPropMap.begin(); it != EPropMap.end(); it++)
	{
		delete it->second;
	}

	for (map<int, Load*>::iterator it = LoadMap.begin(); it != LoadMap.end(); it++)
	{
		delete it->second;
	}

	for (map<int, Constraint*>::iterator it = ConstraintMap.begin(); it != ConstraintMap.end(); it++)
	{
		delete it->second;
	}
}

FEMinfo* FEMinfo::CreateCopy(int NewId)
{
    FEMinfo* feminfo = new FEMinfo(NewId);
    //在堆上分配产生一个新的feminfo
    feminfo->AnalysisTypeData = this->AnalysisTypeData;
    //feminfo->fem2dtype = this->fem2dtype;

	for (size_t id = 1; id <= VertexMap.size(); id++)
    {
        Vertex* NewVertex = new Vertex(*(VertexMap.find(id)->second));
        feminfo->VertexMap[NewVertex->getid()] = NewVertex;
    }

	for (size_t id = 1; id <= EleMap.size(); id++)
    {
        Element* NewEle = (EleMap.find(id)->second)->Clone();
        feminfo->EleMap[NewEle->GetElementId()] = NewEle;
    }

	//feminfo->SetMatAndEPropAndVertexInElement();
    return feminfo;
}

int FEMinfo::FinallyCompulsorySet()
{
	if (VertexMap.size() == 0)
	{
		return 0;
	}
    else if(EleMap.size() == 0)
    {
        return 0;
    }
	else if (MatMap.size() == 0)
    {
        return 0;
    }
	

    for(size_t i = 1 ; i <= EleMap.size();i++)
    {
        Element* Ele = EleMap.find(i)->second;

		const Eigen::MatrixXi VertexIdArray = Ele->GetVertexIdArray();
		int row = VertexIdArray.rows();
		int col = VertexIdArray.cols();
		if (row == 1 && col >= 1)
		{
			for (int i = 0; i < col; i++)
			{
				int VertexId = VertexIdArray(0, i);
				Vertex* Vert = VertexMap.find(VertexId)->second;
				Vert->SetDOF(dim, Ele->GetElementType());
				Ele->SetVertex(Vert);
			}
		}
		else
		{
			for (int i = 0; i < row; i++)
			{
				int VertexId = VertexIdArray(i, 0);
				Vertex* Vert = VertexMap.find(VertexId)->second;
				Vert->SetDOF(dim, Ele->GetElementType());
				Ele->SetVertex(Vert);
			}
		}

        int MaterialId = Ele->GetMaterialId();
        Mat* mat = MatMap.find(MaterialId)->second;
        Ele->SetMat(mat);

        int EPropId = Ele->GetEPropId();
        if(EPropId != 0)
        {
            EProp* eprop = EPropMap.find(EPropId)->second;
            Ele->SetEProp(eprop);
        }

    }

	return 1;
}

int FEMinfo::getVertexNum() const
{
	return VertexMap.size();
}

Vertex* FEMinfo::getVertexById(int id) const
{
	map<int, Vertex*>::const_iterator it;
	it = VertexMap.find(id);

	return (it == VertexMap.end()? NULL:it->second);
}

int FEMinfo::getElementNum() const
{
	return EleMap.size();
}

Element* FEMinfo::getElementById(int id)const
{
	map<int, Element*>::const_iterator it;
	it = EleMap.find(id);

	return(it == EleMap.end() ? NULL : it->second);
}

int FEMinfo::getLoadNum() const
{
	return LoadMap.size();
}

Load* FEMinfo::getLoadById(int id) const
{
	map<int, Load*>::const_iterator it;
	it = LoadMap.find(id);

	return (it == LoadMap.end() ? NULL : it->second);
}

int FEMinfo::getConstraintNum() const
{
	return ConstraintMap.size();
}

Constraint* FEMinfo::getConstraintById(int id)const
{
	map<int, Constraint*>::const_iterator it;
	it = ConstraintMap.find(id);

	return (it == ConstraintMap.end() ? NULL : it->second);
}

int FEMinfo::getdim() const
{
	return dim;
}


















