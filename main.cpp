﻿#include "core.h"
#include <math.h>
#include <iostream>

int main()
{


    std::string InputFilePath = "F:\\FEMCode_CPP\\Cpp_FEM";
    std::string InputFileName = "2dquad_136.txt";
    AbstractFileReader* FileReader = new BuildInFileReader(InputFilePath,
                                                           InputFileName);

	FEMinfo *FemInformation = new FEMinfo(1,FileReader);

	abstractFEMModel* FEMModel = new LinearStaticModel(FemInformation);
    //线性静态模型

	FEMModel->Solve();

	FEMModel->ShowAns();

	


    delete FEMModel;
	delete FemInformation;
    delete FileReader;

    return 0;
}
