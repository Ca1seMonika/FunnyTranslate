# FunnyTranslate
基于百度翻译的自动生草翻译软件, 利用中英日互相翻译的语义差异性来达到生草翻译的效果, 例子:[谷歌翻译20次法国简介！极度生草 今 日 乳 法](https://www.bilibili.com/video/BV1VA411i7ko?from=search&seid=4951937456691269719)  
## 如何使用?
1.在[百度翻译开放平台](http://api.fanyi.baidu.com/)创建你的账户并申请通用翻译api(免费)  
2.下载Release文件夹, 在UserInfo.txt中填入平台分配给你的appid与key, 保存并关闭  
3.在content.txt文件中输入你要翻译的结果  
4.打开powershell进入Release文件夹, 输入命令:
```
.\FunnyTranslate
```
5.在程序运行结束后(大约30s)在Output/Out.txt中查看翻译结果  
  
此项目不会泄露你申请的appid和key(没啥用), 你也可以自己编译该项目
