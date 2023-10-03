#include "structure.h"
#include <stdio.h>
#include <stdlib.h>
#include "save.h"
#include "time.h"
static void insert_node(struct tree* curr, struct tipcontent* newtip);
static void delete_node(struct tree* delnode);
/*创建一个新节点,返回指向节点的指针，为动态内存分配，可释放*/
struct tipcontent *newtipcontent(wchar_t **mincontent, wchar_t *name,int uselanguage) {
  struct tipcontent *tip = malloc(1 * sizeof(struct tipcontent));
  tip->mincontent = mincontent;
  wcsncpy(tip->name, name, worknamemax);
  tip->language == uselanguage;
  time(&(tip->create_time));
  return tip;
}
/*树链表*/

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
  while (!feof(file)) {
    /*读取节点内容*/
    struct tipcontent *this_tip = calloc(1, sizeof(struct tipcontent));
    fread(this_tip, sizeof(struct tipcontent), 1,
          file); /*注意读取的是tipcontent结构体*/
    fread(&wchar_count, sizeof(unsigned long), 1, file);
    wchar_t *this_str = malloc(wchar_count * sizeof(wchar_t));
    fread(this_str, sizeof(wchar_t), wchar_count, file);
    this_str[wchar_count - 2] = L'\000';
    this_tip->mincontent = &this_str;
    /*指定下一个树的内容*/
    struct tree *nexttree = calloc(1, sizeof(struct tree));
    previostree->next=nexttree;
    previostree->tip=this_tip;
    nexttree->previous=previostree;
    nexttree->tip=NULL;
    nexttree->next=NULL;
    previostree=nexttree;
  }
  fclose(file);
  return root;
}
/*写入链表到文件，如果文件不存在则创建新文件并写入*/
void write_root_end(struct tree *root, char *str) {
  FILE *file = write_file(str);

  /*
  **存档结构:
  !1个  |多个-----------------------------------------------|
  !1个  | 1个--------------|1个----------------|宽字符-------|
  !float|struct tipcontent|unsigned long      |wchar_t     |
  ?版本号|内容结构体并且不是树|代表宽字符串的长度    |宽字符串的内容 |
  */
  /*第一个写入的是版本号！！！注意后期有用的*/
  fwrite(&workdirname.version, sizeof(float), 1,
         file);
  /*如果未达到链表末尾,并且链表内容不为空就继续*/
  unsigned long wchar_count;
  while (root->next != NULL&&root->tip!=NULL) {
    /*写入节点内容*/
    fwrite(root->tip,sizeof(struct tipcontent),1,file);
    wchar_count=wcslen(*(root->tip->mincontent))+1;
    fwrite(&wchar_count,sizeof(unsigned long),1,file);
    fwrite(*(root->tip->mincontent),sizeof(wchar_t),wchar_count,file);
  }
  fclose(file);
  return;
}
// 链表插入函数,会插入内容到需要插入的节点之前
static void insert_node(struct tree* curr, struct tipcontent* newtip) {
  struct tree* newnode = malloc(sizeof(struct tree));
  /*新建链表内容是当前节点*/
  newnode->previous=curr;
  newnode->tip=curr->tip;
  newnode->next=curr->next;
  /*旧的节点内容被替换成新节点内容*/
  curr->next = newnode;
  curr->tip=newtip;
}
// 链表删除函数,删除指定节点内容
static void delete_node(struct tree* delnode){
  /*上一个节点不为空*/
  if(delnode->previous!=NULL){
    delnode->previous->next=delnode->next;
  }
  /*下个节点不为空*/
  if(delnode->next!=NULL){
    delnode->next->previous=delnode->previous;
  }
  // 释放内存
  free(delnode->tip);
  free(delnode);
}
int remove_node(wchar_t *str,struct tree root){
  ;
}