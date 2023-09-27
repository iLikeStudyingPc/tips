#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "time.h"
#include "unistd.h"
#include "wchar.h"
enum _system { WINDOWS = 10, LINUX, ERROR = 255 };

/*代表着工作保存路径*/
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
extern enum _system thesystem;

/*in structure.c*/

extern char* Initialize(void);
/*in system.c*/
#ifdef _WIN32
#include "conio.h"
#include "shlobj.h"
#include "windows.h"
#elif __linux__
#include <sys/stat.h>
#include <sys/types.h>
extern char getch(void);
#endif

/*in rule.c*/

extern int regular_name(wchar_t* str);

/*in language.c*/

enum p{unknow=0,chinese=1,english};
void set_language(int select);