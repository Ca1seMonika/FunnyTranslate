#ifndef _MAIN_H_
#define _MATN_H_

#include<iostream>
#include<fstream>
#include<cstring>
#include<string>
#include"Translate.h"

std::string appId = "";
std::string key = "";

enum RES {
    //所有参数正常
    PARA_OK,
    //app_id为空
    ERR_PARA_ID,
    //key为空
    ERR_PARA_KEY,
    //内容为空
    ERR_PARA_Q,
};

enum PTYPE {
    IDKEY,
    CONTENT,
};

class InfoIO: public std::fstream {
public:
    InfoIO();
    ~InfoIO();

    /**
     * @describe 设置类中appId, key, transContent, transTimes, from, to变量的值
     * @params t: 选择要设置的变量
     * @return void
    */
    void SetParams(PTYPE t);

    /**
     * @describe 检查appId, key, transContent, transTimes, from, to变量的值是否被正确设置
     * @return RES 自定义的枚举类型, 检查的结果
     */
    RES CheckParams();

    /**
     * 调用其他类函数,开始翻译
     * @return void
     */
    void Start();
private:
    std::fstream infoIn;
    std::fstream infoOut;
    std::fstream sTrans;

    std::string transContent;
};

#endif