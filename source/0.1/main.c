#include "function.h"
#include "save.h"
int main(int argc, char** argv) {
  Initialize();
  set_language(chinese_CN);
  wprintf(L"可以打印字符%s\n",workdirname.name[8]);
  wchar_t str[50] = L"";
  for (int i = 1; i < argc; i++) {
    /*将多字符转化为宽字符*/
    {
      *argv++;
      mbstowcs(str,*argv, sizeof(str));
    }
    if(regular_name(str)){
      wprintf(L"合法");
    }else{
      wprintf(L"非法");
    }
    wprintf(L"%d:%ls\n",i,str);
  }
  return EXIT_SUCCESS;
}

