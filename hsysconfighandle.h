#ifndef HSYSCONFIGHANDLE_H
#define HSYSCONFIGHANDLE_H
#include <iostream>
#include <QVariant>
#include "hconfigapi.h"
class HSysconfig;
class HSysConfigHandle
{
public:
    static HSysConfigHandle* initInstance();
    static HSysConfigHandle* pInstance;
    static void exitInstance();
    HSysConfigHandle();
    ~HSysConfigHandle();
public:
    void initSysConfig(const char* file);
    void getSettingValue(int nSettingID,int nSysSetID,QVariant* &value);
    //HSysconfig* getSysConfig(){return pSysconfig;}
    void   getSysConfigByID(int nSysSetID,HSysSetList* &sysSetList);
    bool   applySysConfig();
private:
    HSysconfig* pSysconfig;
};

#endif // HSYSCONFIGHANDLE_H
