#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "structure.h"
#include "save.h"
#define ___DEBUGOPEN 0
/*
**命令行非控制文本
*/
struct command_str {
  struct command_str *next;
  char *str;
};
static struct command_str root = {NULL, NULL};  // 创建根指针
static void clear_command_str(struct command_str *this);
static int string_all_digits(char *str);
Workdirname2023927 workdirname;
/*
设置程序的退出
*/
void exitnow(void) {
  save_optons();
  if (root.next != NULL) {
    clear_command_str(root.next);
  }
  return;
}

/*
主程序
*/
int main(int argc, char **argv) {
  if(Initialize()==NULL){
    char p[strlen(*argv)+16];
    Language_setting_interaction();
    return(EXIT_SUCCESS);
  };
  make_the_dir(workdirname.name[2]);
  set_language(workdirname.language);
  if(workdirname.version<VERSION){
    wprintf(L"%ls\n",language_pack.Version_update_operation_in_progress);
    workdirname.version=VERSION;
  }
  if (thesystem == WINDOWS) {
    system("chcp 65001&&cls");
  }
  if (argc == 1) {
    wprintf(L"%ls\n", language_pack.Help);
    exit(EXIT_SUCCESS);
  }
  struct command_opention thisopen = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  /*
  !在自检操作之前并未设置退出操作
  */
  atexit(exitnow);

  /*
  **初始化noderoot节点树
  */
  struct tree *noderoot=rootstart(workdirname.name[1]);

  int count_command = 0;
  int count_str = 0;
  for (char **p = argv; *++p != NULL;) {
    if (regular_command(*p) == 0) { /*非法命令就退出*/
      wprintf(L"%ls%ls\n", language_pack.Illegal_characters,
              L"@#+_-=,./:"); /*非法字符，你只能使用合法字符，例如:@#+_-=,./:*/
      return EXIT_FAILURE;
    } else if (**p == '-') {
      count_command += 1;
      /*wprintf(L"found \'-\'\n");调试*/
      if (whitch_command(*p, &thisopen) == 0) {
        if (thesystem == WINDOWS) {
          printf("%s", *p);
          wprintf(L":%ls\n", language_pack.counld_not_find_command);
        } else if (thesystem == LINUX) {
          wprintf(L"%s:%ls\n", *p, language_pack.counld_not_find_command);
        }
        exit(EXIT_FAILURE);
      }
    } else {
      count_str += 1;
      struct command_str *this_str = malloc(1 * sizeof(struct command_str));
      this_str->str = *p;
      this_str->next = NULL;
      for (struct command_str *befor = &root;; befor = befor->next) {
        if (befor->next == NULL) {
          befor->next = this_str;
          break;
        }
      }
      /*root是字符串寄存器，存储命令参数*/
    }
  }
  if (count_command == 0) {
#if ___DEBUGOPEN
    wprintf(L"goto command_default\n");
#endif
    switch (workdirname.default_control) {
      case 0:
        goto gotosearch;
        break;
      default:;
        break;
    }
  }
  if (thisopen.version == 1) {
    wprintf(L"%ls %.3f\n", language_pack.Version, workdirname.version);
  } else if (thisopen.help == 1) {
    wprintf(L"%ls\n", language_pack.Help);
  } else if (thisopen.rf == 1) { /*删除笔记*/
    for (struct command_str *p = &root; (p = p->next) != NULL;) {
      wchar_t str[worknamemax];
      mbstowcs(str, p->str,sizeof(str));
      int ch=tree_remove_node(noderoot,str);
      switch(ch){
        case 1:wprintf(L"%ls:%s\n",language_pack.Complete_the_deletion_operation,p->str);break;
        case 0:wprintf(L"%ls:%s\n",language_pack.Entry_not_found,p->str);break;
      }
      /*add(p->str)*/
    }
    if(!write_root_end(noderoot,workdirname.name[1])){
      wprintf(L"%ls\n",language_pack.Archive_failed);
    }
  } else if (thisopen.rm == 1) { /*询问是否删除笔记*/
    for (struct command_str *p = &root; (p = p->next) != NULL;) {
      if(thesystem==WINDOWS){
        wprintf(L"%ls",language_pack.do_you_want_remove_note);
        printf("%s  <y,n>\n",p->str);
      }else if(thesystem==LINUX){
        wprintf(L"%ls %s  <y,n>\n",language_pack.do_you_want_remove_note,p->str);
      }
      fflush(stdout);
      int ch = 0;
      while ((ch = getch()) != '\r' && ch != 'y' && ch != 'n' && ch != 'Y' &&
             ch != 'N')
        ;
      if (ch == 'Y' || ch == 'y') {
        char str[100] = "";
        sprintf(str, "%s -rf %s", *argv, p->str);
        if (thesystem == LINUX) {
          wprintf(L"执行:%s\n", str);
        } else if (thesystem == WINDOWS) {
          wprintf(L"执行:", str);
          printf("%s\n", str);
        }
        fflush(stdout);
        system(str);
      }else{
        wprintf(L"拒绝删除\n");
      }
    }
  } else if (thisopen.search == 1) { /*搜索笔记*/
  gotosearch:
    for (struct command_str *p = &root; (p = p->next) != NULL;) {
      wchar_t str[worknamemax];
      mbstowcs(str, p->str,sizeof(str));
      struct tree *thistree=treesearch(noderoot,str);
      if(thistree!=NULL&&thistree->tip!=NULL){
        wprintf(L"%ls:%ls\n",language_pack.Found_Entry,str);
        int a=workdirname.language;
        if(a!=thistree->tip->language){
          set_language(thistree->tip->language);
          wprintf(L"%ls\n",(thistree->tip->mincontent));
          fflush(stdout);
          set_language(a);
        }else{
          wprintf(L"%ls\n",(thistree->tip->mincontent));
          fflush(stdout);
        }
      }else{
        wprintf(L"%ls:%ls\n",language_pack.Entry_not_found,str);
      }
    }
  } else if (thisopen.change == 1) { /*修改笔记，如果笔记不存在则添加笔记*/
    wprintf(L"%ls %d:\n",language_pack.Modifying_Note_Entries,count_str);
    for (struct command_str *p = &root; (p = p->next) != NULL;) {
      wchar_t str[worknamemax];
      mbstowcs(str, p->str, sizeof(str));
      int ch=treechange(noderoot,str);
      if(ch==1){
        wprintf(L"%ls:%ls\n",language_pack.complete,str);
      }else if(ch==0){
        wprintf(L"%ls:%ls\n",language_pack.Entry_not_found,str);
      }else if(ch==-1){
        wprintf(L"%ls:%ls\n",language_pack.Empty_text_error,str);
      }
      
      /*add(p->str)*/
    }
  } else if (thisopen.add == 1) { /*添加笔记*/
    wprintf(L"%ls:%d:\n",language_pack.add_note,count_str);
    for (struct command_str *p = &root; (p = p->next) != NULL;) {
      wchar_t str[worknamemax];
      mbstowcs(str, p->str, sizeof(str));
      int ch=treeadd(noderoot,str);
      if(ch==1){
        wprintf(L"%ls:%ls\n",language_pack.complete,str);
      }else if(ch==0){
        wprintf(L"%ls:%ls\n",language_pack.Entry_already_exists,str);
      }else if(ch==-1){
        wprintf(L"%ls:%ls\n",language_pack.Empty_text_error,str);
      }
      /*add(p->str)*/
    }
    if(!write_root_end(noderoot,workdirname.name[1])){
      wprintf(L"%ls\n",language_pack.Archive_failed);
    }
  } else if (thisopen.restore == 1) { /*备份*/
    ;
  } else if (thisopen.backup == 1) { /*恢复*/
    ;
  } else if (thisopen.language == 1) { /*语言设定*/
    if ((root.next) != NULL) {
      if (string_all_digits(root.next->str)) {
        set_language(atoi(root.next->str));
      } else {
        Language_setting_str(root.next->next->str);
      }
    } else {
      Language_setting_interaction();
    };
  } else if (thisopen.man == 1) { /*man手册翻译选项*/
    ;
  }
  /*debug show tree*/
#if ___DEBUGOPEN
  wprintf(L"\n-------------------------------------\n以下是调试消息:\n");
  int debug=0;
  while(noderoot->tip!=NULL){
    if(noderoot->tip!=NULL){
      wprintf(L"%d name:%ls\nmincontent:\n",++debug,noderoot->tip->name);
      int a=workdirname.language;
        if(a!=noderoot->tip->language){
          set_language(noderoot->tip->language);
          wprintf(L"%ls\n",(noderoot->tip->mincontent));
          fflush(stdout);
          set_language(a);
        }else{
          wprintf(L"%ls\n",(noderoot->tip->mincontent));
          fflush(stdout);
        }
    }
    noderoot=noderoot->next;
  }
  free(noderoot);
  /*wprintf(L"\nadd:%d "
  L"backup:%d "
  L"search:%d "
  L"search:%d "
  L"language:%d\n",thisopen.add,thisopen.backup,thisopen.search,thisopen.man,thisopen.language);
  */
#endif
  return EXIT_SUCCESS;
}
/*用于清空非命令的字符串内存*/
static void clear_command_str(struct command_str *this) {
  if (this->next != NULL) {
    clear_command_str(this->next);
  }
  free(this);
}

/*检查字符串是不是都是数字,是返回1否则0*/
static int string_all_digits(char *str) {
  do {
    if (!isdigit(*str)) {
      return 0;
    }
  } while (*++str != '\0');
  return 1;
}
/*
  wchar_t str[50] = L"";
  for (int i = 1; i < argc; i++) {
    //将多字符转化为宽字符
{
  *argv++;
  mbstowcs(str, *argv, sizeof(str));
}
if (!regular_name(str)) return EXIT_FAILURE;
}
*/

/*
今日任务
1,创建-内容识别器，能够识别命令行，选取功能。默认功能在设置结构体设置，无-识别时候，进行默认功能，默认功能是搜索笔记
2,创建各个语言的报错功能，能够通过设置语种切换报错消息。(切换语言，要使用getch进行)
3，创建结构体字符串，收录笔记内容。
*/