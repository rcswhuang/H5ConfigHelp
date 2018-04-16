#ifndef HXML_H
#define HXML_H
#include "hsysconfig.h"

#include <QtXml/QDomDocument>
#include <QtXml/QDomElement>
#include <QtXml/QDomNode>
class HSysconfig;
//本xml写发比较定制，没有提供统一的接口的原因就是使用的应用交少
//而且xml的内容比较简单。如果是复杂的xml文件读写存储，则需要提供
//统一接口的xml dll文档
class HQtXML
{
public:
    HQtXML(HSysconfig* sysconfig);
    ~HQtXML();
public:
    void parseXML();
    //分开写是为了后期增加和修改方便,每个设置对应一个读写。
    //维护比较方便
    void parseDomNode(const QDomNode& dom,HSysSetList* pList);
    void writeXML();
    void writeDomNode(QDomDocument& doc,QDomElement& root,HSysSetList* &pSysSetList);
    void loadSysSet(HSettingList* &sysSetList);
    void saveSysSet(HSettingList* &sysSetList);

public:
    HSysconfig* pSysConfig;
private:
    //通过调用文件接口获取目录
    QString strConfigFile;

};

#endif // HXML_H
