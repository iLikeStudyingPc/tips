#include "function.h"
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
/*用于初始化文件仓库*/
static void return_fileplace(void) {
#ifdef __WIN32
  TCHAR docPath[MAX_PATH];
  if (SUCCEEDED(SHGetFolderPath(NULL, CSIDL_PERSONAL, NULL, 0, docPath))) {
    // 处理获取到的文档目录路径
    strcpy(workdirname.name[0], docPath);
    char *str = NULL;
    while ((str = strchr(workdirname.name[0], '\\')) != NULL) *str = '/';
  } else {
    wprintf(L"错误:无法找到文档路径\n");
    exit(EXIT_FAILURE);
  }
  strcat(workdirname.name[0], "/mytips/");
  if (GetFileAttributesA(workdirname.name[0]) == INVALID_FILE_ATTRIBUTES) {
    // 文件夹不存在，创建文件夹
    if (!CreateDirectoryA(workdirname.name[0], NULL)) {
      wprintf(L"初始化错误:无法创建文件夹\n");
      exit(EXIT_FAILURE);
    }
  }
#elif __linux__
  char *xdg_docs = getenv("XDG_DOCUMENTS_DIR");
  if (xdg_docs) {
    strcpy(workdirname.name[0], xdg_docs);
  } else {
    strcpy(workdirname.name[0], getenv("HOME"));
    strcat(workdirname.name[0], "/Documents");
  }
  // 拼接具体文件名
  strcat(workdirname.name[0], "/mytips/");
  // 检测文件夹是否存在
  struct stat st;
  if (stat(workdirname.name[0], &st) == -1) {
    // 文件夹不存在，创建文件夹
    if (!mkdir(workdirname.name[0], 0777) == 0) {
      wprintf(L"初始化错误:无法创建文件夹\n");
      exit(EXIT_FAILURE);
    }
  }
#endif
}
/*软件开启准备活动,寻找软件存档的目录*/
extern char* Initialize(void) {
  return_fileplace();
  char *workspace=malloc(100*sizeof(char));
  *(workspace+0)='\0';
  strcat(strcpy(workspace,workdirname.name[0]),"path.data");
  FILE *thespace=fopen(workspace,"r+");
  if(thespace==NULL){
    /*
    **告知软件tips基本结构体存档路径,并创建
    */
    {
      strcat(strcpy(workspace,workdirname.name[0]),"mytips.data");
      thespace=fopen(workspace,"w");
      fclose(thespace);
    }
    /*
    **创建初始化存档目录
    */
    strcat(strcpy(workspace,workdirname.name[0]),"path.data");
    thespace=fopen(workspace,"w");
    strcpy(workdirname.name[9],"version 1.0");
    fwrite(&workdirname,sizeof(Workdirname2023927),1,thespace);
  }else{
    fread(&workdirname,sizeof(Workdirname2023927),1,thespace);
  }
  free(workspace);
  fclose(thespace);
  return workdirname.name[0];
}