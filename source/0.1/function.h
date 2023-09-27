#include "stdio.h"
#include "time.h"
#include "stdlib.h"
#include "string.h"
#include "unistd.h"
#include "ctype.h"
enum _system{WINDOWS=10,LINUX,ERROR=255};
#ifdef _WIN32
/*windows数据支持*/
#include "shlobj.h"
#include "windows.h"
#include "conio.h"
enum _system thesystem=WINDOWS;
#elif __linux__
/*linux数据支持*/
enum _system thesystem=LINUX;
#include <sys/stat.h>
#include <sys/types.h>
/*linux对于windows getch的模拟*/
char getch(void){
    system("stty -icanon");
    system("stty -echo");//linux内部,我们用 `system("stty -icanon");` 关闭缓冲区 `system("stty -echo");` 关闭终端回显示
		char b=getchar();
		if(b==27){
			if((b=getchar())==91){
				b=getchar();
				switch(b){
							case 65:b=72;break;//上
							case 66:b=80;break;//下
							case 68:b=75;break;//左
							case 67:b=77;break;//右
				}
			}
		}//上下左右键适配
    if(b=='\n') b='\r';
    system("stty icanon");//linux内部，我们用 `system("stty icanon");`开启缓冲区 `system("stty echo");` 开启终端回显示
    system("stty echo");
    return b;
}
#elif
/*错误系统支持*/
enum _system thesystem=ERROR;
#endif
/*代表着工作保存路径*/
typedef struct Workdirname2023{
  /*
  !workdirname.name[0]:公共路径
  */
  char name[10][100];
}Workdirname2023927;