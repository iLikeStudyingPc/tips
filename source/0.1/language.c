#include <locale.h>
#include <stdio.h>
#include <string.h>
typedef struct Workdirname2023 {
  /*
  !workdirname.name[0]:公共路径
  !workdirname.name[1]:软件tips基本结构体存档路径
  ?workdirname.name[8]:语言支持
  ?workdirname.name[9]:软件版本
  */
  char name[10][100];
} Workdirname2023927;

extern Workdirname2023927 workdirname;

static void language_group_set(int select);

enum p{unknow=0,chinese=1,english};
/*设置语言支持*/
void set_language(int select){
  /*设置为中文*/
  if(select==chinese){
    strcpy(workdirname.name[8],setlocale(LC_ALL, "zh_CN.utf8"));
    language_group_set(chinese);
  /*设置为英语*/
  } else if(select==english){
    strcpy(workdirname.name[8],setlocale(LC_ALL, "en_US.utf8"));
    language_group_set(english);
  }else{
    strcpy(workdirname.name[8],setlocale(LC_ALL,NULL));
    language_group_set(unknow);
  }
}
/*设置语言集显示内容*/
static void language_group_set(int select){
  /*未编写区域，将会在之后支持*/
  return;
}