#include "hsysconfighandle.h"
#include "hsysconfigapi.h"
HSysConfigHandle* HSysConfigHandle::pInstance = NULL;

HSysConfigHandle* HSysConfigHandle::instance()
{
    if(pInstance)
    {
        pInstance = new HSysConfigHandle;
    }
    return pInstance;
}


HSysConfigHandle::HSysConfigHandle()
{
}

void HSysConfigHandle::initSysConfig()
{
    if(pInstance)
    {
        pSysConfApi = new HSysconfigapi;
        pSysConfApi->initSysSet();
    }
}

/////////////////////////////////////////////////////////////
void SYSCONFIGAPISHARED_EXPORT getSettingValue(ushort uSettingID,ushort syssetid,QVariant* &value)
{
    HSysConfigHandle* pInstance = HSysConfigHandle::instance();
    if(pInstance)
    {
        ((HSysconfigapi*)pInstance->getSysConfApi())->getSettingValue(uSettingID,syssetid,value);
    }
}
