#include <locale.h>
#include "function.h"

static void language_group_set(int select);
/*设置语言支持*/
void set_language(int select){
  workdirname.language=select;
  switch(select){
    case english_US:setlocale(LC_ALL, "en_US.utf8");language_group_set(select);break;/*美国英语*/
    case english_GB:setlocale(LC_ALL, "en_GB.utf8");language_group_set(select);break;/*英国英语*/
    case chinese_CN:setlocale(LC_ALL,"zh_CN.utf8");language_group_set(select);break;/*简体中文*/
    case chinese_TW:setlocale(LC_ALL,"zh_TW.utf8");language_group_set(select);break;/*繁体中文*/
    case french_FR:setlocale(LC_ALL,"fr_FR.utf8");language_group_set(select);break;/*法语*/
    case spanish_ES:setlocale(LC_ALL,"es_ES.utf8");language_group_set(select);break;/*西班牙语*/
    case arabic_AE:setlocale(LC_ALL,"ar_AE.utf8");language_group_set(select);break;/*阿拉伯语(阿联酋)*/
    case german_DE:setlocale(LC_ALL,"de_DE.utf8");language_group_set(select);break;/*德语*/
    case russians_RU:setlocale(LC_ALL,"ru_RU.utf8");language_group_set(select);break;/*俄语*/
    case Danish_DK:setlocale(LC_ALL,"da_DK.utf8");language_group_set(select);break;/*丹麦语*/
    case portuguese_PT:setlocale(LC_ALL,"pt_PT.utf8");language_group_set(select);break;/*葡萄牙语*/
    default:setlocale(LC_ALL,NULL);language_group_set(english_US);break;
  }
}
/*设置语言集显示内容*/
static void language_group_set(int select){
  /*未编写区域，将会在之后支持*/
  return;
}