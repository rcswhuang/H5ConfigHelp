#include "hxml.h"
#include <QFile>
HXML::HXML()
{

}

HXML::~HXML()
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
void HXML::parseXML()
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
            e.attribute("ID",strId);
            int nId = strId.toUShort();
            parseDomNode(n,nId);
        }
        n = n.nextSibling();
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
