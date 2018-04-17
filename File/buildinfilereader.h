#ifndef BUILDINFILEREADER_H
#define BUILDINFILEREADER_H
#include "../TopAbstractClass/abstractfilereader.h"
#include "buildinkeyword.h"

/*BuildIn 文件输入示例
*Analysis 103
*Vertex
1 0.5 0.5
2 0.4 0.7
.
.
.
*Element
//Element文件写入有两种
第一种，当输入的单元为等参单元时
格式：
单元Id 单元类型（查看枚举表） 点编号 点编号 ... 材料编号
1 1 1 2 1   //第1个单元,单元类型为Line2,由1和2两个点构成,材料ID为1
第二种，当输入的单元为梁单元，杆单元，壳单元
格式
单元Id 单元类型（查看枚举表） 点编号 点编号 ... 材料编号 单元属性编号
*/

class BuildInFileReader:public AbstractFileReader
{
public:
    BuildInFileReader(const std::string& InputPath,const std::string& InputFile);
    ~BuildInFileReader() {}
private:
    BuildinKeyWord SwitchFromKeyWordToEnum(const std::string& keyword);
};

#endif // BUILDINFILEREADER_H
