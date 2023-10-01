#include "function.h"
#include <stdlib.h>
/*代表着工作保存路径*/
Workdirname2023927 workdirname;
/*一个tip内容*/
struct tipcontent{
  /*内容*/
  wchar_t mincontent[1000];
  /*功能tag*/
  wchar_t tag[51];
  /*名称*/
  wchar_t name[51];
  /*tag创建时间*/
  time_t create_time;
  /*配置语言支持(插入与显示时候安装语言支持显示，如果插入不配置语言选项则按照默认语言选项进行)*/
  int language;
};
// 定义散列表节点
struct hash_node {
  struct tipcontent content;
  struct hash_node* next;
};
// 定义散列表
struct hash_table {
  int size;
  struct hash_node** table;
};

// 初始化散列表
struct hash_table* init_hash_table(int size) {
  struct hash_table* hash = malloc(sizeof(struct hash_table));
  hash->size = size;
  hash->table = malloc(sizeof(struct hash_node*) * size);
  for (int i = 0; i < size; i++) {
    hash->table[i] = NULL;
  }
  return hash;
}

// 计算哈希值
static int hash_function(wchar_t* key, int size) {
  int hash = 0;
  for (int i = 0; key[i] != '\0'; i++) {
    hash += key[i];
  }
  return hash % size;
}

// 插入节点到散列表
void insert_node(struct hash_table* hash, struct tipcontent content) {
  int index = hash_function(content.name, hash->size);
  struct hash_node* new_node = malloc(sizeof(struct hash_node));
  new_node->content = content;
  new_node->next = NULL;

  if (hash->table[index] == NULL) {
    hash->table[index] = new_node;
  } else {
    struct hash_node* current = hash->table[index];
    while (current->next != NULL) {
      current = current->next;
    }
    current->next = new_node;
  }
}
// 列出所有具有指定标签的节点
void list_nodes_by_tag(struct hash_table* hash, wchar_t* tag) {
  for (int i = 0; i < hash->size; i++) {
    struct hash_node* current = hash->table[i];
    while (current != NULL) {
      if (wcscmp(current->content.tag, tag) == 0) {
        // 找到具有指定标签的节点，执行相应操作
        // ...
      }
      current = current->next;
    }
  }
}
// 根据名称查询节点
struct hash_node* search_node_by_name(struct hash_table* hash, wchar_t* name) {
  int index = hash_function(name, hash->size);
  struct hash_node* current = hash->table[index];
  while (current != NULL) {
    if (wcscmp(current->content.name, name) == 0) {
      return current;
    }
    current = current->next;
  }
  return NULL;
}
