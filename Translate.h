#ifndef _TRANSLATE_H_
#define _TRANSLATE_H_

#include<string>
#include<winsock2.h>
#include<openssl/md5.h>
#include"curlpost.h"

class Translate {
public:
    Translate(std::string content,
              std::string from,
              std::string to);
    ~Translate();

    /**
     * 开始翻译
     * @params transTimes: 往返翻译的次数
     * @return string 最终翻译的结果
     */
    std::string StartTranslate(int transTimes);

private:
    /**
     * 进行单次翻译
     * @return TRANSRES 自定义枚举类型, 标识翻译是否成功
     */
    void SingleTranslate();

    /**
     * 拼接请求正文
     * @return string 请求正文
     */
    std::string SetParam();

    /**
     * 处理返回内容
     * @return void
     */
    void DealContent();

    std::string content;
    std::string from;
    std::string to;
    std::string transResult;
};

#endif