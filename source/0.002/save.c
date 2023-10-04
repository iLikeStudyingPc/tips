#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "save.h"
#include "function.h"

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
    wprintf(
        L"Initialization error: Unable to find file system user document "
        L"path\n");
    exit(EXIT_FAILURE);
  }
  strcat(workdirname.name[0], "/mytips/");
  if (!make_the_dir(workdirname.name[0])) exit(EXIT_FAILURE);
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
  if (!make_the_dir(workdirname.name[0])) exit(EXIT_FAILURE);
#endif
}
/*软件开启准备活动,告诉软件存档位置，但是并不会读取这些存档,首次初始化返回NULL*/
extern char *Initialize(void) {
  return_fileplace();
  char *workspace = malloc(100 * sizeof(char));
  *(workspace + 0) = '\0';
  strcat(strcpy(workspace, workdirname.name[0]), "setting.data");
  FILE *thespace = fopen(workspace, "r");
  if (thespace == NULL) {
    workdirname.language = english_US; /*默认语言设置为英文*/
    {
      /*
      **告知软件tips基本结构体等存档路径,但文件并不被创建
      */
      strcat(strcpy(workdirname.name[1], workdirname.name[0]), "mytips.data");
      strcat(strcpy(workdirname.name[2], workdirname.name[0]), "txt_dir/");
    }
    /*
    **创建初始化存档目录
    */
    strcat(strcpy(workspace, workdirname.name[0]), "setting.data");
    thespace = fopen(workspace, "w");
    /*告知软件版本*/
    workdirname.version = VERSION;
    workdirname.default_control = 0;
    fwrite(&workdirname, sizeof(Workdirname2023927), 1, thespace);
    fclose(thespace);
    thespace = fopen(workspace, "r");
    if (thespace != NULL) {
      fread(&workdirname, sizeof(Workdirname2023927), 1, thespace);
    } else {
      wprintf(L"Unable to complete initialization on this computer\n");
      exit(EXIT_FAILURE);
    }
    free(workspace);
    fclose(thespace);
    return NULL;
  } else {
    fread(&workdirname, sizeof(Workdirname2023927), 1, thespace);
  }
  free(workspace);
  fclose(thespace);
  return workdirname.name[0];
}
/*以只读2进制方式打开文件，打不开会返回NULL*/
FILE *read_file(char *filename) {
  FILE *thisfile = fopen(filename, "rb");
  return thisfile;
}
/*以只写2进制方式打开文件，文件不存在就创建，而无法创建的话会返回NULL*/
FILE *write_file(char *filename) {
  FILE *thisfile = fopen(filename, "wb");
  if (thisfile == NULL) {
    char filedirname[strlen(filename) + 2];
    strcpy(filedirname, filename);
    char *p = strrchr(filedirname, '/');
    *p = '\0';
    make_the_dir(filedirname);
    thisfile = fopen(filename, "wb");
  }
  return thisfile;
}

/*创建文件夹，当文件夹不存在时候就创建文件夹，错误创建返回0*/
int make_the_dir(char *string) {
#ifdef __WIN32
  DWORD fileAttributes = GetFileAttributesA(string);
  if (fileAttributes == INVALID_FILE_ATTRIBUTES) {
    // 文件夹不存在，创建文件夹
    if (!CreateDirectoryA(string, NULL)) {
      printf("Unable to create folder\n");
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
void save_optons(void) {
  char str[100];
  sprintf(str, "%s%s", workdirname.name[0], "setting.data");
  FILE *savefile = fopen(str, "w");
  if (savefile != NULL) {
    fwrite(&workdirname, sizeof(Workdirname2023927), 1, savefile);
    fclose(savefile);
  } else {
    exit(EXIT_FAILURE);
  }
  return;
}