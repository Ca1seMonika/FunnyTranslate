/**
 * main.cpp 
 * 翻译程序的主框架,负责文件的读写,主要请求参数的设置,以及开始翻译
 * author: Wu Zihao
 * date: 2020.8.20
 */
#include"main.h"

int main(int args, char** argv) {
    InfoIO infoio;

    if(args != 1){
        std::cout
                << "这是一个生草翻译程序\n"
                << "在content.txt文件中输入你想翻译的内容, 在powershell运行该程序, 在该程序运行结束后就可在Output/Out.txt看到翻译结果\n"
                << "为保证软件正常运作, 翻译内容不要超过6000个字节(中文约2000字)\n"
                << "您不需要输入任何参数\n";
        return 0;
    }

    infoio.SetParams(IDKEY);
    infoio.SetParams(CONTENT);

    RES res = infoio.CheckParams();
    if (res == PARA_OK) {
        infoio.Start();
    }
    else if (res == ERR_PARA_Q) {
        std::cout << "未输入翻译内容 " << std::endl;
    }
    else if (res == ERR_PARA_ID) {
        std::cout << "app_id为空" << std::endl;
        std::cout << "访问 http://api.fanyi.baidu.com/ 获取你的id" << std::endl;
    }
    else if (res == ERR_PARA_KEY) {
        std::cout << "secret_key为空" << std::endl;
        std::cout << "访问 http://api.fanyi.baidu.com/ 获取你的key" << std::endl;
    }
    return 0;
}

InfoIO::InfoIO() {
    infoIn.open("UserInfo.txt", std::ios::in);
    infoOut.open("Output/Out.txt", std::ios::out | std::ios::trunc);
    sTrans.open("content.txt", std::ios::in);
}

InfoIO::~InfoIO() {
    infoIn.close();
    infoOut.close();
    sTrans.close();
}

void InfoIO::SetParams(PTYPE t) {
    switch (t) {
        case IDKEY: {
            infoIn >> appId;
            infoIn >> key;
            try {
                if(appId.size() < 7 || key.size() < 11){
                    throw "UserInfo.txt可能未创建,请创建UserInfo.txt并填入你的appid与key";
                }
                appId = appId.substr(7);
                key = key.substr(11);
            } catch (const char* errmsg){
                std::cerr << errmsg << std::endl;
                exit(-1);
            }
            break;
        }
        case CONTENT: {
            std::string s = "";
            sTrans >> s;
            transContent += s;
            while (sTrans >> s) {
                transContent += " " + s;
            }
            break;
        }
    }
}

RES InfoIO::CheckParams() {
    if(transContent.size() == 0){
        return ERR_PARA_Q;
    }else if(appId.size() == 0){
        return ERR_PARA_ID;
    }else if(key.size() == 0) {
        return ERR_PARA_KEY;
    }
    return PARA_OK;
}

void InfoIO::Start() {
    std::string transRes;
    Translate translate(transContent);

    transRes = translate.StartTranslate();
    infoOut << transRes;
}