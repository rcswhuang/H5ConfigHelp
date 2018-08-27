#include "hsysconfig.h"
#include "hqtxml.h"
#include <QProcessEnvironment>
#include <QCoreApplication>
HSysconfig::HSysconfig()
{
}

HSysconfig::~HSysconfig()
{
    while(!pSettingList->isEmpty())
    {
        SETTING* setting = pSettingList->takeFirst();
        if(setting)
        {
            while(!setting->pSysSetList->isEmpty())
            {
                SYSSET *sysset = setting->pSysSetList->takeFirst();
                if(sysset)
                {
                    delete sysset;
                    sysset = NULL;
                }
            }
            setting->pSysSetList->clear();
        }
        delete setting;
    }
    pSettingList->clear();
}

QString HSysconfig::getConfigXmlFile()
{
    QString strConfigFilePath = QProcessEnvironment::systemEnvironment().value("wfsystem_dir");
    if(strConfigFilePath.isEmpty())
    {
        strConfigFilePath = QCoreApplication::applicationDirPath();
        strConfigFilePath = strConfigFilePath.left(strConfigFilePath.lastIndexOf("/"));
    }
    QString strConfigFile = strConfigFilePath + "/wfconfig.xml";
    return strConfigFile;
}

void HSysconfig::initSysSet()
{
    pSettingList = new HSettingList;

    pNormalSysSetList = new HSysSetList;//一般设置
    SETTING* normalSetting = new SETTING;
    normalSetting->wSettingId = SYS_SET_NORMAL;
    normalSetting->pSysSetList = pNormalSysSetList;
    pSettingList->append(normalSetting);

    pNetSysSetList = new HSysSetList;//网络设置
    SETTING* netSetting = new SETTING;
    netSetting->wSettingId = SYS_SET_NET;
    netSetting->pSysSetList = pNetSysSetList;
    pSettingList->append(netSetting);

    pPathSysSetList = new HSysSetList;//路径设置
    SETTING* pathSetting = new SETTING;
    pathSetting->wSettingId = SYS_SET_PATH;
    pathSetting->pSysSetList = pPathSysSetList;
    pSettingList->append(pathSetting);

    pFunSysSetList = new HSysSetList;//功能设置
    SETTING* funSetting = new SETTING;
    funSetting->wSettingId = SYS_SET_PATH;
    funSetting->pSysSetList = pFunSysSetList;
    pSettingList->append(funSetting);

    pFormatSysSetList = new HSysSetList;//票号格式设置
    SETTING* formatSetting = new SETTING;
    formatSetting->wSettingId = SYS_SET_FORMAT;
    formatSetting->pSysSetList = pFormatSysSetList;
    pSettingList->append(formatSetting);

    pTicketSysSetList = new HSysSetList;//操作票设置
    SETTING* ticketSetting = new SETTING;
    ticketSetting->wSettingId = SYS_SET_TICKET;
    ticketSetting->pSysSetList = pTicketSysSetList;
    pSettingList->append(ticketSetting);

    pOtherSysSetList = new HSysSetList;//其他设置
    SETTING* otherSetting = new SETTING;
    otherSetting->wSettingId = SYS_SET_OTHER;
    otherSetting->pSysSetList = pOtherSysSetList;
    pSettingList->append(otherSetting);

    pQtXml = new HQtXml(this,getConfigXmlFile());
    pQtXml->parseXML();
}

HSysSetList* HSysconfig::getSysSetById(int nSettingID)
{
    if(pSettingList == NULL)
        return NULL;
    if(nSettingID == SYS_SET_NET)
    {
       if(pNetSysSetList)
           return pNetSysSetList;
    }
    else if(nSettingID == SYS_SET_NORMAL)
    {
        if(pNormalSysSetList)
            return pNormalSysSetList;
    }
    else if(nSettingID ==SYS_SET_FUN )
    {
        if(pFunSysSetList)
            return pFunSysSetList;
    }
    else if(nSettingID ==SYS_SET_PATH )
    {
        if(pPathSysSetList)
            return pPathSysSetList;
    }
    else if(nSettingID ==SYS_SET_TICKET)
    {
        if(pTicketSysSetList)
            return pTicketSysSetList;
    }
    else if(nSettingID ==SYS_SET_FORMAT )
    {
        if(pFormatSysSetList)
            return pFormatSysSetList;
    }
    else if(nSettingID ==SYS_SET_OTHER )
    {
        if(pOtherSysSetList)
            return pOtherSysSetList;
    }
    return NULL;
}

void HSysconfig::getSettingValue(int nSettingID, int nSysSetID, QVariant *&value)
{
    HSysSetList* pSysSetList = (HSysSetList*)getSysSetById(nSettingID);
    if(pSysSetList)
    {
        QList<SYSSET*>::iterator it;
        for(it = pSysSetList->begin();it != pSysSetList->end();++it)
        {
            SYSSET* sysSet = *it;
            if(sysSet && sysSet->id == nSysSetID)
            {
                value = &(sysSet->var);
            }
        }
    }
}

bool HSysconfig::apply()
{
    if(!pQtXml) return false;
    pQtXml->writeXML();
    return true;
}
