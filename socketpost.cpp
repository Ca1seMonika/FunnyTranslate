#include"socketpost.h"

const char* fm = "POST %s HTTP/1.1\r\n"
                "Accept: */*\r\n"
                "Connection: Keep-Alive\r\n"
                "Content-Type: application/x-www-form-urlencoded;\r\n"
                "Content-Length: %d\r\n"
                "\r\n"
                "%s";

SocketPost::SocketPost() {
    this->addr = "111.202.114.53";
}

SocketPost::~SocketPost() {
}

void SocketPost::SetPostURL(std::string url) {
    this->URL = url;
}

void SocketPost::SetPostFields(std::string& reqContent) {
    this->field = reqContent;
}

void SocketPost::StartRequest(std::string& s) {
    WORD wVersionRequest = MAKEWORD(2, 2);
    WSADATA wsa;

    if (WSAStartup(wVersionRequest, &wsa) != 0) {
        std::cout << "WSA字库初始化失败" << std::endl;
        exit(0);
    }

    SOCKET sockClient = socket(AF_INET, SOCK_STREAM, 0);

    SOCKADDR_IN addrsrv;
    addrsrv.sin_addr.S_un.S_addr = inet_addr(addr.c_str());
    addrsrv.sin_family = AF_INET;
    addrsrv.sin_port = htons(80);

    char httpPostRequest[10000] = {0};
    sprintf(httpPostRequest, fm, URL.c_str(), strlen(field.c_str()), field.c_str());

    if (connect(sockClient, (sockaddr*)&addrsrv, sizeof(sockaddr)) < 0) {
        std::cout << "与服务器连接失败" << std::endl;
        exit(0);
    }

    send(sockClient, httpPostRequest, strlen(httpPostRequest), 0);

    char buf[BUFSIZE + 1] = {0};
    int recv_length;
    while(recv_length = recv(sockClient, buf, BUFSIZE, 0)){
        s += std::string(buf).substr(0, recv_length);
        if(recv_length != BUFSIZE)  break;
    }

    const char* ps = strstr(s.c_str(), "dst\":\"");
    if(ps != NULL){
        s = s.substr(ps + 6 - s.c_str(), strlen(ps + 6) - 4);
    }else{
        std::cout << "服务器返回错误, 错误代码:"
                << s.substr(strstr(s.c_str(), "error_code") - s.c_str() + 13, 5)
                << std::endl;
        exit(0);
    }

    closesocket(sockClient);
    WSACleanup();
}