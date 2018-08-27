#include "hsysconfighandle.h"
#include "hsysconfig.h"

/*
 * 注意：系统配置文件必须存放在对应bin目录下面
*/
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

void HSysConfigHandle::initSysConfig(const char *file)
{
    if(pInstance)
    {
        pSysconfig = new HSysconfig;
        pSysconfig->initSysSet(file);
    }
}


void HSysConfigHandle::getSettingValue(int nSettingID,int nSysSetID,QVariant &value)
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
    return false;
}

/////////////////////////////////////////////////////////////
void initSysConfig(const char* file)
{
    HSysConfigHandle::initInstance()->initSysConfig(file);
}

void exitSysConfig()
{
    HSysConfigHandle::exitInstance();
}

void getSettingValue(int nSettingID,int nSysSetID,QVariant &value)
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
