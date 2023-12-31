#include <wchar.h>
#define VERSION 1.001
/*代表着工作保存路径*/
typedef struct Workdirname2023 {
  /*
  !workdirname.name[0]:公共路径,公共路径里包含文件setting.data，存储其他软件的存档路径
  !workdirname.name[1]:软件tips基本结构体存档路径
  !workdirname.name[2]:文本编辑软件的存档路径
  !workdirname.name[3]:文本编辑软件命令行
  !workdirname.name[4]:软件save命令导出路径（注意读取是从导出路径读取的）
  */
  char name[10][100];
  /*设置的语言*/
  int language;
  float version;
  /*默认操作,0为查找笔记操作*/
  int default_control;
} Workdirname2023927;
extern Workdirname2023927 workdirname;
#define worknamemax (51)
/*in system.c*/
#include <sys/stat.h>
#include <sys/types.h>
extern char getch(void);

/*in rule.c*/
struct command_opention{
  int add;
  int change;
  int search;
  int save;
  int load;
  int help;
  int language;
  int version;
  int rm;
  int rf;
  int settxt;
  int all;
  int name;
  int content;
  int new;
  int old;
  int backup;
  int init;
};
extern int detection_program_exist(char *str);
extern int whitch_command(char *str, struct command_opention *thisopention);
extern int regular_name(wchar_t *str);
extern int regular_command(char *str);
extern int set_txt_program(void);




/*in language.c*/

/*添加语言时候记得修改这里的字符串列表*/
#define Count_language (12)

void Language_setting_interaction(void);
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
  wchar_t Help[4000];                 // 帮助文件
  wchar_t counld_not_find_command[200];//无当前命令参数，请使用"mytips -help"命令查看帮助文件
  wchar_t do_you_want_remove_note[80];//删除这个笔记吗?
  wchar_t Version_update_operation_in_progress[80];//正在进行版本更新操作
  wchar_t Complete_the_deletion_operation[100];//完成删除操作
  wchar_t Entry_not_found[70];//找不到条目
  wchar_t Archive_failed[70];//存档失败
  wchar_t Found_Entry[70];//找到条目
  wchar_t Modifying_Note_Entries[70];//修改笔记条目
  wchar_t complete[50];//完成
  wchar_t Empty_text_error[80];//空文本错误
  wchar_t add_note[80];//添加笔记条目
  wchar_t Entry_already_exists[80];//条目已存在
  wchar_t Please_enter_a_new_text_editor_name[80];
  wchar_t Text_editor_name_modified_successfully[80];
  wchar_t Text_editor_name_modification_failed[80];
  wchar_t please_enter_a_new_note_name[100];//请输入新的笔记名称
  wchar_t Naming_conflict_existing_note_already_exists[100];//命名冲突，现有笔记已经存在
  wchar_t save[80];//存档
  wchar_t Please_select_an_archive_to_load[100];//请选择存档进行加载
  wchar_t The_folder_is_empty_or_does_not_exist[100];//文件夹为空或者文件夹不存在
  wchar_t Archive_replacement_completed[200];//进行存档替换完成
  wchar_t are_you_sure_replace[150];//你确定要替换吗？
  wchar_t Your_note_name_cannot_start_with_the_symbol[120];//你的笔记命名不能以-符号开头
  //修改条目
}; /*结构体请由末尾加入新文本，进行顺序的设置*/
extern struct LANGUNAGE_SUPPORT language_pack;

/**/