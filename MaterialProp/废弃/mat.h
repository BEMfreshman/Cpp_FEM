#ifndef MAT_H
#define MAT_H

/*
 *Mat为抽象类
 */
class Mat
{
public:

    enum MatType
    {
        Iso,   //各向同性
        Orth   //正交各向异性
    };

    enum Dim
    {
        Two,   //二维
        Three  //三维
    };

    enum LinearOrNon
    {
        Linear,
        NonLinear
    };

    virtual ~Mat() = 0;


    void SetDensity(double Rho);
    void SetId(int id);


    virtual void InitialEandNu(double* E,double* Nu) = 0;  //初始化E和Nu
    virtual void InitialEandG(double* E,double* G) = 0;    //初始化E和G
    virtual void InitialNuandG(double* Nu,double* G) = 0;  //初始化Nu和G

    int GetENum();
    int GetNuNum();
    int GetGNum();

    double* GetE();
    double* GetNu();
    double* GetG();

    int GetId();

    MatType GetMatType();



protected:
    Mat();

protected:
    int id;
    double* E;
    double* Nu;
    double* G;
    double* Rho;

    int ENum;
    int NuNum;
    int GNum;

    MatType mattype;
    Dim dim;
    LinearOrNon linearornon;

private:

};

#endif // MAT_H
