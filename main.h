#ifndef _MAIN_H_
#define _MATN_H_

#include<iostream>
#include<fstream>
#include<cstring>
#include"Translate.h"

enum RES {
    //所有参数正常
    PARA_OK,
    //不支持的语言类型
    ERR_PARA_F,
    //不支持的语言类型
    ERR_PARA_T,
    //app_id为空
    ERR_PARA_ID,
    //key为空
    ERR_PARA_KEY,
    //内容为空
    ERR_PARA_Q,
    //翻译次数为0
    ERR_PARA_C,
    //参数from与to相同
    ERR_PARA_ST
};

enum PTYPE {
    IDKEY,
    CONTENT,
    FROM,
    TO,
    TIMES
};

class InfoIO: public std::fstream {
public:
    InfoIO();
    ~InfoIO();

    /**
     * @describe 设置类中appId, key, transContent, transTimes, from, to变量的值
     * @params t: 选择要设置的变量, pC: 设置的内容
     * @return void
    */
    template <typename ParamContent>
    void SetParams(PTYPE t, ParamContent pC);

    /**
     * @describe 检查appId, key, transContent, transTimes, from, to变量的值是否被正确设置
     * @return RES 自定义的枚举类型, 检查的结果
     */
    RES CheckParams();

    /**
     * @describe 调用其他类的函数, 开始翻译
     * @return string 翻译的结果
     */
    std::string StartTranslate();

    std::fstream infoOut;
private:
    std::fstream infoIn;
    std::fstream sTrans;

    std::string transContent;
    std::string appId;
    std::string key;
    std::string from;
    std::string to;
    int transTimes;

    Translate translate;
};

#endif