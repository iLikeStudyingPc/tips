#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include <wctype.h>
#include "function.h"
#include "language.h"
#include <unistd.h>
static void toLowerCase(char *str);

/*
**用于检测是否符合名字的规范（只包含字母，数字或者@#+_-=,.:字符）,若符合返回真1，不符合就返回假0,首项为-时候返回-1，要求不是命令行
*/
int regular_name(wchar_t *str) {
  if(*str==L'-') return -1;
  for (;; str += 1) {
    if (*str == L'\0') return 1;
    if ((iswalnum(*str)) && wcschr(L"@#+_-=,.:", *str) == NULL) {
      return 1;
    } else {
      return 0;
    }
  }
}
/*
**用于检测命令行是否符合规范（只包含字母，数字或者@#+_-=,.:字符）,若符合返回真1，不符合就返回假0
*/
int regular_command(char *str) {
  for (;; str += 1) {
    if (*str == '\0') return 1;
    if ((!(isalnum(*str))) && strchr("@#+_-=,.:", *str) == NULL) {
      return 0;
    }
  }
}
/*把句子转化为全英语小写*/
static void toLowerCase(char *str) {
  int i = 0;
  while (str[i] != '\0') {
    str[i] = tolower(str[i]);
    i++;
  }
}
/*
**检测字符串，返回命令id，告诉主函数启动。
*/
int whitch_command(char *str, struct command_opention *thisopention) {
  toLowerCase(str);
  if (strcmp(str, "-a") == 0 || strcmp(str, "-add") == 0) {
    // wprintf(L"find -add\n");
    thisopention->add = 1;
    return 1;
  }
  if (strcmp(str, "-save") == 0) { /*备份*/
    thisopention->save = 1;
    return 1;
  }
  if (strcmp(str, "-s") == 0 || strcmp(str, "-search") == 0) {
    wprintf(L"find -search\n");
    thisopention->search = 1;
    return 1;
  }
  if (strcmp(str, "-c") == 0 || strcmp(str, "-change") == 0) {
    wprintf(L"find -change\n");
    thisopention->change = 1;
    thisopention->content = 1;
    return 1;
  }
  if (strcmp(str, "-rm") == 0) { /*删除*/
    /*wprintf(L"find -rm\n");*/
    thisopention->rm = 1;
    return 1;
  }
  if (strcmp(str, "-rf") == 0) { /*全部同意删除*/
    /*wprintf(L"find -rf\n");*/
    thisopention->rf = 1;
    return 1;
  }
  if (strcmp(str, "-l") == 0 || strcmp(str, "-load") == 0) { /*恢复*/
    thisopention->load = 1;
    return 1;
  }
  if (strcmp(str, "-n") == 0||strcmp(str, "-new") == 0) { /*恢复*/
    wprintf(L"find -new\n");
    thisopention->new = 1;
    return 1;
  }
  if (strcmp(str, "-o") == 0||strcmp(str, "-old") == 0) { /*恢复*/
    wprintf(L"find -old\n");
    thisopention->old = 1;
    return 1;
  }
  if (strcmp(str, "-b") == 0||strcmp(str, "-backup") == 0) { /*恢复*/
    thisopention->backup = 1;
    return 1;
  }
  if (strcmp(str, "-v") == 0 || strcmp(str, "-version") == 0) {
    // wprintf(L"find -version\n");
    thisopention->version = 1;
    return 1;
  }
  if (strcmp(str, "-h") == 0 || strcmp(str, "-help") == 0) {
    // wprintf(L"find -help\n");
    thisopention->help = 1;
    return 1;
  }
  if (strcmp(str, "-language") == 0) {
    thisopention->language = 1;
    return 1;
  }
  if (strcmp(str, "-settxt") == 0) {
    thisopention->settxt = 1;
    return 1;
  }
  if (strcmp(str, "-all") == 0) {
    thisopention->all = 1;
    return 1;
  }
  if (strcmp(str, "-name") == 0) {
    thisopention->name = 1;
    return 1;
  }
  if (strcmp(str, "-content") == 0) {
    thisopention->content = 1;
    return 1;
  }
  if (strcmp(str, "-init") == 0) {
    thisopention->init = 1;
    return 1;
  }
  return 0;
}

//(%ls)该文本编辑器软件并未找到，请设置新的文本编辑其软件名：
//(%ls)The text editor software was not found. Please set a new text editor
//software name:
/*
 *用于检测文本编辑器软件在电脑中是否存在，如果不存在则申请宿主设置新的文本编辑器。
 *检测的规则,命令行可执行软件在系统环境中存在就返回1,否则返回0.
 */
int detection_program_exist(char *str) {
  char command[strlen(str) + 40];
  sprintf(command, "command -v %s >/dev/null 2>&1",
          str);  // 使用command -v检测程序是否存在
  if (system(command) == 0) {
    return 1;
  }
  return 0;
}

/*设置txt软件。设置成功返回1，否则为0*/
int set_txt_program(void) {
  char name[500];
  wprintf(L"%ls\n", language_pack.Please_enter_a_new_text_editor_name);
  scanf("%s", name);
  if (detection_program_exist(name)) {
    strncpy(workdirname.name[3], name, 49);
    wprintf(L"%ls\n", language_pack.Text_editor_name_modified_successfully);
    return 1;
  } else {
    wprintf(L"%ls\n", language_pack.Text_editor_name_modification_failed);
    return 0;
  }
}
