#include <stdlib.h>
#include <string.h>

#include "function.h"
#include "save.h"
/*
设置程序的退出
*/
void exitnow(void){
  save_optons();
}
/*
主程序
*/
int main(int argc, char** argv) {
  Initialize();
  set_language(workdirname.language);
  for (char** p = argv;*++p!= NULL;) {
    if (regular_command(*p)==0) {
      wprintf(
          L"%ls%ls\n",
          L"Illegal characters, you can only use legal characters, such as:",
          L"@#+_-=,./:");/*非法字符，你只能使用合法字符，例如:@#+_-=,./:*/
      return EXIT_FAILURE;
    }else if(**p=='-'){
      wprintf(L"found \'-\'\n");//调试
    }
  }
  /*在此自检操作之前并未设置退出操作*/
  atexit(exitnow);
  return EXIT_SUCCESS;
}

/*
  wchar_t str[50] = L"";
  for (int i = 1; i < argc; i++) {
    //将多字符转化为宽字符
{
  *argv++;
  mbstowcs(str, *argv, sizeof(str));
}
if (!regular_name(str)) return EXIT_FAILURE;
}
*/

/*
今日任务
1,创建-内容识别器，能够识别命令行，选取功能。默认功能在设置结构体设置，无-识别时候，进行默认功能，默认功能是搜索笔记
2,创建各个语言的报错功能，能够通过设置语种切换报错消息。(切换语言，要使用getch进行)
3，创建结构体字符串，收录笔记内容。


*/