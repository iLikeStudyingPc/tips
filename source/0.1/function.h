#include "stdio.h"
#include "time.h"
#include "stdlib.h"
#include "string.h"
#include "unistd.h"
#include "ctype.h"
enum _system{WINDOWS=10,LINUX,ERROR=255};

/*代表着工作保存路径*/
typedef struct Workdirname2023{
  /*
  !workdirname.name[0]:公共路径
  */
  char name[10][100];
}Workdirname2023927;

extern enum _system thesystem;
/*in structure.c*/
/*软件的初始化*/
extern char* Initialize(void);
#ifdef _WIN32
#include "shlobj.h"
#include "windows.h"
#include "conio.h"
#elif __linux__
#include <sys/stat.h>
#include <sys/types.h>
extern char getch(void);
#endif





