#include "structure.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "save.h"
#include "time.h"
static void insert_node(struct tree *curr, struct tipcontent *newtip);
static void delete_node(struct tree *delnode);
static wchar_t *new_wchar_text(wchar_t *__oldstr, int __language,
                               char *filename);
/*创建一个新节点,返回指向节点的指针，为动态内存分配，可释放*/
struct tipcontent *newtipcontent(wchar_t **mincontent, wchar_t *name,
                                 int uselanguage) {
  struct tipcontent *tip = malloc(1 * sizeof(struct tipcontent));
  tip->mincontent = *mincontent;
  wcsncpy(tip->name, name, worknamemax);
  tip->language == uselanguage;
  time(&(tip->create_time));
  return tip;
}

/*读取文件链表并返回根指针，如果文件链表不存在就创建链表并初始化根指针,无法创建返回NULL*/
struct tree *rootstart(char *str) {
  struct tree *root = calloc(1, sizeof(struct tree));
  FILE *file = read_file(str);
  if (file == NULL) { /*没有这个文件就初始化根指针*/
    file = write_file(str);
    if (file == NULL) {
      wprintf(L"无法创建此文件%s", workdirname.name[1]);
      fflush(stdout);
      return NULL;
    }
    fclose(file);
    file = read_file(str);
  }
  /*
  **存档结构:
  !1个  |多个-----------------------------------------------|
  !1个  | 1个--------------|1个----------------|宽字符-------|
  !float|struct tipcontent|unsigned long      |wchar_t     |
  ?版本号|内容结构体并且不是树|代表宽字符串的长度    |宽字符串的内容 |
  */
  float version;
  unsigned long wchar_count;
  /*一开始的上一个指针*/
  struct tree *previostree = root;
  fread(&version, sizeof(float), 1,
        file); /*第一个读取的是代表存档的版本号！！！注意后期有用的*/
  /*如果未达文件末尾*/
  while (1) {
    if (feof(file)) {
      fclose(file);
      break;
    }
    /*读取节点内容的笔记*/
    struct tipcontent *this_tip = calloc(1, sizeof(struct tipcontent));
    fread(this_tip, sizeof(struct tipcontent), 1, file);
    /*注意读取的是tipcontent结构体*/
    fread(&wchar_count, sizeof(unsigned long), 1, file);
    wchar_t *this_str = malloc((wchar_count + 1) * sizeof(wchar_t));
    /*字符串*/
    fread(this_str, sizeof(wchar_t), wchar_count, file);
    this_tip->mincontent = this_str;
    /*写入节点内容到内存树*/
    previostree->tip = this_tip;
    struct tree *nexttree = calloc(1, sizeof(struct tree));
    previostree->next = nexttree;
    nexttree->previous = previostree;
    nexttree->next = NULL;
    previostree = previostree->next;
    previostree->tip = NULL;
  }
  return root;
}
/*写入链表到文件，如果文件不存在则创建新文件并写入*/
int write_root_end(struct tree *root, char *str) {
  FILE *file = write_file(str);
  /*
  **存档结构:
  !1个  |多个-----------------------------------------------|
  !1个  | 1个--------------|1个----------------|宽字符-------|
  !float|struct tipcontent|unsigned long      |wchar_t     |
  ?版本号|内容结构体并且不是树|代表宽字符串的长度    |宽字符串的内容 |
  */
  /*第一个写入的是版本号！！！注意后期的更新是有用的*/
  fwrite(&workdirname.version, sizeof(float), 1, file);
  /*如果未达到链表末尾,并且链表内容不为空就继续*/
  unsigned long *wchar_count = malloc(1 * sizeof(unsigned long));
  while (root->next != NULL && root->tip != NULL &&
         *(root->tip->name) != L'\000') {
    /*写入节点内容*/
    fwrite(root->tip, sizeof(struct tipcontent), 1, file);
    *wchar_count = wcslen((root->tip->mincontent) /*内容*/);
    fwrite(wchar_count, sizeof(unsigned long), 1, file);
    fwrite((root->tip->mincontent), sizeof(wchar_t), *wchar_count, file);
    root = root->next;
  }
  free(wchar_count);
  fclose(file);
  return 1;
}
// 链表插入函数,会插入内容到需要插入的节点之前
static void insert_node(struct tree *curr, struct tipcontent *newtip) {
  struct tipcontent *oldtip = curr->tip;
  curr->tip = newtip;
  struct tree *newnode = malloc(sizeof(struct tree));
  newnode->previous = curr;
  newnode->next = curr->next;
  newnode->tip = oldtip;
  curr->next = newnode;
  return;
}
// 链表删除函数,删除指定节点内容
static void delete_node(struct tree *delnode) {
  /*上一个节点不为空*/
  free(delnode->tip->mincontent);
  free(delnode->tip);
  if (delnode->previous != NULL) {
    delnode->previous->next = delnode->next;
  } else if (delnode->next !=
             NULL) { /*根节点并且下个节点不为空时候当心，不可以清理根节点*/
    struct tree *p = delnode->next;
    delnode->tip = p->tip;
    delnode->next = p->next;
    free(p);
    return;
  } else {
    return;
  }
  /*下个节点不为空*/
  if (delnode->next != NULL) {
    delnode->next->previous = delnode->previous;
  }
  // 释放内存
  free(delnode);
}
/*这是删除树中节点的函数，返回1删除成功，返回0找不到删除失败*/
int tree_remove_node(struct tree *root, wchar_t *str) {
  struct tree *curr = treesearch(root, str);
  if (curr != NULL) {
    delete_node(curr);
    return 1;
  } else {
    return 0;
  }
}
/*添加树，正确返回1，文本为空错误返回-1，已经存在笔记返回0*/
int treeadd(struct tree *root, wchar_t *str) {
  struct tree *curr = treesearch(root, str);
  char __filename[wcslen(str) + 10];
  wcstombs(__filename, str, sizeof(__filename));
  strcat(__filename, ".txt");
  if (curr == NULL) { /*如果搜到为空则添加*/
    wchar_t *new_text = new_wchar_text(NULL, workdirname.language, __filename);
    if (new_text == NULL || new_text[0] == L'\0') {
      /*文本为空不添加*/
      return -1;
    }
    // wprintf(L"新树即将写入：\n%ls\n",new_text);
    struct tipcontent *thenew =
        newtipcontent(&new_text, str, workdirname.language);
    // wprintf(L"新树内存写入：\n%ls\n",*(thenew->mincontent));
    insert_node(root, thenew);
    return 1;
  } else {
    return 0;
  }
}
/*编辑树的名字，树存在并编辑成功返回1，文本为空错误不修改返回-1,发现了旧的笔记名字冲突返回-2，如果名字不符合规范返回-3,笔记不存在返回0*/
int treenamechange(struct tree *root, wchar_t *str, int mod) {
  struct tree *curr = treesearch(root, str);
  if (curr != NULL) { /*如果搜到不为空则编辑笔记名称*/
    wchar_t newname[worknamemax];
    wprintf(L"%ls:%ls", str, language_pack.please_enter_a_new_note_name);
    fgetws(newname, worknamemax, stdin);
    int wclen = wcslen(newname);
    if (wclen <= 1) {
      return -1;
    }
    newname[wclen - 1] = L'\0';
    /*如果符号不符合规范则错误提示*/
    if (regular_name(newname) == 0) {
      wprintf(L"%ls%ls\n", language_pack.Illegal_characters, L"@#+_-=,.:");
      return -3;
    }
    /*如果发现了旧的笔记名字冲突*/
    if (treesearch(root, newname) != NULL) {
      wprintf(L"%ls\n",
              language_pack.Naming_conflict_existing_note_already_exists);
      return -2;
    }
    wcscpy(curr->tip->name, newname);
    if (mod == 1) {
      int ch = treechange(curr, newname);
      if (ch == -1) {
        wprintf(L"%ls:%ls\n", language_pack.Empty_text_error, newname);
      }
    }
    return 1;
  } else {
    return 0;
  }
}
/*编辑树，树存在并编辑成功返回1，文本为空错误不修改返回-1，笔记不存在返回0*/
int treechange(struct tree *root, wchar_t *str) {
  struct tree *curr = treesearch(root, str);
  char __filename[wcslen(str) + 10];
  wcstombs(__filename, str, sizeof(__filename));
  strcat(__filename, ".txt");
  if (curr != NULL) { /*如果搜到不为空则编辑*/
    wchar_t *new_text =
        new_wchar_text(curr->tip->mincontent, curr->tip->language, __filename);
    if (new_text == NULL || new_text[0] == L'\0') {
      /*文本为空不修改*/
      return -1;
    }
    free(curr->tip->mincontent);
    curr->tip->mincontent = new_text;
    return 1;
  } else {
    return 0;
  }
}
/*在指定树按顺序寻找名称为name的树，最后返回这个树,不存在则返回NULL*/
struct tree *treesearch(struct tree *root, wchar_t *name) {
  while (root->tip != NULL) {
    if (wcscmp(root->tip->name, name) == 0) {
      return root;
    }
    root = root->next;
  }
  return NULL;
}
/*返回新的文本,__language代表编辑语言，如果文本为空返回NULL*/
static wchar_t *new_wchar_text(wchar_t *__oldstr, int __language,
                               char *filename) {
  /*
  **告诉text文件位置
  */
  int a = workdirname.language;
  if (a != __language) {
    set_language(__language);
  }
  char *fileplace = malloc(
      (strlen(workdirname.name[2]) + strlen(filename) + 10) * sizeof(char));
  strcat(strcpy(fileplace, workdirname.name[2]), filename);
  FILE *textfile = NULL;

  /*
  !!交给其他软件修改newtext.text
  */
  textfile = fopen(fileplace, "w");
  if (__oldstr != NULL) {
    fwprintf(textfile, L"%ls", __oldstr);
  }
  fclose(textfile);
  {
    char command_line[strlen(fileplace) + 20];
    sprintf(command_line, "%s ", workdirname.name[3]);
    strcat(command_line, fileplace);
    system(command_line);
  }
  /*
  **读取newtext.text
  */
  static int max = 10;
  wchar_t *new_text = malloc(max * sizeof(wchar_t));
  unsigned int wch;
  unsigned count_wc = 0;
  unsigned count_max = max;
  textfile = fopen(fileplace, "r");
  if (textfile == NULL) { /*非法访问不存在的文件（写入为空）*/
    free(new_text);
    return NULL;
  }
  while ((wch = getwc(textfile)) != WEOF) {
    new_text[count_wc] = wch;
    count_wc += 1;
    if (count_wc == count_max - 2) {
      count_max += max;
      new_text = realloc(new_text, count_max * sizeof(wchar_t));
      if (new_text == NULL) {
        wprintf(L"Failed to load text file, computer out of memory");
        exit(EXIT_FAILURE);
      }
    }
  }
  new_text[count_wc] = L'\0';
  fclose(textfile);
  /*
  **删除newtext.text文件
  */
  remove(fileplace);
  fflush(stdin);
  free(fileplace);
  if (a != __language) {
    set_language(a);
  }
  /*wprintf(L"准备写入:\n%ls",new_text);*/
  return new_text;
}

