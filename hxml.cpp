#include "hxml.h"
#include <QFile>

#if defined(XERCES_NEW_IOSTREAMS)
#include <iostream>
#else
#include <iostream.h>
#endif

XERCES_CPP_NAMESPACE_USE

HXML::HXML()
{
    try
    {
        XMLPlatformUtils::Initialize();
    }
    catch (const XMLException& toCatch)
    {
         XERCES_STD_QUALIFIER cerr << "Error during initialization! :\n"
              << XMLString::transcode(toCatch.getMessage()) << XERCES_STD_QUALIFIER endl;
    }
}

HXML::HXML(const char* file)
{
    try
    {
        XMLPlatformUtils::Initialize();
    }
    catch (const XMLException& toCatch)
    {
         XERCES_STD_QUALIFIER cerr << "Error during initialization! :\n"
              << XMLString::transcode(toCatch.getMessage()) << XERCES_STD_QUALIFIER endl;
    }
    m_xmlFile = file;
}

HXML::~HXML()
{
    XMLPlatformUtils::Terminate();
}

void HXML::setSysconfig(HSysconfig *sysconfig)
{
    m_pSysConfig = sysconfig;
}
void HXML::parseXML()
{
    /*QDomDocument doc;
    QFile file(strConfigFile);
    if (!file.open(QIODevice::ReadOnly))
        return;
    if (!doc.setContent(&file)) {
        file.close();
        return;
    }
    file.close();*/

    // print out the element names of all elements that are direct children
    // of the outermost element.
    XercesDOMParser *domParser = new XercesDOMParser();
    domParser->setDoNamespaces(false);
    domParser->setValidationScheme(XercesDOMParser::Val_Auto);
    ErrorHandler* errHandle = (ErrorHandler*) new HandlerBase();
    domParser->setErrorHandler(errHandle);

    try
    {
        domParser->parse(m_xmlFile);
    }
    catch(const SAXException &toCatch)
    {
        XERCES_STD_QUALIFIER cerr << "SAXException error :\n"
             << XMLString::transcode(toCatch.getMessage()) << XERCES_STD_QUALIFIER endl;
        return;
    }
    catch(const XMLException &toCatch)
    {
        XERCES_STD_QUALIFIER cerr << "XMLException error :\n"
             << XMLString::transcode(toCatch.getMessage()) << XERCES_STD_QUALIFIER endl;
        return;
    }
    catch(const DOMException &toCatch)
    {
        XERCES_STD_QUALIFIER cerr << "DOMException error :\n"
             << XMLString::transcode(toCatch.getMessage()) << XERCES_STD_QUALIFIER endl;
        return;
    }

     DOMDocument *doc = domParser->getDocument(); // doc
     DOMElement *root = doc->getDocumentElement();//root

     if(!root)
     {
         delete(domParser);
         domParser = NULL;
         return;
     }
     //获取第一个元素
     DOMElement *child = root->getFirstElementChild(); //SETTING
     while(child)
     {
         char *szId = XMLString::transcode(paraElement->getAttribute(XMLString::transcode("id")));
         int id = atoi(szId);
         HSysSetList* pSysSetList = m_pSysConfig->getSysSetById(id);
         if(!pSysSetList) continue;
         parseDOMElement(child,pSysSetList);
         child = child->getNextElementSibling();
     }
}

void HXML::parseDOMElement(DOMElement *&element,HSysSetList* pSysSetList)
{
    if(!element) return;
    DOMElement* paraElement = element->getFirstElementChild();//PARAMETER
    while(paraElement)
    {
        SYSSET* sysSet = new SYSSET;
        char *id = XMLString::transcode(paraElement->getAttribute(XMLString::transcode("id")));
        sysSet->id = atoi(id);
        XMLString::release(&id);
        char *value = XMLString::transcode(paraElement->getAttribute(XMLString::transcode("value")));
        sysSet->var = QVariant(value);
        XMLString::release(&value);
        pSysSetList->append(sysSet);
        paraElement = paraElement->getNextElementSibling();
    }
}



void HXML::parseDomNode(const QDomNode& dom,ushort id)
{
    SETTING* setting;// = findSettingById(id);
    if(setting == NULL)
        return;
    QDomNode n = dom.firstChild();//PARAM
    while(!n.isNull())
    {
        QDomElement e = n.toElement(); // try to convert the node to an element.
        if(!e.isNull())
        {
            if(e.tagName() == "PARAMETER")
            {
                //objName,id,value
                SYSSET* sysSet = new SYSSET;
                e.attribute("OBJNAME",sysSet->strObjName);
                QString strValue;
                e.attribute("VALUE",strValue);
                sysSet->var = QVariant(strValue);
                setting->pSysSetList->append(sysSet);
            }
        }
        n = n.nextSibling();
    }
}
