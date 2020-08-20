/**
 * main.cpp 
 * 翻译程序的主框架,负责文件的读写,主要请求参数的设置,以及开始翻译请求
 * author: Wu Zihao
 * date: 2020.8.20
 */
#include"main.h"

int main(int args, char** argv) {
    InfoIO infoio;
    for(int i = 1; i < args; i++){
        if(strncmp(argv[i], "-f", 2) == 0){
            infoio.SetParams(FROM, argv[i] + 2);
        }else if(strncmp(argv[i], "-t", 2) == 0){
            infoio.SetParams(TO, argv[i] + 2);
        }else if(strncmp(argv[i], "-n", 2) == 0){
            infoio.SetParams(TIMES, argv[i] + 2);
        }else if(strcmp(argv[i], "-h") == 0){
			std::cout << "这是一个生草翻译程序\n"
						<< "在content.txt文件中输入你想翻译的内容,在powershell运行该程序并填入相应的参数,\
						就可在Output/Out.txt文件中得到生草的翻译结果(生草程度取决于你输入的参数)\n"
						<< "-f: 源语言类型,如: -fzh, 默认为zh\n"
						<< "-t; 翻译语言类型,如: -ten, 默认为en\n"
						<< "[-f 与 -t的可选项都为: 中文:zh,英文:en,日文:jp]\n"
						<< "-n: 翻译次数,如: -n20, 默认为20\n"
						<< "-h: 这个帮助文档\n";
			return 0;
        }
    }

    infoio.SetParams(IDKEY, 0);
    infoio.SetParams(CONTENT, 0);
    
    RES res = infoio.CheckParams();
    if (res == PARA_OK) {
		
		
	}
	else if (res == ERR_PARA_Q) {
		infoio.infoOut << "未输入翻译内容 " << std::endl;
	}
	else if (res == ERR_PARA_C) {
		infoio.infoOut << "翻译次数输入错误" << std::endl;
	}
	else if (res == ERR_PARA_ID) {
		infoio.infoOut << "app_id为空" << std::endl;
		infoio.infoOut << "访问 http://api.fanyi.baidu.com/ 获取你的id" << std::endl;
	}
	else if (res == ERR_PARA_KEY) {
		infoio.infoOut << "secret_key为空" << std::endl;
		infoio.infoOut << "访问 http://api.fanyi.baidu.com/ 获取你的key" << std::endl;
	}
	else if (res == ERR_PARA_F) {
		infoio.infoOut << "不支持的翻译源类型 " << std::endl;
		infoio.infoOut << "支持的翻译源类型有:中文:zh,英文:en,日文:jp" << std::endl;
	}
	else if (res == ERR_PARA_T) {
		infoio.infoOut << "不支持的翻译目标类型" << std::endl;
		infoio.infoOut << "支持的翻译目标类型有:中文:zh,英文:en,日文:jp" << std::endl;
	}
	else if (res == ERR_PARA_ST) {
		infoio.infoOut << "源语言类型与翻译语言类型相同" << std::endl;
	}
    return 0;
}

InfoIO::InfoIO() {
    from = "zh", to = "en", transTimes = 20;
    infoIn.open("UserInfo.txt", std::ios::in);
    infoOut.open("Output/Out.txt", std::ios::out | std::ios::trunc);
    sTrans.open("content.txt", std::ios::in);
}

InfoIO::~InfoIO() {
    infoIn.close();
    infoOut.close();
    sTrans.close();
}

template <typename ParamContent>
void InfoIO::SetParams(PTYPE t, ParamContent pC) {
    switch(t){
        case IDKEY: {
            infoIn >> appId;
            infoIn >> key;
            appId = appId.substr(6);
            key = key.substr(10);
            break;
        }
        case CONTENT: {
            std::string s = "";
            while(sTrans >> s){
                transTimes += s + "%20";
            }
            transTimes[transTimes.size() - 3] = '\0';
            break;
        }
        case FROM: {
            from = pC;
            break;
        }
        case TO: {
            to = pC;
            break;
        }
        case TIME: {
            transTimes = pC;
            break;
        }
    }
}

RES InfoIO::CheckParams() {
    if(transContent.size() == 0){
        return ERR_PARA_Q;
    }else if(transTimes == 0){
        return ERR_PARA_C;
    }else if(appId.size() == 0){
        return ERR_PARA_ID;
    }else if(key.size() == 0){
        return ERR_PARA_KEY;
    }else if(from != "zh" && from != "en" && from != "jp"){
        return ERR_PARA_F;
    }else if(to != "zh" && to != "en" && to != "jp"){
        return ERR_PARA_T;
    }else if(to == from){
        return ERR_PARA_ST;
    }
    return PARA_OK;
}

std::string StartTranslate() {

}