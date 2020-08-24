#ifndef _CURLPOST_H_
#define _CURLPOST_H_

#include <string>
#include <iostream>
#include <curl/curl.h>

class CurlPost {
public:
    /**
     * 设置URL
     * @param u: url
     * @return void
     */
     void SetPostURL(const std::string& u);
     /**
      * 设置请求正文
      * @param f: 传入的请求正文
      * @return void
      */
      void SetPostFields(const std::string& f);
      /**
       * 开始post请求
       * @return string 请求结果
       */
      std::string StartPostRequest();
private:
    /**
     * curlpost所需的处理函数
     */
    static size_t req_reply(void* ptr, size_t size, size_t nmemb, void* stream);

    std::string URL;
    std::string fields;
};

#endif