/*-load命令，剪贴树，把loadtree树中内容导入到root里面，如果遇到条目名称一样时候，
若mod==1时，则复制loadtree内容，
如果mod==0则遇见重复时候询问，
如果mod==-1的话就保留*/
int treeload(struct tree *root, struct tree *loadtree, int mod) {
  while(loadtree!=NULL&&loadtree->tip!=NULL){
  if (loadtree->tip->name[0] != L'\0' &&
      loadtree->tip->mincontent[0] != L'\0') {
    struct tree *curr = treesearch(root, loadtree->tip->name);
    /*原来的树找不到新内容就插入*/
    if (curr == NULL) {
      insert_node(root,loadtree->tip);
    } else if (mod == 1) /*复制新内容*/ {
      if(wcscmp(curr->tip->mincontent,loadtree->tip->mincontent)==0){
        loadtree=loadtree->next;
        continue;
      }
      new : curr->tip = loadtree->tip;
    } else if (mod == -1) {
      ;
    } else if (mod == 0) {
      int a = workdirname.language;
      #ifdef __WIN32
      system("cls");
      #elif __linux__
      system("clear");
      #endif
      wprintf(L"%ls<y,n>\n",language_pack.are_you_sure_replace);
      if(wcscmp(curr->tip->mincontent,loadtree->tip->mincontent)==0){
        loadtree=loadtree->next;
        continue;
      }
      if (a != curr->tip->language) {
        set_language(curr->tip->language);
        wprintf(L"old:\n%ls:%ls\n", curr->tip->name, (curr->tip->mincontent));
        fflush(stdout);
        set_language(a);
      } else {
        wprintf(L"old:\n%ls:%ls\n", curr->tip->name, (curr->tip->mincontent));
        fflush(stdout);
      }
      if (a != loadtree->tip->language) {
        set_language(loadtree->tip->language);
        wprintf(L"new:\n%ls:%ls\n", loadtree->tip->name,
                (loadtree->tip->mincontent));
        fflush(stdout);
        set_language(a);
      } else {
        wprintf(L"new:\n%ls:%ls\n", loadtree->tip->name,
                (loadtree->tip->mincontent));
        fflush(stdout);
      }
      wprintf(L"%ls<y,n>\n",language_pack.are_you_sure_replace);
      int ch = getch();
      if (ch =='y'||ch=='Y') {
        goto new;
      }
    }
  }
  loadtree=loadtree->next;
  }
}
