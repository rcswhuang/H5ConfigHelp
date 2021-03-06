﻿#ifndef HQTXML_H
#define HQTXML_H
#include "hsysconfig.h"
#include <QtXml/QDomDocument>
#include <QtXml/QDomElement>
#include <QtXml/QDomNode>
class HSysconfig;

class HQtXml
{
public:
    HQtXml(HSysconfig* sysconfig,QString strConfigXmlFile);
    ~HQtXml();
public:
    void parseXML();
    void parseDomNode(const QDomNode& dom,HSysSetList* pList);
    void writeXML();
    void writeDomNode(QDomDocument& doc,QDomElement& root,HSysSetList* &pSysSetList);

public:
    HSysconfig* pSysConfig;
private:
    //通过调用文件接口获取目录
    QString strConfigFile;

};

#endif // HXML_H
