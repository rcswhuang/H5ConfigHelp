#include "hsysconfighandle.h"
#include "hsysconfig.h"
HSysConfigHandle* HSysConfigHandle::pInstance = NULL;

HSysConfigHandle* HSysConfigHandle::initInstance()
{
    if(!pInstance)
    {
        pInstance = new HSysConfigHandle;
    }
    return pInstance;
}

void HSysConfigHandle::exitInstance()
{
    if(pInstance)
    {
        delete pInstance;
        pInstance = NULL;
    }
}

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
    if(pInstance)
    {
        pSysconfig = new HSysconfig;
        pSysconfig->initSysSet();
    }
}


void HSysConfigHandle::getSettingValue(int nSettingID,int nSysSetID,QVariant* &value)
{
    if(pInstance)
    {
        pSysconfig->getSettingValue(nSettingID,nSysSetID,value);
    }
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

/////////////////////////////////////////////////////////////
void initSysConfig()
{
    HSysConfigHandle::initInstance()->initSysConfig();
}

void exitSysConfig()
{
    HSysConfigHandle::exitInstance();
}

void getSettingValue(int nSettingID,int nSysSetID,QVariant* &value)
{
    HSysConfigHandle::initInstance()->getSettingValue(nSettingID,nSysSetID,value);
}

void  getSysConfigByID(int nSettingID,HSysSetList* &sysSetList)
{
    HSysConfigHandle::initInstance()->getSysConfigByID(nSettingID,sysSetList);
}

bool  applySysConfig()
{
    return  HSysConfigHandle::initInstance()->applySysConfig();
}
