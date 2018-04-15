#ifndef HXML_H
#define HXML_H
#include "hconfigapi.h"
#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/sax/HandlerBase.hpp>
#include <xercesc/dom/DOMDocument.hpp>
#include <xercesc/dom/DOMElement.hpp>
#include <xercesc/dom/DOM.hpp>
#include <xercesc/util/XMLString.hpp>
#include "hsysconfig.h"
XERCES_CPP_NAMESPACE_USE

//#include <xercesc/dom/DOMErrorHandler.hpp>

//extern SETTING* findSettingById(ushort wSettingId);
class HXML
{
public:
    HXML();
    HXML(const char* file);
    ~HXML();
public:
    void setSysconfig(HSysconfig* sysconfig);
    void parseXML();
    //分开写是为了后期增加和修改方便,每个设置对应一个读写。
    //维护比较方便
    void parseDomNode(const QDomNode& dom,ushort id);

    void parseDOMElement(DOMElement* &element,HSysSetList* pSysSetList);
public:
    HSysconfig* m_pSysConfig;
private:
    //通过调用文件接口获取目录
    QString strConfigFile;
    const char* m_xmlFile;
};

#endif // HXML_H
