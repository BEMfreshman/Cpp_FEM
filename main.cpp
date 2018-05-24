#include "core.h"
#include <iostream>
#include <math.h>


int main()
{


    std::string InputFilePath = "F:\\Cpp_FEM";
    std::string InputFileName = "1dbeam_q.txt";
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
