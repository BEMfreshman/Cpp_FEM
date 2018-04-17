说明：
该文件夹下面放置抽象类，用于总体控制FEM的求解过程。
1.AbstractModel。抽象类，是所有具体问题类（例如：LinearModel类或者Dynamic类）的父类。
2.AbstractElement。抽象类，是所有的具体单元类的父类。提供单元类的通用接口和功能。
3.AbstractMaterial。抽象类，是所有的具体材料类的父类。提供材料类的通用接口和功能。
4.AbstractFileReader。抽象类，是所有的具体文件读取类的父类。提供文件读取功能，并统一打包成一种数据结构输出。
5.AbstractPostFileReader。抽象类，将计算结果输出为后处理器可以读的格式。
6.FEMInfo。数据读入后，按照不同的数据体实例化类，并将类指针存储起来。
7.AbstractNumericalMethod。抽象类，数值算法的总结集合。会根据不同的要求采用不同的实例算法。


8.InputCard。输入卡片类。

