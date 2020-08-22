#include"Translate.h"

extern std::string appId;
extern std::string key;
const char* url = "http://api.fanyi.baidu.com/api/trans/vip/translate";

char* UnicodeToUtf8(const wchar_t* unicode)
{
	int len;
	len = WideCharToMultiByte(CP_UTF8, 0, unicode, -1, NULL, 0, NULL, NULL);
	char* szUtf8 = (char*)malloc(len + 1);
	memset(szUtf8, 0, len + 1);
	WideCharToMultiByte(CP_UTF8, 0, unicode, -1, szUtf8, len, NULL, NULL);
	return szUtf8;
}

Translate::Translate(std::string content,
                    std::string from,
                    std::string to) {
    this->content = content;
    this->from = from;
    this->to = to;
}

Translate::~Translate() {
}

std::string Translate::StartTranslate(int transTimes) {
    for(int i = 0; i < transTimes; i++){
        SingleTranslate();
    }
    return transResult;
}

void Translate::SingleTranslate() {
    std::string param = "";
    param = SetParam();

    SocketPost socketpost;
    socketpost.SetPostURL(url);
    socketpost.SetPostFields(param);
    socketpost.StartRequest(transResult);

    DealContent();
    std::swap(from, to);

    param = SetParam();
    socketpost.SetPostFields(param);
    socketpost.StartRequest(transResult);

    DealContent();
    std::swap(from, to);

    transResult = content;
}

std::string Translate::SetParam() {
    unsigned char md[17] = {0};
    std::string salt = std::to_string(rand());
    std::string sign = appId + content + salt + key;
    std::string param;
	char temp[3] = { '\0' }, buf[33] = { '\0' };

	MD5((unsigned char*)sign.c_str(), sign.size(), md);
	for (int i = 0; i < 16; i++) {
		sprintf(temp, "%2.2x", md[i]);
		strcat(buf, temp);
	}

    param = "q=" + content + "&from=" + from + "&to=" + to + "&appid=" + appId + "&salt=" + salt + "&sign=" + sign;
    return param;
}

void Translate::DealContent() {
    if(to == "zh" || to == "jp"){
        char tmp[5] = { '\0' };
        wchar_t wst[10000] = {L'\0'};
        size_t data, cnt=0;

        transResult.insert(0, "      ");

        for (size_t i = 2; i < strlen(tmp); i += 6) {
            if (i != 2) {
                strncpy(tmp, transResult.c_str() + i, 4);
                sscanf(tmp, "%4x", &data);
                wst[cnt++] = data;
            }
            for (i = i + 4; i < transResult.size() && transResult[i] != '\\'; i++) {
                wst[cnt++] = transResult[i];
            }
            i=i-4;
        }
        wst[wcslen(wst)] = L'\0';

        content = std::string(UnicodeToUtf8(wst));
    }else{
        content.clear();
        std::string tmp = "";
        std::stringstream ss(transResult);
        while(ss >> tmp){
            content += tmp + "%20";
        }
        content[content.size() - 3] = '\0';
    }
}