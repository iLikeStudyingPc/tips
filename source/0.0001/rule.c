#include <ctype.h>
#include <string.h>
#include <wchar.h>
#include <wctype.h>
static void toLowerCase(char *str);
struct command_opention{
  int add;
  int change;
  int search;
  int backup;
  int restore;
  int help;
  int man;
  int language;
  int version;
  int rm;
  int rf;
};
/*
**用于检测是否符合名字的规范（只包含字母，数字或者@#+_-=,./:字符）,若符合返回真1，不符合就返回假0
*/
int regular_name(wchar_t *str) {
  for (;; str += 1) {
    if (*str == L'\0') return 1;
    if ((!(iswalnum(*str))) && wcschr(L"@#+_-=,./:", *str) == NULL) {
      return 0;
    }
  }
}
/*
**用于检测命令行是否符合规范（只包含字母，数字或者@#+_-=,./:字符）,若符合返回真1，不符合就返回假0
*/
int regular_command(char *str) {
  for (;; str += 1) {
    if (*str == '\0') return 1;
    if ((!(isalnum(*str))) && strchr("@#+_-=,./:", *str) == NULL) {
      return 0;
    }
  }
}
/*把句子转化为全英语小写*/
static void toLowerCase(char *str) {
    int i = 0;
    while (str[i]!='\0') {
        str[i] = tolower(str[i]);
        i++;
    }
}
/*
**检测字符串，返回命令id，告诉主函数启动。
*/
int whitch_command(char *str, struct command_opention *thisopention) {
  toLowerCase(str);
  if(strcmp(str,"-a")==0||strcmp(str,"-add")==0){
    //wprintf(L"find -add\n");
    thisopention->add=1;
    return 1;
  }
  if(strcmp(str,"-backup")==0){/*备份*/
    wprintf(L"find -backup\n");
    thisopention->backup=1;
    return 1;
  }
  if(strcmp(str,"-s")==0||strcmp(str,"-search")==0){
    wprintf(L"find -search\n");
    thisopention->search=1;
    return 1;
  }
  if(strcmp(str,"-c")==0||strcmp(str,"-change")==0){
    wprintf(L"find -change\n");
    thisopention->change=1;
    return 1;
  }
  if(strcmp(str,"-rm")==0){/*删除*/
    /*wprintf(L"find -rm\n");*/
    thisopention->rm=1;
    return 1;
  }
  if(strcmp(str,"-rf")==0){/*全部同意删除*/
    wprintf(L"find -rf\n");
    thisopention->rf=1;
    return 1;
  }
  if(strcmp(str,"-restore")==0){/*恢复*/
    wprintf(L"find -restore\n");
    thisopention->restore=1;
    return 1;
  }
  if(strcmp(str,"-v")==0||strcmp(str,"-version")==0){
    //wprintf(L"find -version\n");
    thisopention->version=1;
    return 1;
  }
  if(strcmp(str,"-h")==0||strcmp(str,"-help")==0){
    //wprintf(L"find -help\n");
    thisopention->help=1;
    return 1;
  }
  if(strcmp(str,"-man")==0){
    wprintf(L"find -man\n");
    thisopention->man=1;
    return 1;
  }
  if(strcmp(str,"-language")==0){
    thisopention->language=1;
    return 1;
  }
  return 0;
}