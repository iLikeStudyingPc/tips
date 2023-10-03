#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
static int make_the_dir(char *string){
  #ifdef __WIN32
  TCHAR docPath[MAX_PATH];
  if (GetFileAttributesA(string) == INVALID_FILE_ATTRIBUTES) {
    // 文件夹不存在，创建文件夹
    if (!make_the_dir(string)) {
      wprintf(L"Unable to create folder\n");
      return 0;
    }
  }
  #endif
  #ifdef __linux__
  {
    struct stat st;
    if (stat(string, &st) == -1) {
    // 文件夹不存在，创建文件夹
      if (!mkdir(string, 0777) == 0) {
        wprintf(L"Unable to create folder\n");
        return 0;
      }
    }
  }
  #endif
  return 1;
}
int main(void) {
  setlocale(LC_ALL, "zh_CN.utf8");
  char filename[]="./helloworld/sav.c";
  {
    FILE *thisfile = fopen(filename, "wb+");
    if (thisfile == NULL) {
      char filedirname[strlen(filename) + 2];
      strcpy(filedirname, filename);
      char *p = strrchr(filedirname, '/');
      *p = '\0';
      wprintf(L"%s\n",filedirname);
      make_the_dir(filedirname);
      thisfile =fopen(filename, "wb+");
    }
  }
}