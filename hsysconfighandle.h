#ifndef HSYSCONFIGHANDLE_H
#define HSYSCONFIGHANDLE_H
#include <iostream>
class HSysconfig;
class HSysConfigHandle
{
public:
    static HSysConfigHandle* instance();
    static HSysConfigHandle* pInstance;
    HSysConfigHandle();
public:
    void initSysConfig(const char* file);
    HSysconfig* getSysConfApi(){return pSysConfApi;}
private:
    HSysconfig* pSysConfApi;
};

#endif // HSYSCONFIGHANDLE_H
