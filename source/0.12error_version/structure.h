#include "function.h"
struct tipcontent{
  /*内容,注意是宽字符指针的指针，读取时候要谨慎*/
  wchar_t *mincontent;
  /*名称*/
  wchar_t name[worknamemax];
  /*笔记创建时间*/
  time_t create_time;
  /*笔记所使用语言*/
  int language;
};
/*tipcontent节点树*/
struct tree{
  struct tree *previous;
  struct tree *next;
  struct tipcontent *tip;
};
struct tipcontent *newtipcontent(wchar_t **mincontent,wchar_t *name,int uselanguage);
struct tree *rootstart(char *str);
int treeadd(struct tree *root,wchar_t *str);
struct tree *treesearch(struct tree *root,wchar_t *name);
int write_root_end(struct tree *root, char *str);
int treechange(struct tree *root,wchar_t *str);
int tree_remove_node(struct tree *root,wchar_t *str);