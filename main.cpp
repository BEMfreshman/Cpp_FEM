#include "core.h"
#include <iostream>


int main()
{
    std::string InputFilePath = "F:\\Cpp_FEM";
    std::string InputFileName = "BuildInput.txt";
    AbstractFileReader* FileReader = new BuildInFileReader(InputFilePath,
                                                           InputFileName);
    //Factory fac = new Factory();
    abstractFEMModel* FEMModel = new LinearStaticModel(FileReader);
    //线性静态模型



    delete FEMModel;
    delete FileReader;

    return 0;
}
