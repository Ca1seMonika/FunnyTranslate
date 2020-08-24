/**
 * curlpost.cpp
 * 封装curl的post请求
 * @author Wu Zihao
 * @date 2020.8.24
 */

#include "curlpost.h"

const char* CT = "Content-Type: application/x-www-form-urlencoded;\r\n"
                 "User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/84.0.4147.125 Safari/537.36";

void CurlPost::SetPostURL(const std::string& u) {
    this->URL = u;
}

void CurlPost::SetPostFields(const std::string& f) {
    this->fields = f;
}

std::string CurlPost::StartPostRequest() {
    std::string responseContent = "";
    CURL* curl = curl_easy_init();
    CURLcode reqRes;

    if(curl == NULL){
        std::cout << "curl初始化失败,请重试" << std::endl;
        exit(0);
    }

    curl_slist* header = NULL;
    header = curl_slist_append(header, CT);

    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, header);
    curl_easy_setopt(curl, CURLOPT_URL, URL.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void*)&responseContent);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, req_reply);
    curl_easy_setopt(curl, CURLOPT_POST, 1);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, fields.c_str());
    curl_easy_setopt(curl, CURLOPT_HEADER, 0);

    reqRes = curl_easy_perform(curl);
    curl_easy_cleanup(curl);

    if(reqRes != CURLE_OK){
        std::cout << "curl请求失败, 失败原因: " << curl_easy_strerror(reqRes) << std::endl;
        exit(0);
    }

    size_t tar = responseContent.find("error_code");
    if(tar != std::string::npos){
        std::cout << "服务器返回错误, 错误代码: " << responseContent.substr(tar + 13, 5) << std::endl;
        exit(0);
    }

    tar = responseContent.find("dst\":\"");
    return responseContent.substr(tar + 6, responseContent.find_last_of('\"') - tar - 6);
}

size_t CurlPost::req_reply(void *ptr, size_t size, size_t nmemb, void *stream) {
    std::string* str = (std::string*)stream;
    (*str).append((char*)ptr, size * nmemb);
    return size * nmemb;
}