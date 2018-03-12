#ifndef HSYSCONFIGAPI_H
#define HSYSCONFIGAPI_H

#include "sysconfigapi_global.h"
#include "hxml.h"
#include <QList>
class HSysconfigapi
{

public:
    HSysconfigapi();
    ~HSysconfigapi();
public:
    void initSysSet();
    //void loadSysSet(HSysSetList* &pSysSetList,ushort wSettingId);
    //void saveSysSet(HSysSetList* &pSysSetList,ushort wSettingId);
    HSysSetList* getSysSetById(ushort wSettingID);
    void getSettingValue(ushort wSettingID,ushort wSysSetID,QVariant* &value);

private:
    HXML *pXml;
    HSettingList* pSettingList;
    HSysSetList* pNormalSysSetList;//一般设置
    HSysSetList* pNetSysSetList;//网络设置
    HSysSetList* pPathSysSetList;//路径设置
    HSysSetList* pFunSysSetList;//功能设置
    HSysSetList* pFormatSysSetList;//票号格式设置
    HSysSetList* pTicketSysSetList;//操作票设置
    HSysSetList* pOtherSysSetList;//其他设置
};

#endif // HSYSCONFIGAPI_H
