#include "function.h"
/*代表着工作保存路径*/
Workdirname2023927 workdirname;
/*用于初始化文件仓库*/
static void return_fileplace(void) {
#ifdef __linux__
  char *xdg_docs = getenv("XDG_DOCUMENTS_DIR");
  if (xdg_docs) {
    strcpy(workdirname.name[0], xdg_docs);
  } else {
    strcpy(workdirname.name[0], getenv("HOME"));
    strcat(workdirname.name[0], "/Documents");
  }
  // 拼接具体文件名
  strcat(workdirname.name[0], "/mytips/");
  // 检测文件夹是否存在
  struct stat st;
  if (stat(workdirname.name[0], &st) == -1) {
    // 文件夹不存在，创建文件夹
    if (!mkdir(workdirname.name[0], 0777) == 0) {
      printf("初始化错误:无法创建文件夹\n");
      exit(EXIT_FAILURE);
    }
  }
#elif __WIN32
  TCHAR docPath[MAX_PATH];
  if (SUCCEEDED(SHGetFolderPath(NULL, CSIDL_PERSONAL, NULL, 0, docPath))) {
    // 处理获取到的文档目录路径
    strcpy(workdirname.name[0], docPath);
    char *str = NULL;
    while ((str = strchr(workdirname.name[0], '\\')) != NULL) *str = '/';
  } else {
    printf("错误:无法找到文档路径\n");
    exit(EXIT_FAILURE);
  }
  strcat(workdirname.name[0], "\\mytips\\");
  if (GetFileAttributesA(workdirname.name[0]) == INVALID_FILE_ATTRIBUTES) {
    // 文件夹不存在，创建文件夹
    if (!CreateDirectoryA(workdirname.name[0], NULL)) {
      printf("初始化错误:无法创建文件夹\n");
      exit(EXIT_FAILURE);
    }
  }
#endif
}
extern char* Initialize(void) {
  return_fileplace();
  char *workspace=malloc(100*sizeof(char));
  *(workspace+0)='\0';
  strcat(strcat(workspace,workdirname.name[0]),"sava.data");
  FILE *thespace=fopen(workspace,"r+");
  if(thespace==NULL){
    printf("%s not found\n\n",workspace);
    /*
    **告知软件tips基本结构体存档路径,并创建
    */
    {
      strcat(strcat(workspace,workdirname.name[0]),"mytips.data");
      thespace=fopen(workspace,"w");
      fclose(thespace);
    }
    /*
    **创建初始化存档目录
    */
    strcat(strcat(workspace,workdirname.name[0]),"sava.data");
    thespace=fopen(workspace,"w");
    strcpy(workdirname.name[9],"project debug2");
    fwrite(&workdirname,sizeof(Workdirname2023927),1,thespace);
  }else{
    fread(&workdirname,sizeof(Workdirname2023927),1,thespace);
  }
  free(workspace);
  fclose(thespace);
  return workdirname.name[0];
}