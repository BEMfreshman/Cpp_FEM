#include "feminfo.h"
#include "../Utils/factory.h"

#include "abstractfilereader.h"
#include "../Geo/vertex.h"
#include "abstractelement.h"
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

    //实例化Vertex
    InputCard *VertexInputCard =
            FileReader->GetInputCard(AbstractFileReader::Vertex);

    for(size_t i = 0; i < VertexInputCard->sizeofInputCard();i++)
    {
        InputItem* EachInputItem =
                VertexInputCard->GetInputItemAccordtoID(i);
        int id;
        double CoordX,CoordY,CoordZ;

        EachInputItem->GetDataByItemName(&id,Vertex_Id);
        EachInputItem->GetDataByItemName(&CoordX,Vertex_CoordX);
        EachInputItem->GetDataByItemName(&CoordY,Vertex_CoordY);
        int SuccessFlag =
                EachInputItem->GetDataByItemName(&CoordZ,Vertex_CoordZ);
        if(SuccessFlag == 0)
        {
            //不存在Z坐标
            Vertex* vertex = fac->CreateVertex(id,CoordX,CoordY);
            VertexVec.push_back(vertex);
        }
        else
        {
            //存在Z坐标
            Vertex* vertex = fac->CreateVertex(id,CoordX,CoordY,CoordZ);
            VertexVec.push_back(vertex);
        }
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
        Element::ElementType EleType;
        Eigen::MatrixXi VertexIdArray;

        EachInputItem->GetDataByItemName(&id,Element_Id);
        EachInputItem->GetDataByItemName(EleTypeStr,Element_Type);
        EachInputItem->GetDataByItemName(VertexIdArray,Element_VertexIdArray);
        EachInputItem->GetDataByItemName(&MaterialId,Element_MatId);


        if(EleTypeStr == "LINE2")
        {
            EleType = Element::Line2;
        }
        else if(EleTypeStr == "LINE3")
        {
            EleType = Element::Line3;
        }
        else if(EleTypeStr == "TRIANGLE3")
        {
            EleType = Element::Triangle3;
        }
        else if(EleTypeStr == "TRIANGLE4")
        {
            EleType = Element::Triangle4;
        }
        else if(EleTypeStr == "QUAD4")
        {
            EleType = Element::Quadrilateral4;
        }
        else if(EleTypeStr == "QUAD8")
        {
            EleType = Element::Quadrilateral8;
        }
        else if(EleTypeStr == "QUAD9")
        {
            EleType = Element::Quadrilateral9;
        }
        else if(EleTypeStr == "TET4")
        {
            EleType = Element::Tetrahedron4;
        }
        else if(EleTypeStr == "HEX8")
        {
            EleType = Element::Hexahedron8;
        }
        else if(EleTypeStr == "TRUSS")
        {
            EleType = Element::Truss;
        }
        else if(EleTypeStr == "BEAM")
        {
            EleType = Element::Beam;
        }
        else if(EleTypeStr == "SHELL")
        {
            EleType = Element::Shell;
        }


        int SuccessFlag =
                EachInputItem->GetDataByItemName(&EPropId,Element_EPropId);

        if(SuccessFlag == 0)
        {
            //不存在单元属性
            Element* Ele = fac->CreateElement(id,MaterialId,
                                              EleType,VertexIdArray);
            EleVec.push_back(Ele);
        }
        else
        {
            Element* Ele = fac->CreateElement(id,MaterialId,EPropId,
                                              EleType,VertexIdArray);
            EleVec.push_back(Ele);
        }
    }

    // 实例化材料类
    // 目前只针对固体材料而言，
    // 固体材料一般具有 密度，杨氏弹性模量，泊松比，剪切刚度（可通过E和Nu得出结果）
    
	InputCard* MatInputCard =
		FileReader->GetInputCard(AbstractFileReader::Material);

	InputItem* AnalysisInputItem =
		analysistypeinputcard->GetInputItemAccordtoID(0);

	std::string DimAndMatStatus;
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

		MatVec.push_back(mat);

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

		EPropVec.push_back(EP);
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

}

FEMinfo* FEMinfo::CreateCopy(int NewId)
{
    FEMinfo* feminfo = new FEMinfo(NewId);
    //在堆上分配产生一个新的feminfo
    feminfo->AnalysisTypeData = this->AnalysisTypeData;
    //feminfo->fem2dtype = this->fem2dtype;

    for(int i = 0 ; i < VertexVec.size();i++)
    {
        Vertex* NewVertex = new Vertex(*(VertexVec[i]));
        feminfo->VertexVec.push_back(NewVertex);
    }

    for(int i = 0;i < EleVec.size();i++)
    {
        Element* NewEle = (EleVec[i])->Clone();
        feminfo->EleVec.push_back(NewEle);
    }

    feminfo->SetMatAndEProp();
    return feminfo;
}

void FEMinfo::SetMatAndEProp()
{
    if(EleVec.size() == 0)
    {
        return;
    }
    else if(MatVec.size() == 0)
    {
        return;
    }

    for(size_t i = 0 ; i < EleVec.size();i++)
    {
        Element* Ele = EleVec[i];
        int MaterialId = Ele->GetMaterialId();
        Mat* mat = MatVec[MaterialId];
        Ele->SetMat(mat);

        int EPropId = Ele->GetEPropId();
        if(EPropId != 0)
        {
            EProp* eprop = EPropVec[EPropId];
            Ele->SetEProp(eprop);
        }
    }
}


















