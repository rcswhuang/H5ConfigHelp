#include "hsysconfighandle.h"
#include "hconfigapi.h"
#include "hsysconfig.h"
HSysConfigHandle* HSysConfigHandle::pInstance = NULL;

HSysConfigHandle* HSysConfigHandle::instance()
{
    if(!pInstance)
    {
        pInstance = new HSysConfigHandle;
    }
    return pInstance;
}


HSysConfigHandle::HSysConfigHandle()
{
}

void HSysConfigHandle::initSysConfig(const char *file)
{
    if(pInstance)
    {
        pSysConfApi = new HSysconfig;
        pSysConfApi->initSysSet(file);
    }
}

/////////////////////////////////////////////////////////////
void SYSCONFIG_EXPORT initSysConfig(const char* file)
{
    HSysConfigHandle::instance()->initSysConfig(file);
}
void SYSCONFIG_EXPORT exitSysConfig()
{

}

void SYSCONFIG_EXPORT getSettingValue(int nSettingID,int nSysSetID,QVariant* &value)
{

}
