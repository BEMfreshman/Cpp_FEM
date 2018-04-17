#include "abstractfemmodel.h"
#include "feminfo.h"
#include "../File/buildinfilereader.h"
abstractFEMModel::abstractFEMModel(AbstractFileReader* InputFileReader)
{
    FEMinfo *FemInformation = new FEMinfo(1,InputFileReader);
    FemInformationVec.push_back(FemInformation);
}

abstractFEMModel::~abstractFEMModel()
{
    std::vector<FEMinfo*>::iterator it;
    for(it = FemInformationVec.begin();
        it!=FemInformationVec.end();it++)
    {
        delete (*it);
    }
}
