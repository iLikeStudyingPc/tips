extern char *Initialize(int mod);
void save_optons(void);
FILE *write_file(char *filename);
FILE *read_file(char *filename);
int make_the_dir(char *string);
int is_directory(const char *path);
char **get_files(const char *directory);
char *_chosefile(char *str);
