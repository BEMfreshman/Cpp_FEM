#include "core.h"
#include <iostream>


int main()
{
    std::string InputFilePath = "F:\\FEMCode_CPP\\Cpp_FEM";
    std::string InputFileName = "1dbeam.txt";
    AbstractFileReader* FileReader = new BuildInFileReader(InputFilePath,
                                                           InputFileName);

	FEMinfo *FemInformation = new FEMinfo(1,FileReader);

	abstractFEMModel* FEMModel = new LinearStaticModel(FemInformation);
    //线性静态模型

	FEMModel->Solve();

	


    delete FEMModel;
	delete FemInformation;
    delete FileReader;

    return 0;
}
