#include "hxercesxml.h"
#include "hsysconfig.h"
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
         char *szId = XMLString::transcode(child->getAttribute(XMLString::transcode("id")));
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

void HXML::writeXML()
{
  /*
   * <?xml version="1.0" encoding="utf-8"?>
    <SYSCONFIG  name="sysconfig">
        <SETTING id="SYS_SET_NET">
            <parameter id="com select" value="com1" />
            <parameter id="com set" value="9600,n,8,1" />
       </SETTING>
    </SYSCONFIG>
    */

   DOMImplementation* impl =  DOMImplementationRegistry::getDOMImplementation(X("Core"));

   if (impl != NULL)
   {
       try
       {
           DOMDocument* doc = impl->createDocument(
                       0,                    // root element namespace URI.
                       X("Sysconfig"),         // root element name
                       0);                   // document type object (DTD).

           DOMElement* rootElem = doc->getDocumentElement();
           rootElem->setAttribute(X("name"),X("sysconfig"));
           for(int i = SYS_SET_START; i < SYS_SET_MAX;i++)
           {
               HSysSetList* pSysSetList = m_pSysConfig->getSysSetById(i);
               DOMElement*  settingElem = doc->createElement(X("Setting"));
               settingElem->setAttribute(X("id"),X(std::to_string(i).c_str()));
               rootElem->appendChild(settingElem);
               for(int k = 0; k < pSysSetList->count();i++)
               {
                   SYSSET* sysset = (SYSSET*)pSysSetList->at(i);
                   DOMElement*  paraElem = doc->createElement(X("parameter"));
                   settingElem->appendChild(paraElem);
                   paraElem->setAttribute(X("id"),X(std::to_string(sysset->id).c_str()));
                   paraElem->setAttribute(X("value"),X(sysset->var.toString().toStdString().c_str()));

                   const XMLSize_t elementCount = doc->getElementsByTagName(X("*"))->getLength();
                   XERCES_STD_QUALIFIER cout << "The tree just created contains: " << elementCount
                        << " elements." << XERCES_STD_QUALIFIER endl;

                   doc->release();
               }
            }
       }
       catch (const OutOfMemoryException&)
       {
           XERCES_STD_QUALIFIER cerr << "OutOfMemoryException" << XERCES_STD_QUALIFIER endl;
           //errorCode = 5;
       }
       catch (const DOMException& e)
       {
           XERCES_STD_QUALIFIER cerr << "DOMException code is:  " << e.code << XERCES_STD_QUALIFIER endl;
           //errorCode = 2;
       }
       catch (...)
       {
           XERCES_STD_QUALIFIER cerr << "An error occurred creating the document" << XERCES_STD_QUALIFIER endl;
           //errorCode = 3;
       }
   }  // (inpl != NULL)
   else
   {
       XERCES_STD_QUALIFIER cerr << "Requested implementation is not supported" << XERCES_STD_QUALIFIER endl;
       //errorCode = 4;
   }
}


