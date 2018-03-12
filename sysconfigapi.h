#ifndef SYSCONFIGAPI_H
#define SYSCONFIGAPI_H
#include <QtGlobal>
#include <QVariant>
#include <QList>
#include "sysconfigapi_global.h"
/*
 * 构建此结构的目的就是为了方便xml存储和读取，以及设置和读取控件的值
 * 如果控件保存和读取是按照顺序进行的则结构type可以不需要
 * 另外提供dll供读取xml中的值使用
 * 外部接口:getSettingValue(setting,syssetid,&value)
*/
#ifdef __cplusplus
extern "C"
{
#endif
    void SYSCONFIGAPISHARED_EXPORT getSettingValue(ushort uSettingID,ushort uSysSetID,QVariant* &value);



    typedef struct _tagSysSet
    {
        QString strObjName;
        ushort type;
        ushort id;
        QVariant var;
    }SYSSET;
    typedef QList<SYSSET*> HSysSetList;

    typedef struct _tagSetting
    {
        ushort wSettingId;
        HSysSetList* pSysSetList;
    }SETTING;
    typedef QList<SETTING*> HSettingList;



    //定义功能
    #define SYS_SET_NET     0x001
    #define SYS_SET_NORMAL  0x002
    #define SYS_SET_FUN     0x003
    #define SYS_SET_PATH    0x004
    #define SYS_SET_TICKET  0x005
    #define SYS_SET_FORMAT  0x006
    #define SYS_SET_OTHER   0x007

    //通讯设置
    //电脑钥匙通讯
    #define SYS_KEY_COM_SELECT 0x010
    #define SYS_KEY_COM_SET    0x011
    #define SYS_KEY_COM_TIME   0x012

    //模拟屏通讯
    #define SYS_MNP_COM_SELECT 0x013
    #define SYS_MNP_COM_SET    0x014
    #define SYS_MNP_COM_TIME   0x015


    //模拟屏2通讯
    #define SYS_MNP2_COM_SELECT 0x016
    #define SYS_MNP2_COM_SET    0x017
    #define SYS_MNP2_COM_TIME   0x018

    //优特五防串口通讯
    #define SYS_YT_COM_SELECT  0x019
    #define SYS_YT_COM_SET     0x020
    #define SYS_YT_COM_TIME    0x021

    //闭锁器配置
    #define SYS_BSQ_COM_SELECT 0x022
    #define SYS_BSQ_COM_SET    0x023
    #define SYS_BSQ_COM_TIME   0x024

    //五防机网络
    #define SYS_WF_NET_IPA     0x025
    #define SYS_WF_NET_IPB    0x026
    #define SYS_WF_NET_PORT   0x027

    //五防机编号
    #define SYS_WF_KEY_NUM   0x028


    //一般设置 0x050
    //时间设置
    #define SYS_PASSWORD_VALID_TIME  0x050
    #define SYS_SEND_VIRTUAL_YX_TIME    0x051
    #define SYS_BAT_YX_VALID_TIME 0x052
    //声音设置
    #define SYS_YX_CLOSE_SOUND 0x053
    #define SYS_YX_OPEN_SOUND 0x054
    #define SYS_STATUS_CHECK_FAIL_SOUND 0x055
    #define SYS_RULE_CHECK_FAIL_SOUND 0x056
    //颜色设置
    #define SYS_YX_CHANGE_COLOR 0x057
    #define SYS_YX_MANUAL_COLOR 0x058
    #define SYS_YX_REPAIR_COLOR 0x059
    #define SYS_WF_STATUS_COLOR 0x05A
    //遥控设置
    #define SYS_CTRL_SELECT_TIMEOUT 0x05B
    #define SYS_CTRL_EXECUTE_TIMEOUT 0x5C
    #define SYS_CTRL_DOUBLEYX_TIMEOUT 0x05D
    #define SYS_CTRL_GUARD 0x05E
    #define SYS_CTRL_FORCED_CHECK 0x05F
    #define SYS_NUMBER_CASE_SENSITIVE 0x60

    //路径设置 0x90
    #define SYS_PATH_UNITE_SET 0x090
    #define SYS_PATH_DATA_SET 0x091
    #define SYS_PATH_SYMBOL_SET 0x092
    #define SYS_PATH_EVENT_SET 0x093
    #define SYS_PATH_MACRO_SET 0x094
    #define SYS_PATH_OPNOTE_SET 0x095
    #define SYS_PATH_BITMAP_SET 0x096
    #define SYS_PATH_WORKNOTE_SET 0x097
    #define SYS_PATH_MEDIR_SET 0x098
    #define SYS_PATH_GRAPH_SET 0x099
    #define SYS_PATH_SIGNPAD_SET 0x09A
    #define SYS_PATH_FIL_SET 0x09B
    #define SYS_PATH_UNITE_CHECK 0x09C

    //功能设置 0xD0
    #define SYS_FUN_OPNOTE_MANAGER 0xD0
    #define SYS_FUN_PRINT_SET 0x0D1
    #define SYS_FUN_WORKNOET_MANGER 0x0D2
    #define SYS_FUN_GRAPH_EDITOR 0x0D3
    #define SYS_FUN_EVENT_SCAN 0x0D4
    #define SYS_FUN_WFLOCK_SCAN 0x0D5
    #define SYS_FUN_WF_CONFIG 0x0D6
    #define SYS_KEY_NULL 0x0100
    #define SYS_KEY_YT26  0x0101
    #define SYS_KEY_YT27  0x0102
    #define SYS_KEY_NR_USB  0x0103

    //操作票号设置 0x0110 150 190

    #define TICKET_ONE_TICKET_NUM 0x110
    #define TICKET_ONE_TICKET_PAGE_NUM 0x111
    #define TICKET_ADD_HEAD_TAIL 0x112
    #define TICKET_SHOW_HEAD_TAIL 0x113
    #define TICKET_HEAD_CONTENT 0x114
    #define TICKET_TAIL_CONTENT 0x115
    #define TICKET_PREFIX_SET 0x116
    #define TICKET_SUFFIX_SET 0x117
    #define TICKET_FIX_LENGTH_SET 0x118
    #define TICKET_PREFIX_CONTENT 0x119
    #define TICKET_SUFFIX_CONTENT 0x120
    #define TICKET_FIX_LENGTH_CONTENT 0x121
    #define TICKET_MODIFY_PRETICKET_SET 0x122
    #define TICKET_MODIFY_NEXT_NUM 0x123
    #define TICKET_MODIFY_TICKET_SET 0x124
    #define TICKET_MODIFY_SERIAL_SET 0x125
    #define TICKET_BEGIN_SERIAL_NUM 0x126

    //操作票设置
    #define WF_LOCKYX_CHECK 0x150
    #define WF_AUTOMATCH_CHECK 0x151
    #define WF_ALLWF_YK_CHECK 0x152
    #define WF_PROMPT_CHECK  0x153
    #define WF_MNP_CONFIRM_CHECK  0x154
    #define WF_FORBID_MB_EDITOR_CHECK 0x155
    #define WF_EXEC_TICKET_CHECK 0x156
    #define WF_REFRESH_TICKET_CHECK 0x157
    #define WF_DIRECT_OPERA_CHECK 0x158
    #define WF_PROMPT_NET_CHECK 0x159
    #define WF_FORBID_PRE_CHECK 0x160
    #define WF_JUDGE_MUL_CHECK 0x161
    #define WF_LOCK_ALL_CHECK 0x162
    #define WF_CLEAR_TICKET_CHECK 0x163
    #define WF_SECTION_OPER_CHECK 0x164
    #define WF_FORBID_MODIFY_CHECK 0x165
    #define WF_SAVE_FORBIDMB_CHECK 0x166
    #define WF_CLICK_PROMPT_CHECK 0x167
    #define WF_FROM_MNP_CHECK 0x168
    #define WF_SAVE_STATE_CHECK 0x169
    #define WF_FUJIAN_MODEL_CHECK 0x170
    #define WF_PROMPT_UNDOWN_CHECK 0x171
    #define WF_PRINT_FORBID_WM_CHECK 0x172

    //其他设置
    #define PRIV_SAVE_PRE_TICKET 0x200
    #define PRIV_OPERA_PRE_TICKET 0x201
    #define NAME_GROUP_NAME 0x202
    #define NAME_CUSTOM_NAME 0x203
    #define STATE_CHANGE_STATION_NAME 0x204
    #define STATE_CHANGE_VOLTAGE 0x205
    #define STATE_CHANGE_INTERVAL_NAME 0x206
    #define STATE_CHANGE_DIGITAL_NAME 0x207
    #define STATE_CHANGE_NULL 0x208


#ifdef __cplusplus
}
#endif


#endif
