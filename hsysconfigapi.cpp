#include "hsysconfigapi.h"


HSysconfigapi::HSysconfigapi()
{
}

HSysconfigapi::~HSysconfigapi()
{

}

void HSysconfigapi::initSysSet()
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

    pXml = new HXML();
    pXml->parseXML();
}

HSysSetList* HSysconfigapi::getSysSetById(ushort wSettingID)
{
    if(pSettingList == NULL)
        return NULL;
    if(wSettingID == SYS_SET_NET)
    {
       if(pNetSysSetList)
           return pNetSysSetList;
    }
    else if(wSettingID == SYS_SET_NORMAL)
    {
        if(pNormalSysSetList)
            return pNormalSysSetList;
    }
    else if(wSettingID ==SYS_SET_FUN )
    {
        if(pFunSysSetList)
            return pFunSysSetList;
    }
    else if(wSettingID ==SYS_SET_PATH )
    {
        if(pPathSysSetList)
            return pPathSysSetList;
    }
    else if(wSettingID ==SYS_SET_TICKET)
    {
        if(pTicketSysSetList)
            return pTicketSysSetList;
    }
    else if(wSettingID ==SYS_SET_FORMAT )
    {
        if(pFormatSysSetList)
            return pFormatSysSetList;
    }
    else if(wSettingID ==SYS_SET_OTHER )
    {
        if(pOtherSysSetList)
            return pOtherSysSetList;
    }
    return NULL;
}

void HSysconfigapi::getSettingValue(ushort wSettingID, ushort wSysSetID, QVariant *&value)
{
    HSysSetList* pSysSetList = (HSysSetList*)getSysSetById(wSettingID);
    if(pSysSetList)
    {
        QList<SYSSET*>::iterator it;
        for(it = pSysSetList->begin();it != pSysSetList->end();++it)
        {
            SYSSET* sysSet = *it;
            if(sysSet && sysSet->id == wSysSetID)
            {
                value = &(sysSet->var);
            }
        }
    }
}

