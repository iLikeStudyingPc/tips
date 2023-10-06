#include <stdio.h>
#include "save.h"
#include <stdlib.h>
#include <string.h>

#include "function.h"
#define __DEBIAN 1
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
/*软件开启准备活动,告诉软件存档位置，但是并不会读取这些存档,首次初始化返回NULL,当mod==1时候重新初始化*/
extern char *Initialize(int mod) {
  return_fileplace();
  char *workspace = malloc(100 * sizeof(char));
  *(workspace + 0) = '\0';
  strcat(strcpy(workspace, workdirname.name[0]), "setting.data");
  FILE *thespace = fopen(workspace, "r");
  if (thespace == NULL||mod==1) {
    workdirname.language = english_US; /*默认语言设置为英文*/
    {
      /*
      **告知软件tips基本结构体等存档路径,但文件并不被创建
      */
      strcat(strcpy(workdirname.name[1], workdirname.name[0]), "mytips.data");
      strcat(strcpy(workdirname.name[2], workdirname.name[0]), "txt_dir/");
      strcat(strcpy(workdirname.name[4], workdirname.name[0]), "save/");
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
  if (workdirname.name[3][0] == '\0') {
#ifdef __WIN32
    strcpy(workdirname.name[3], "notepad");
#elif __linux__
    strcpy(workdirname.name[3], "nano");
#endif
  }
  /*如果默认的编辑器不存在则申请修改编辑器*/
  if (!detection_program_exist(workdirname.name[3])) {
    /*设置失败*/
    if (!set_txt_program()) {
      exit(EXIT_FAILURE);
    }
  }
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
        wprintf(L"Create dir: %s\n", string);
// debian
#if __DEBIAN
        char command[strlen(string) + 50];
        strcat(strcpy(command, "sudo mkdir -p "), string);
        system(command);
        strcat(strcpy(command, "sudo chmod 777 "), string);
        system(command);
        if (stat(string, &st) != -1) {
          return 1;
        }
#endif
        printf("Unable to create folder\n");
        return 0;
      }
    }
  }
#endif
  return 1;
}
void save_optons(void) {
  char str[strlen(workdirname.name[0]) + 255];
  sprintf(str, "%s%s", workdirname.name[0], "setting.data");
  FILE *savefile = fopen(str, "w");
  if (savefile != NULL) {
    fwrite(&workdirname, sizeof(Workdirname2023927), 1, savefile);
    fclose(savefile);
  } else {
    wprintf(L"save option error\n");
    exit(EXIT_FAILURE);
  }
  return;
}

/*
 *用于设置软件文本编辑器软件
 *设置失败，则返回0，设置成功就返回1,并修改workdirname.name[3]
 */
int change_txt_program(char *str) {
  if (detection_program_exist(str)) {
    strcpy(workdirname.name[3], str);
    return 1;
  } else {
    return 0;
  }
}