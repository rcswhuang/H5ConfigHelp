#include "hqtxml.h"
#include "hsysconfig.h"
#include <QFile>
#include <QTextStream>
HQtXml::HQtXml(HSysconfig* sysconfig,QString strConfigXmlFile)
    :pSysConfig(sysconfig),strConfigFile(strConfigXmlFile)
{

}

HQtXml::~HQtXml()
{

}

/*
<SYSCONFIG  NAME=”sysconfig”>
    <SETTING ID="SYS_SET_NET">
        <PARAMETER OBJNAME="" NAME=”com select” VALUE=”com1” />
        <PARAMETER NAME=”com set” VALUE=”9600,n,8,1” />
        ....

        <PARAMETER …../>
   </SETTING>
   <SETTING ID = "SYS_SET_NORMAL">
       ....
   </SETTING>
   ...
</SYSCONFIG>
*/
void HQtXml::parseXML()
{
    QDomDocument doc;
    QFile file(strConfigFile);
    if (!file.open(QIODevice::ReadOnly))
        return;
    if (!doc.setContent(&file)) {
        file.close();
        return;
    }
    file.close();

    // print out the element names of all elements that are direct children
    // of the outermost element.
    QDomElement docElem = doc.documentElement();
    QDomNode n = docElem.firstChild();//SETTING
    while(!n.isNull()) {
        if(!n.hasAttributes())
            continue;
        QDomElement e = n.toElement(); // try to convert the node to an element.
        if(!e.isNull())
        {
            QString strId;
            strId = e.attribute("id");
            if(strId.isEmpty())
                continue;
            int wSettingID = strId.toUShort();
            HSysSetList* pSysSetList = NULL;
            pSysSetList = pSysConfig->getSysSetById(wSettingID);
            if(pSysSetList)
                parseDomNode(n,pSysSetList);
        }
        n = n.nextSibling();
    }

}

void HQtXml::parseDomNode(const QDomNode& dom,HSysSetList* pList)
{
    //SETTING* setting;// = findSettingById(id);
    if(pList == NULL)
        return;
    QDomNode n = dom.firstChild();//PARAM
    while(!n.isNull())
    {
        QDomElement e = n.toElement(); // try to convert the node to an element.
        if(!e.isNull())
        {
            if(e.tagName() == "Parameter")
            {
                SYSSET* sysSet = new SYSSET;
                if(sysSet)
                {
                    QString strId;
                    strId = e.attribute("id");
                    sysSet->id = strId.toUShort();
                    QString strValue;
                    strValue = e.attribute("value");
                    sysSet->var = QVariant(strValue);
                    pList->append(sysSet);
                }
            }
        }
        n = n.nextSibling();
    }
}

void HQtXml::writeXML()
{
    QFile file(strConfigFile);
    if(!file.open(QIODevice::WriteOnly))
        return;
    QTextStream dsm(&file);
    QDomDocument doc;
    QDomProcessingInstruction instruction;
    instruction = doc.createProcessingInstruction("xml" , "version =\"1.0\" encoding=\"UTF-8\"");
    doc.appendChild(instruction);
    QDomElement root = doc.createElement("Sysconfig");
    doc.appendChild(root);

    for(int i = SYS_SET_START+1; i <= SYS_SET_MAX;i++)
    {
        QDomElement setDom = doc.createElement("Setting");
        QDomAttr idAttr = doc.createAttribute("id");
        idAttr.setValue(QString("%1").arg(i));
        setDom.setAttributeNode(idAttr);
        root.appendChild(setDom);
        HSysSetList* pSysSetList = pSysConfig->getSysSetById(i);
        writeDomNode(doc,setDom,pSysSetList);
    }

    dsm.setCodec("UTF-8");
    doc.save(dsm,4);
    file.close();
}

void HQtXml::writeDomNode(QDomDocument &doc,QDomElement& root, HSysSetList* &pSysSetList)
{
    if(pSysSetList == NULL)
        return;
    for(int i = 0; i < pSysSetList->count();i++)
    {
        SYSSET* sysSet = (SYSSET*)pSysSetList->at(i);
        if(sysSet)
        {
            QDomElement dom = doc.createElement("Parameter");
            dom.setAttribute("id",sysSet->id);
            dom.setAttribute("name",sysSet->strObjName);
            dom.setAttribute("value",sysSet->var.toString());
            root.appendChild(dom);
        }
    }
}


void HQtXml::loadSysSet(HSettingList* &sysSetList)
{
    //pSysSetList = sysSetList;
    //parseXML();
}

void HQtXml::saveSysSet(HSettingList* &sysSetList)
{
    //pSysSetList = sysSetList;
    //writeXML();
}
