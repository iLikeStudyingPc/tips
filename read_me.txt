本文件介绍工程组成部分
环境搭建：
vscode软件，用c语言，暂无使用第三方库。
你需要修改.vscode里面的配置文件的gcc,gdb,g++软件目录，然后运行生成任务时候，需要选择正确的任务
文件夹组成部分：
source：用于保存各个版本源代码;--{
  function.h:保存源代码所需大部分的头文件，定义结构体等部分。
  save.c:用于程序保存存档，设置等功能。
  language.c:用于程序选择语言，提供不同的语言支持
  rule.c:程序检测用户输入符号元素或者操作等方面是否符合规范。
  structure.c:数据结构，保存和封装数据操作的函数。
  main.c:软件入口，设置信号处理等部分。
}
software:用于保存各个版本的软件输出，其中debug文件夹里用于测试调试版本。

特别说明:
使用windows时候，有一些编码问题。

软件使用帮助:
mytips - 命令行笔记本应用

用法:
mytips [命令] [参数]

一级命令:
-a, -add <笔记名> 添加新笔记
-c, -change <笔记名> 修改指定的笔记内容
-s, -search <关键词> 搜索笔记
-rm 删除指定笔记
-rf 无需同意即删除指定笔记
-v, -version 显示程序版本信息
-h, -help 显示此帮助信息
-l,-load 从存档文件导入笔记
-save 备份全部笔记到文件
-settxt 修改软件编辑器（linux默认为nano）
-language <语言> 设置界面语言
-init 软件重新初始化

一级命令命令优先级别：version>help>settxt>rf>rm>search>change>add>load>save>language>init


-c的二级命令
-all 修改笔记全部内容
-name 只修改笔记条目的名称
-content （默认只修改笔记内容)
-c的二级命令优先级别：all>rename>content


-l的二级命令:
-new 导入笔记不经过确定，冲突时候，保存新笔记
-old 导入笔记不经过确定，冲突时候，保存旧笔记
-backup 导入笔记并且删除之前的笔记
-content 导入笔记(默认，冲突时候依次确定)

-l的二级命令优先级别 old>new>backup>content

笔记名 指定要操作的笔记的名字
关键词 搜索该关键词在笔记内容中的匹配
语言 设置界面语言,支持:english_US,english_GB,chinese_CN,chinese_TW,french_FR,spanish_ES,arabic_AE,german_DE,russians_RU,Danish_DK,....

示例:
mytips -a tar 添加名为"tar"的笔记


