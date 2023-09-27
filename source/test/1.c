#include <wchar.h>
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
int main(void){
  setlocale(LC_ALL, "zh_CN.utf8");
  wprintf(L"合法");
  wprintf(L"非法");
}