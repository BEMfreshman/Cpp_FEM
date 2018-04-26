#include "abstractfemmodel.h"
abstractFEMModel::abstractFEMModel(FEMinfo* FEMInformation)
{
    
	FemInformation = FEMInformation;
}

abstractFEMModel::~abstractFEMModel()
{
    
}

int abstractFEMModel::PreProcess()
{
	//前操作
	//为每个单元赋予材料属性、单元属性和点的指针
	//确定总的自由度个数，SPC的自由度直接删除，不计入总数

	if (FemInformation->SetMatAndEPropAndVertexInElement() == 0)
	{
		printf("单元Mat、EProp和Vertex指针设置失败\n");
		return 0;
	}

}
