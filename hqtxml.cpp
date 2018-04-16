#include "hqtxml.h"
#include <QFile>
#include "hsysconfig.h"
HQtXML::HQtXML(HSysconfig* sysconfig)
    :pSysConfig(sysconfig)
{

}

HQtXML::~HQtXML()
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
void HQtXML::parseXML()
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
            e.attribute("id",strId);
            int wSettingID = strId.toUShort();
            HSysSetList* pSysSetList = NULL;
            pSysSetList = pSysConfig->getSysSetById(wSettingID);
            if(!pSysSetList) continue;
            parseDomNode(n,pSysSetList);
        }
        n = n.nextSibling();
    }

}

void HQtXML::parseDomNode(const QDomNode& dom,HSysSetList* pList)
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
                    e.attribute("id",strId);
                    sysSet->id = strId.toUShort();
                    QString strValue;
                    e.attribute("value",strValue);
                    sysSet->var = QVariant(strValue);
                    pList->append(sysSet);
                }
            }
        }
        n = n.nextSibling();
    }
}




void HQtXML::writeXML()
{
    QDomDocument doc("MyML");
    QDomProcessingInstruction instruction;
    instruction = doc.createProcessingInstruction("xml" , "version =\"1.0\" encoding=\"UTF-8\"");
    doc.appendChild(instruction);
    QDomElement root = doc.createElement("Sysconfig");
    doc.appendChild(root);

    for(int i = SYS_SET_START; i < SYS_SET_MAX;i++)
    {
        QDomElement setDom = doc.createElement("Setting");
        QDomAttr idAttr = doc.createAttribute("id");
        idAttr.setValue(QString("%1").arg(i));
        setDom.setAttributeNode(idAttr);
        root.appendChild(setDom);
        HSysSetList* pSysSetList = pSysConfig->getSysSetById(i);
        writeDomNode(doc,root,pSysSetList);
    }
}

void HQtXML::writeDomNode(QDomDocument &doc,QDomElement& root, HSysSetList* &pSysSetList)
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
            dom.setAttribute("value",sysSet->var.toString());
            root.appendChild(dom);
        }
    }
}


void HQtXML::loadSysSet(HSettingList* &sysSetList)
{
    //pSysSetList = sysSetList;
    //parseXML();
}

void HQtXML::saveSysSet(HSettingList* &sysSetList)
{
    //pSysSetList = sysSetList;
    //writeXML();
}
