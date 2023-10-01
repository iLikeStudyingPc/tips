#include <wctype.h>
#include <wchar.h>
#include <ctype.h>
#include <string.h>
/*
**用于检测是否符合名字的规范（只包含字母，数字或者@#+_-=,./:字符）,若符合返回真1，不符合就返回假0
*/
int regular_name(wchar_t *str){
  for(;;str+=1){
    if(*str==L'\0') return 1;
    if((!(iswalnum(*str)))&&wcschr(L"@#+_-=,./:",*str)==NULL){
      return 0;
    }
  }
}
/*
**用于检测命令行是否符合规范（只包含字母，数字或者@#+_-=,./:字符）,若符合返回真1，不符合就返回假0
*/
int regular_command(char *str){
  for(;;str+=1){
    if(*str=='\0') return 1;
    if((!(isalnum(*str)))&&strchr("@#+_-=,./:",*str)==NULL){
      return 0;
    }
  }
}