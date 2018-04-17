TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    TopAbstractClass/abstractelement.cpp \
    TopAbstractClass/abstractfilereader.cpp \
    TopAbstractClass/abstractpostfilereader.cpp \
    TopAbstractClass/feminfo.cpp \
    File/buildinfilereader.cpp \
    File/inputitem.cpp \
    File/inputcard.cpp \
    Utils/factory.cpp \
    TopAbstractClass/abstractfemmodel.cpp \
    Geo/point.cpp \
    Geo/vertex.cpp \
    Geo/truss.cpp \
    Geo/quadelement.cpp \
    FEMModel/linearstaticmodel.cpp \
    TopAbstractClass/abstractmaterial.cpp \
    MaterialProp/structuremat.cpp \
    MaterialProp/linearstrumat.cpp \
    MaterialProp/isolinearstrumat.cpp \
    MaterialProp/orthlinearstrumat.cpp \
    TopAbstractClass/abastractelementprop.cpp \
    Utils/utilfunction.cpp


SUBDIRS += \
    FEM.pro

HEADERS += \
    TopAbstractClass/abstractelement.h \
    TopAbstractClass/abstractfilereader.h \
    TopAbstractClass/abstractpostfilereader.h \
    TopAbstractClass/feminfo.h \
    File/buildinfilereader.h \
    File/inputitem.h \
    File/inputcard.h \
    File/buildinkeyword.h \
    Utils/factory.h \
    TopAbstractClass/abstractfemmodel.h \
    Geo/point.h \
    Geo/vertex.h \
    Geo/truss.h \
    core.h \
    Geo/quadelement.h \
    FEMModel/linearstaticmodel.h \
    TopAbstractClass/abstractmaterial.h \
    TopAbstractClass/matpropvar.h \
    TopAbstractClass/sparsematrixtype.h \
    MaterialProp/structuremat.h \
    MaterialProp/linearstrumat.h \
    MaterialProp/isolinearstrumat.h \
    MaterialProp/orthlinearstrumat.h \
    TopAbstractClass/abastractelementprop.h \
    File/inputitemname.h \
    Utils/utilfunction.h


INCLUDEPATH+=F:\eigen\eigen

