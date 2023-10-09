#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <dirent.h>
#include "function.h"
#include "save.h"
/*返回存档树的位置*/
static void return_fileplace(void) {
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
}
/*软件开启准备活动,告诉软件存档位置，但是并不会读取这些存档,首次初始化返回NULL,当mod==1时候重新初始化*/
extern char *Initialize(int mod) {
  return_fileplace();
  char *workspace = malloc(100 * sizeof(char));
  *(workspace + 0) = '\0';
  strcat(strcpy(workspace, workdirname.name[0]), "setting.data");
  FILE *thespace = fopen(workspace, "r");
  if (thespace == NULL || mod == 1) {
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
    strcpy(workdirname.name[3], "nano");
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
  {
    struct stat st;
    if (stat(string, &st) == -1) {
      // 文件夹不存在，创建文件夹
      if (!mkdir(string, 0777) == 0) {
        wprintf(L"Create dir: %s\n", string);
        char command[strlen(string) + 50];
        strcat(strcpy(command, "sudo mkdir -p "), string);
        system(command);
        strcat(strcpy(command, "sudo chmod 777 "), string);
        system(command);
        if (stat(string, &st) != -1) {
          return 1;
        }
        printf("Unable to create folder\n");
        return 0;
      }
    }
  }
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

/*
这个函数用于判断给定路径是否是一个目录。
使用方法：
int result = is_directory("/path/to/directory");
if (result) {
    printf("给定路径是一个目录。\n");
} else {
    printf("给定路径不是一个目录。\n");
}
*/
int is_directory(const char *path) {
  struct stat file_stat;
  if (stat(path, &file_stat) == 0) {
    return S_ISDIR(file_stat.st_mode);
  }
  return 0;
}

/*filedir是一个文件夹，在linux中运行，首先检测文件夹有效性，然后进入到目录内，返回一系列该目录中的文件名，但不返回文件夹名，
  get_files这个函数返回给定目录中的文件名数组。返回的数组以NULL结尾。
  使用方法：
  char **files = get_files("/path/to/directory");
    if (files == NULL) {
    printf("无法返回文件。\n");
    return 1;
  }
  for (int i = 0; files[i] != NULL; i++) {
    printf("%s\n", files[i]);
    free(files[i]);
  }
  free(files);
*/
char **get_files(const char *directory) {
  DIR *dir;
  struct dirent *entry;

  dir = opendir(directory);
  if (dir == NULL) {
    return NULL;
  }

  char **files = malloc(100 * sizeof(char *));
  int count = 0;

  while ((entry = readdir(dir)) != NULL) {
    if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
      continue;
    }

    char file_path[1024];
    snprintf(file_path, sizeof(file_path), "%s/%s", directory, entry->d_name);

    if (!is_directory(file_path)) {
      files[count] = malloc(strlen(entry->d_name) + 1);
      strcpy(files[count], entry->d_name);
      count++;
    }
  }
  closedir(dir);
  files[count] = NULL;
  return files;
}

/*在文件夹里选择文件,无文件则返回0*/
char *_chosefile(char *str) {
  char **files = get_files(workdirname.name[4]);
  int length = 0, chose = 0, ch = 0;
  /*取得文件列表长度*/
  for (length = 0; files[length] != NULL; length++)
    ;
  if (length == 0) {
    return NULL;
  }
  do {
    /*控制选择列表箭头*/
    switch (ch) {
      case 72:
        chose -= 1;
        break;
      case 80:
        chose += 1;
        break;
    }
    if (chose < 0) {
      chose = length - 1;
    } else if (chose >= length) {
      chose = 0;
    }
    system("clear");
    /*注意限制范围!!!*/
    wprintf(L"%ls\n", language_pack.Please_select_an_archive_to_load);
    for (int i = chose - 2; i < chose + 3; i++) {
      if (i < 0) {
        wprintf(L"^^^^^^^^^^^^^^^^^^^^^^\n");
      } else if (i >= length) {
        wprintf(L"vvvvvvvvvvvvvvvvvvvvvv\n");
      } else {
        wprintf(L"%s", files[i]);
        if (i == chose) wprintf(L" <--choise");
        wprintf(L"\n");
      }
    }
  } while ((ch = getch()) != '\r' && ch != '\n');
  return files[chose];
}