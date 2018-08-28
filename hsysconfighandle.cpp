#include "hsysconfighandle.h"
#include "hsysconfig.h"
HSysConfigHandle::HSysConfigHandle()
{

}

HSysConfigHandle::~HSysConfigHandle()
{
    if(pSysconfig)
    {
        delete pSysconfig;
        pSysconfig = NULL;
    }
}

void HSysConfigHandle::initSysConfig()
{
    pSysconfig = new HSysconfig;
    pSysconfig->initSysSet();
}


void HSysConfigHandle::getSettingValue(int nSettingID,int nSysSetID,QVariant* &value)
{
    pSysconfig->getSettingValue(nSettingID,nSysSetID,value);
}

void  HSysConfigHandle::getSysConfigByID(int nSettingID,HSysSetList* &sysSetList)
{
    if(pSysconfig)
        sysSetList = pSysconfig->getSysSetById(nSettingID);
    else
        sysSetList = NULL;
}

bool  HSysConfigHandle::applySysConfig()
{
    //保存
    return pSysconfig->apply();
}

////////////////////////////////////////////////////////////
HSysConfigHandle sysConfigHandle;
/////////////////////////////////////////////////////////////
void initSysConfig()
{
    sysConfigHandle.initSysConfig();
}

void getSettingValue(int nSettingID,int nSysSetID,QVariant* &value)
{
    sysConfigHandle.getSettingValue(nSettingID,nSysSetID,value);
}

void  getSysConfigByID(int nSettingID,HSysSetList* &sysSetList)
{
    sysConfigHandle.getSysConfigByID(nSettingID,sysSetList);
}

bool  applySysConfig()
{
    return  sysConfigHandle.applySysConfig();
}
