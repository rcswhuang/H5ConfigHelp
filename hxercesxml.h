#ifndef HXERCESXML_H
#define HXERCESXML_H
#include "hconfigapi.h"
#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/util/XercesDefs.hpp>
#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/sax/HandlerBase.hpp>
#include <xercesc/dom/DOMDocument.hpp>
#include <xercesc/dom/DOMElement.hpp>
#include <xercesc/dom/DOM.hpp>
#include <xercesc/util/XMLString.hpp>
#include <xercesc/util/OutOfMemoryException.hpp>
XERCES_CPP_NAMESPACE_USE
class HSysconfig;


/*
 * 注释:xerces易用性太差，远不如Qt。此处备份留作参考。实际分析采用qt类
*/


class XStr
{
public :
    // -----------------------------------------------------------------------
    //  Constructors and Destructor
    // -----------------------------------------------------------------------
    XStr(const char* const toTranscode)
    {
        // Call the private transcoding method
        fUnicodeForm = XMLString::transcode(toTranscode);
    }

    ~XStr()
    {
        XMLString::release(&fUnicodeForm);
    }


    // -----------------------------------------------------------------------
    //  Getter methods
    // -----------------------------------------------------------------------
    const XMLCh* unicodeForm() const
    {
        return fUnicodeForm;
    }

private :
    // -----------------------------------------------------------------------
    //  Private data members
    //
    //  fUnicodeForm
    //      This is the Unicode XMLCh format of the string.
    // -----------------------------------------------------------------------
    XMLCh*   fUnicodeForm;
};

#define X(str) XStr(str).unicodeForm()

class HXercesXML
{
public:
    HXercesXML();
    HXercesXML(const char* file);
    ~HXercesXML();
public:
    void setSysconfig(HSysconfig* sysconfig);
    void parseXML();
    void writeXML();
    void parseDOMElement(DOMElement* &element,HSysSetList* pSysSetList);
public:
    HSysconfig* m_pSysConfig;
private:
    //通过调用文件接口获取目录
    QString strConfigFile;
    const char* m_xmlFile;
};

#endif // HXML_H
