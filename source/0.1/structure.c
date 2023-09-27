#include "function.h"
/*代表着工作保存路径*/
Workdirname2023927 workdirname;
/*访问文件仓库*/
static void return_fileplace(void) {
  if(thesystem==ERROR){
    printf("系统不被支持\n");
    sleep(3);
    exit(EXIT_FAILURE);
  }
#ifdef __linux__
  // Linux平台获取公用目录路径
  char *xdg_public = getenv("XDG_PUBLICSHARE_DIR");
  if (xdg_public) {
    strcpy(workdirname.name[0], xdg_public);
  } else {
    strcpy(workdirname.name[0], "/usr/local/share");
  }
#elif __WIN32
  // Windows平台获取公用目录路径
  TCHAR publicPath[MAX_PATH];
  if (SUCCEEDED(SHGetFolderPath(NULL, CSIDL_COMMON_DOCUMENTS, NULL, 0, publicPath))) {
    // 处理获取到的公用目录路径
    strcpy(workdirname.name[0], publicPath);
    char *str = NULL;
    while ((str = strchr(workdirname.name[0], '\\')) != NULL) *str = '/';
  } else {
    printf("错误:无法找到公用目录路径\n");
    sleep(3);
    exit(EXIT_FAILURE);
  }
#endif
}
extern char* Initialize(void){
  if(workdirname.name[0][0]=='\0'){
    return_fileplace();
  };
  return workdirname.name[0];
}