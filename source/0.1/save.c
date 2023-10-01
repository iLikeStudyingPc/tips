#include "function.h"
#include "save.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
static int make_the_dir(char *string);
/*返回存档树的位置*/
static void return_fileplace(void) {
#ifdef __WIN32
  TCHAR docPath[MAX_PATH];
  if (SUCCEEDED(SHGetFolderPath(NULL, CSIDL_PERSONAL, NULL, 0, docPath))) {
    // 处理获取到的文档目录路径
    strcpy(workdirname.name[0], docPath);
    char *str = NULL;
    while ((str = strchr(workdirname.name[0], '\\')) != NULL) *str = '/';
  } else {
    wprintf(L"Initialization error: Unable to find file system user document path\n");
    exit(EXIT_FAILURE);
  }
  strcat(workdirname.name[0], "/mytips/");
  if(!make_the_dir(workdirname.name[0])) exit(EXIT_FAILURE);
#elif __linux__
  char *xdg_docs = getenv("XDG_DOCUMENTS_DIR");
  if (xdg_docs) {
    strcpy(workdirname.name[0], xdg_docs);
  } else {
    strcpy(workdirname.name[0], getenv("HOME"));
    strcat(workdirname.name[0], "/Documents");
  }
  // 拼接具体文件名
  strcat(workdirname.name[0], "/mytips/");
  if(!make_the_dir(workdirname.name[0])) exit(EXIT_FAILURE);
#endif
}
/*软件开启准备活动,告诉软件存档位置，但是并不会读取这些存档*/
extern char* Initialize(void) {
  return_fileplace();
  char *workspace=malloc(100*sizeof(char));
  *(workspace+0)='\0';
  strcat(strcpy(workspace,workdirname.name[0]),"setting.data");
  FILE *thespace=fopen(workspace,"r+");
  if(thespace==NULL){
    workdirname.language=english_US;/*默认语言设置为英文*/
    {
      /*
      **告知软件tips基本结构体等存档路径,但文件并不被创建
      */
      strcat(strcpy(workdirname.name[1],workdirname.name[0]),"mytips.data");
    }
    /*
    **创建初始化存档目录
    */
    strcat(strcpy(workspace,workdirname.name[0]),"setting.data");
    thespace=fopen(workspace,"w");
    /*告知软件版本*/
    strcpy(workdirname.name[9],VERSION);
    fwrite(&workdirname,sizeof(Workdirname2023927),1,thespace);
  }else{
    fread(&workdirname,sizeof(Workdirname2023927),1,thespace);
  }
  free(workspace);
  fclose(thespace);
  return workdirname.name[0];
}
/*读取存档并返回指针，如果存档不存在则创建存档，无法创建的话返回NULL*/
static FILE *read_file(char *filename){
  ;
}

/*创建文件夹，当文件夹不存在时候就创建文件夹，错误创建返回0*/
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
void save_optons(void){
  char str[100];
  sprintf(str,"%s%s",workdirname.name[0],"setting.data");
  FILE *savefile=fopen(str,"w");
  if(savefile!=NULL){
    fwrite(&workdirname,sizeof(Workdirname2023927),1,savefile);
    fclose(savefile);
  }else{
    exit(EXIT_FAILURE);
  }
  return;
}