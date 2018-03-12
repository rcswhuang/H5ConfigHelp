#ifndef HSYSCONFIGHANDLE_H
#define HSYSCONFIGHANDLE_H
class HSysconfigapi;
class HSysConfigHandle
{
public:
    static HSysConfigHandle* instance();
    static HSysConfigHandle* pInstance;
    HSysConfigHandle();
public:
    void initSysConfig();
    HSysconfigapi* getSysConfApi(){return pSysConfApi;}
private:
    HSysconfigapi* pSysConfApi;
};

#endif // HSYSCONFIGHANDLE_H
