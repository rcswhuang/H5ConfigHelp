#ifndef HSYSCONFIGHANDLE_H
#define HSYSCONFIGHANDLE_H
#include <iostream>
#include <QVariant>
#include "hconfigapi.h"
class HSysconfig;
class HSysConfigHandle
{
public:
    HSysConfigHandle();
    ~HSysConfigHandle();
public:
    void initSysConfig();
    void getSettingValue(int nSettingID,int nSysSetID,QVariant* &value);
    //HSysconfig* getSysConfig(){return pSysconfig;}
    void   getSysConfigByID(int nSysSetID,HSysSetList* &sysSetList);
    bool   applySysConfig();
private:
    HSysconfig* pSysconfig;
};

#endif // HSYSCONFIGHANDLE_H
