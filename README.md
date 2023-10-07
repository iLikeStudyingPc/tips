This document introduces the components of the project

Environmental construction:

VScode software, using C language, currently does not use third-party libraries.

You need to modify the gcc, gdb, and g++software directories of the configuration files in. vscode, and then select the correct task when running the generate task

Folder components:

Source: used to save the source code of each version-- {

Function. h: Save most of the header files required for the source code, define structures, and other parts.

Save. c: Used for program saving, archiving, setting, and other functions.

Language. c: Used for program language selection, providing different language support

Language. h: Help file for providing programs

Rule. c: The program detects whether user input symbol elements or operations comply with the specifications.

Structure. c: Data structure, functions for saving and encapsulating data operations.

Structure. h: header file for data structure

Main. c: Software entry, setting signal processing and other parts.

System. c: Cross platform functions used by some programs

}


Software: Used to save software output for each version, with the debug folder used for testing and debugging versions.

Special instructions:

When using Windows, there are some encoding issues. There is currently no solution, and the software needs to be moved to the system bin folder for operation. This is the most convenient way

Software Usage Help: 
 tips - command line notebook application

Usage:
 tips [command] [parameter]

First level commands:

-a, -add <note name> add new notes

-c, -change <note name> modify the specified note content

-s, -search <keyword> search notes

-rm delete specified note

-rf delete specified note without confirmation

-v, -version display program version info

-h, -help display this help info

-l,-load import notes from archive file

-save backup all notes to file

-settxt modify software editor (nano by default on linux)

-language <language> set interface language

-init reinitialize the software

First level command priority: version>help>settxt>rf>rm>search>change>add>load>save>language>init


-c secondary commands:

-all modify entire note content

-name only modify note entry name

-content (default only modify note content)

-c secondary command priority: all>rename>content



-l secondary commands:
-n -new import notes without confirmation, keep new notes if conflict

-o -old import notes without confirmation, keep old notes if conflict

-b -backup import notes and delete existing ones

-content import notes (default, confirm each if conflict)

-l secondary command priority: old>new>backup>content

Note name specify note to operate on

Keyword search keyword match in note content

Language set interface language, supports: english_US, english_GB, chinese_CN, chinese_TW, french_FR, spanish_ES, arabic_AE, german_DE, russian_RU, danish_DK,....

Examples:

 tips -a tar add a note named "tar"

 tips -save save notes

 tips -change -new import notes discarding old versions

Please execute after downloading the software ontology(Pay attention to replacing the path of tips in the command with the path in your computer):

    for linux:

    ```shell

      sudo mv /path/to/tips /bin/

      sudo chmod 777 /bin/tips

      tips
      
    ```