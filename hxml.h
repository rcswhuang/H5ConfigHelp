#ifndef HXML_H
#define HXML_H
#include "sysconfigapi.h"
#include <QtXml/QDomDocument>
#include <QtXml/QDomElement>
#include <QtXml/QDomNode>
//extern SETTING* findSettingById(ushort wSettingId);
class HXML
{
public:
    HXML();
    ~HXML();
public:
    void parseXML();
    //分开写是为了后期增加和修改方便,每个设置对应一个读写。
    //维护比较方便
    void parseDomNode(const QDomNode& dom,ushort id);
public:
    HSettingList* pSettingList;
private:
    //通过调用文件接口获取目录
    QString strConfigFile;

};

#endif // HXML_H
