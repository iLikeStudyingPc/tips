#include <wchar.h>
#define VERSION 0.12
enum _system { WINDOWS = 10, LINUX, ERROR = 255 };
/*代表着工作保存路径*/
typedef struct Workdirname2023 {
  /*
  !workdirname.name[0]:公共路径,公共路径里包含文件setting.data，存储其他软件的存档路径
  !workdirname.name[1]:软件tips基本结构体存档路径
  !workdirname.name[2]:文本编辑软件的存档路径
  */
  char name[10][100];
  /*设置的语言*/
  int language;
  float version;
  /*默认操作,0为查找笔记操作*/
  int default_control;
} Workdirname2023927;
extern Workdirname2023927 workdirname;
extern enum _system thesystem;
#define worknamemax (51)
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

/*命令行功能*/
struct command_opention{
  int add;
  int change;
  int search;
  int backup;
  int restore;
  int help;
  int man;
  int language;
  int version;
  int rm;
  int rf;
};
extern int whitch_command(char *str, struct command_opention *thisopention);
extern int regular_name(wchar_t *str);
extern int regular_command(char *str);



/*in language.c*/

void Language_setting_interaction(void);
void Language_setting_str(const char *str);
enum p {
  english_US = 0,
  english_GB,
  chinese_CN,
  chinese_TW,
  french_FR,
  spanish_ES,
  arabic_AE,
  german_DE,
  russians_RU,
  portuguese_PT,
  Danish_DK,
  japanese_JP
};
extern void set_language(int select);

/*语言包结构体*/
struct LANGUNAGE_SUPPORT {
  wchar_t Illegal_characters[200];  // 非法字符，你只能使用合法字符，例如
  wchar_t Version[10];              // 版本
  wchar_t Invalid_command_line[200];  // 无效命令行
  wchar_t Help[2000];                 // 帮助文件
  wchar_t counld_not_find_command[200];//无当前命令参数，请使用"mytips -help"命令查看帮助文件
  wchar_t do_you_want_remove_note[80];//删除这个笔记吗?
}; /*结构体请由末尾加入新文本，进行顺序的设置*/
extern struct LANGUNAGE_SUPPORT language_pack;

/**/