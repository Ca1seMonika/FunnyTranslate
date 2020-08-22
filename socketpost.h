#ifndef _SOCKETPOST_H_
#define _SOCKETPOST_H_

#include<WinSock2.h>
#include<string>
#include<cstring>
#include<iostream>

#define BUFSIZE 2048

class SocketPost {
public:
	SocketPost();
	~SocketPost();
	/**
	 * 设置post请求的url
	 * @params url: 请求的url
	 * @return void
	 */
	void SetPostURL(std::string url);
	/**
	 * 设置post请求的请求正文
	 * @params reqContent: 请求内容
	 * @return void
	 */
	void SetPostFields(std::string& reqContent);
	/**
	 * 开始post请求
	 * @params s: 接收服务器的返回信息
	 * @return REQRES 自定义枚举类型, 表示请求结果
	 */
	void StartRequest(std::string& s);
private:
	std::string URL;
	std::string field;
	std::string addr;
};

#endif