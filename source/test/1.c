#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

int detection_program_exist(char *str) {
    char command[strlen(str)+40];
#ifdef _WIN32
    // Windows系统下的检测代码
    sprintf(command, "where %s > nul 2>&1", str); // 使用where命令检测程序是否存在
    if (system(command) == 0) {
        return 1;
    }
#else
    // Linux系统下的检测代码
    sprintf(command, "command -v %s >/dev/null 2>&1", str); // 使用command -v检测程序是否存在
    if (system(command) == 0) {
        return 1;
    }
#endif

    return 0;
}

int main() {
    char programName[256];
    printf("Enter the program name: ");
    scanf("%s", programName);

    if (detection_program_exist(programName)) {
        printf("The program exists!\n");
    } else {
        printf("The program does not exist!\n");
    }

    return 0;
}