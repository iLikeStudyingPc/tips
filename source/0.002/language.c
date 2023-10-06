#include "language.h"

#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "function.h"

struct LANGUNAGE_SUPPORT language_pack;
static void language_group_set(int select);
void Language_setting_interaction(void);

static char c_language[Count_language][(18)] = {
    "english_US\0",  // 0
    "english_GB\0",    "chinese_CN\0", "chinese_TW\0", "french_FR\0",
    "spanish_ES\0",    "arabic_AE\0",  "german_DE\0",  "russians_RU\0",
    "portuguese_PT\0", "Danish_DK\0",  "japanese_JP\0"};

/*设置语言支持*/
void set_language(int select) {
  workdirname.language = select;
  switch (select) {
#ifdef _WIN32
    case english_US:
      setlocale(LC_ALL, "en_US.utf8");
      language_group_set(select);
      break; /*美国英语*/
    case english_GB:
      setlocale(LC_ALL, "en_GB.utf8");
      language_group_set(select);
      break; /*英国英语*/
    case chinese_CN:
      setlocale(LC_ALL, "zh_CN.utf8");
      language_group_set(select);
      break; /*简体中文*/
    case chinese_TW:
      setlocale(LC_ALL, "zh_TW.utf8");
      language_group_set(select);
      break; /*繁体中文*/
    case french_FR:
      setlocale(LC_ALL, "fr_FR.utf8");
      language_group_set(select);
      break; /*法语*/
    case spanish_ES:
      setlocale(LC_ALL, "es_ES.utf8");
      language_group_set(select);
      break; /*西班牙语*/
    case arabic_AE:
      setlocale(LC_ALL, "ar_AE.utf8");
      language_group_set(select);
      break; /*阿拉伯语(阿联酋)*/
    case german_DE:
      setlocale(LC_ALL, "de_DE.utf8");
      language_group_set(select);
      break; /*德语*/
    case russians_RU:
      setlocale(LC_ALL, "ru_RU.utf8");
      language_group_set(select);
      break; /*俄语*/
    case Danish_DK:
      setlocale(LC_ALL, "da_DK.utf8");
      language_group_set(select);
      break; /*丹麦语*/
    case portuguese_PT:
      setlocale(LC_ALL, "pt_PT.utf8");
      language_group_set(select);
      break; /*葡萄牙语*/
    case japanese_JP:
      setlocale(LC_ALL, "ja_JP.utf8");
      language_group_set(select);
      break; /*日语*/
#endif
    default:
      setlocale(LC_ALL, "en_US.utf8");
      break; /*linux没必要替换编码集，因为会乱码*/
  }
  language_group_set(select);
}
/*终端交互形式的设置语言*/
void Language_setting_interaction(void) {
  for (int ch = 0, t = 0;;) {
    if (thesystem == WINDOWS) {
      system("cls");
    } else if (thesystem == LINUX) {
      system("clear");
    }
    for (int i = 0; i < Count_language; i++) {
#ifdef _WIN32
      wprintf(L"%d:", i);
      printf("%s", c_language[i]);
#elif __linux__
      wprintf(L"%d: %s", i, c_language[i]);
#endif
      if (i == t) {
        wprintf(L"  <--choise");
      }
      wprintf(L"\n");
    }
    ch = getch();
    if (ch == 72) t -= 1;
    if (ch == 80) t += 1;
    if (t == Count_language) t = 0;
    if (t < 0) t = Count_language - 1;
    if (ch == '\r') {
      set_language(t);
      break;
    }
  }
  return;
}
/*设置语言集显示内容*/
static void language_group_set(int select) {
  switch (select) {
    default:
      language_group_set(english_US);
      break;
    case english_US: {
      struct LANGUNAGE_SUPPORT setlanguage = {
          L"Illegal characters, you can only use valid characters, for "
          L"example:",
          L"Version",
          L"Invalid command line, you can run it in the following way:",
          english_US_help,
          L"No current command parameters, please use the\" mytips -help "
          L"\"command to view the help file",
          L"Delete this note?",
          L"Performing version update operation",
          L"Deletion operation completed",
          L"Entry not found",
          L"Archiving failed",
          L"Entry found",
          L"Modify note entry",
          L"Completed",
          L"Empty text error",
          L"Add note entry",
          L"Entry already exists",
          L"请输入新的文本编辑器名称",
          L"文本编辑器名修改成功",
          L"文本编辑器名修改失败",
          L"请输入新的笔记名称：",
          L"命名冲突，现有笔记已经存在"
          /*setlang*/};
      language_pack = setlanguage;
    } break;

    case english_GB: {
      struct LANGUNAGE_SUPPORT setlanguage = {
          L"Illegal characters, you can only use valid characters, for "
          L"example:",
          L"Version",
          L"Invalid command line, you can run it in the following way:",
          english_GB_help,
          L"No current command parameters, please use the\" mytips -help "
          L"\"command to view the help file",
          L"Delete this note?",
          L"Performing version update operation",
          L"Deletion operation completed",
          L"Entry not found",
          L"Archiving failed",
          L"Entry found",
          L"Modify note entry",
          L"Completed",
          L"Empty text error",
          L"Add note entry",
          L"Entry already exists",
          L"请输入新的文本编辑器名称",
          L"文本编辑器名修改成功",
          L"文本编辑器名修改失败",
          L"请输入新的笔记名称：",
          L"命名冲突，现有笔记已经存在"
          /*setlang*/};
      language_pack = setlanguage;
    } break;

    case chinese_CN: {
      struct LANGUNAGE_SUPPORT setlanguage = {
          L"非法字符，你只能使用合法字符，例如：",
          L"版本",
          L"无效命令行，你可以按照这个方式运行：",
          chinese_CN_help,
          L"无当前命令参数，请使用\"mytips -help\"命令查看帮助文件",
          L"删除这个笔记吗?",
          L"正在进行版本更新操作",
          L"完成删除操作",
          L"找不到条目",
          L"存档失败",
          L"找到条目",
          L"修改笔记条目",
          L"完成",
          L"空文本错误",
          L"添加笔记条目",
          L"条目已存在",
          L"请输入新的文本编辑器名称",
          L"文本编辑器名修改成功",
          L"文本编辑器名修改失败",
          L"请输入新的笔记名称：",
          L"命名冲突，现有笔记已经存在"
          /*setlang*/};
      language_pack = setlanguage;
    } break;

    case chinese_TW: {
      struct LANGUNAGE_SUPPORT setlanguage = {
          L"非法字符，你只能使用合法字符，例如：",
          L"版本",
          L"無效命令行，你可以按照這個方式運行：",
          chinese_TW_help,
          L"無當前命令參數，請使用\"mytips -help\"命令查看幫助檔",
          L"刪除這個筆記？",
          L"正在進行版本更新操作",
          L"刪除操作完成",
          L"找不到項目",
          L"存檔失敗",
          L"找到項目",
          L"修改筆記項目",
          L"完成",
          L"空文本錯誤",
          L"新增筆記項目",
          L"項目已存在",
          L"请输入新的文本编辑器名称",
          L"文本编辑器名修改成功",
          L"文本编辑器名修改失败",
          L"请输入新的笔记名称：",
          L"命名冲突，现有笔记已经存在"
          /*setlang*/};
      language_pack = setlanguage;
    } break;

    case french_FR: {
      struct LANGUNAGE_SUPPORT setlanguage = {
          L"Caractères non valides, vous ne pouvez utiliser que des caractères "
          L"valides, par exemple :",
          L"Version",
          L"Ligne de commande non valide, vous pouvez l'exécuter de la manière "
          L"suivante :",
          french_FR_help,
          L"Aucun paramètre de commande actuel, utilisez la commande mytips - "
          L"help pour afficher les fichiers d'aide",
          L"Supprimer cette note ?",
          L"Opération de mise à jour de version en cours",
          L"Opération de suppression terminée",
          L"Entrée non trouvée",
          L"Échec de l'archivage",
          L"Entrée trouvée",
          L"Modifier l'entrée de la note",
          L"Terminé",
          L"Erreur de texte vide",
          L"Ajouter une entrée de note",
          L"entrée existe déjà" /*setlang*/,
          L"请输入新的文本编辑器名称",
          L"文本编辑器名修改成功",
          L"文本编辑器名修改失败",
          L"请输入新的笔记名称：",
          L"命名冲突，现有笔记已经存在"
          /*setlang*/};
      language_pack = setlanguage;
    } break;

    case spanish_ES: {
      struct LANGUNAGE_SUPPORT setlanguage = {
          L"Caracteres no válidos, solo se pueden utilizar caracteres válidos, "
          L"por ejemplo:",
          L"Versión",
          L"Línea de comando no válida, puede ejecutarla de la siguiente "
          L"manera:",
          spanish_ES_help,
          L"No hay parámetros de comando actuales, use el Comando mytips - "
          L"help para ver el archivo de ayuda",
          L"¿Eliminar esta nota?",
          L"Realizando operación de actualización de versión",
          L"Operación de eliminación completada",
          L"No se encontró la entrada",
          L"Fallo al archivar",
          L"Entrada encontrada",
          L"Modificar entrada de nota",
          L"Completado",
          L"Error de texto vacío",
          L"Añadir entrada de nota",
          L"a entrada ya existe",
          L"请输入新的文本编辑器名称",
          L"文本编辑器名修改成功",
          L"文本编辑器名修改失败",
          L"请输入新的笔记名称：",
          L"命名冲突，现有笔记已经存在"
          /*setlang*/};
      language_pack = setlanguage;
    } break;

    case arabic_AE: {
      struct LANGUNAGE_SUPPORT setlanguage = {
          L"أحرف غير صالحة، يمكنك استخدام أحرف صالحة فقط، على سبيل المثال:",
          L"الإصدار",
          L"سطر الأوامر غير صالح، يمكنك تشغيلها بالطريقة التالية:",
          arabic_AE_help,
          L"عذرًا، لا يوجد معاملات أو أوامر حالية. يُرجى استخدام الأمر \"mytips "
          L"-help\" لعرض ملف المساعدة.",
          L"هل ترغب في حذف هذا الملاحظة؟",
          L"جاري تنفيذ عملية تحديث الإصدار",
          L"اكتملت عملية الحذف",
          L"العنصر غير موجود",
          L"فشل في الأرشفة",
          L"تم العثور على العنصر",
          L"تعديل مدخل الملاحظة",
          L"اكتمل",
          L"خطأ في النص الفارغ",
          L"إضافة مدخل الملاحظة",
          L"العنصر موجود بالفعل",
          L"请输入新的文本编辑器名称",
          L"文本编辑器名修改成功",
          L"文本编辑器名修改失败",
          L"请输入新的笔记名称：",
          L"命名冲突，现有笔记已经存在"
          /*setlang*/};
      language_pack = setlanguage;
    } break;

    case german_DE: {
      struct LANGUNAGE_SUPPORT setlanguage = {
          L"Ungültige Zeichen, Sie können nur gültige Zeichen verwenden, zum "
          L"Beispiel:",
          L"Version",
          L"Ungültige Befehlszeile, Sie können sie folgendermaßen ausführen:",
          german_DE_help,
          L"Keine aktuellen Befehlsparameter vorhanden. Bitte verwenden Sie "
          L"den Befehl \"mytips -help\", um die Hilfe anzuzeigen.",
          L"Möchten Sie diese Notiz löschen?",
          L"Führe Versionsaktualisierung durch",
          L"Löschvorgang abgeschlossen",
          L"Eintrag nicht gefunden",
          L"Lokales Archivieren fehlgeschlagen",
          L"Lokaler Eintrag gefunden",
          L"Lokalen Notizeintrag bearbeiten",
          L"Abgeschlossen",
          L"Leerer Textfehler",
          L"Notizeintrag hinzufügen",
          L"Eintrag existiert bereits",
          L"请输入新的文本编辑器名称",
          L"文本编辑器名修改成功",
          L"文本编辑器名修改失败",
          L"请输入新的笔记名称：",
          L"命名冲突，现有笔记已经存在"
          /*setlang*/};
      language_pack = setlanguage;
    } break;

    case russians_RU: {
      struct LANGUNAGE_SUPPORT setlanguage = {
          L"Недопустимые символы, вы можете использовать только допустимые "
          L"символы, например:",
          L"Версия",
          L"Недопустимая командная строка, вы можете запустить ее следующим "
          L"образом:",
          russians_RU_help,
          L"Нет текущих параметров команды. Пожалуйста, используйте команду "
          L"\"mytips -help\", чтобы просмотреть файл справки.",
          L"Удалить эту запись?",
          L"Выполняется операция обновления версии",
          L"Операция удаления завершена",
          L"Запись не найдена",
          L"Ошибка при архивировании",
          L"Запись найдена",
          L"Изменить запись заметки",
          L"Завершено",
          L"Ошибка пустого текста",
          L"Добавить запись заметки",
          L"Запись уже существует",
          L"请输入新的文本编辑器名称",
          L"文本编辑器名修改成功",
          L"文本编辑器名修改失败",
          L"请输入新的笔记名称：",
          L"命名冲突，现有笔记已经存在"
          /*setlang*/};
      language_pack = setlanguage;
    } break;

    case portuguese_PT: {
      struct LANGUNAGE_SUPPORT setlanguage = {
          L"Caracteres inválidos, só pode utilizar caracteres válidos, por "
          L"exemplo:",
          L"Versão",
          L"Linha de comando inválida, pode executá-la da seguinte forma:",
          portuguese_PT_help,
          L"Não há parâmetros de comando atuais. Por favor, use o comando "
          L"\"mytips -help\" para ver o arquivo de ajuda.",
          L"Eliminar esta nota?",
          L"A realizar a operação de atualização de versão",
          L"Operação de eliminação concluída",
          L"Entrada não encontrada",
          L"Falha ao arquivar",
          L"Entrada encontrada",
          L"Modificar entrada da nota",
          L"Concluído",
          L"Erro de texto vazio",
          L" Adicionar entrada da nota",
          L"A entrada já existe",
          L"请输入新的文本编辑器名称",
          L"文本编辑器名修改成功",
          L"文本编辑器名修改失败",
          L"请输入新的笔记名称：",
          L"命名冲突，现有笔记已经存在"
          /*setlang*/};
      language_pack = setlanguage;
    } break;

    case Danish_DK: {
      struct LANGUNAGE_SUPPORT setlanguage = {
          L"Ugyldige tegn, du kan kun bruge gyldige tegn, for eksempel:",
          L"Version",
          L"Ugyldig kommandolinje, du kan køre den på følgende måde:",
          Danish_DK_help,
          L"Der er ingen aktuelle kommandoparametre. Brug venligst kommandoen "
          L"\"mytips -help\" for at se hjælpefilen.",
          L"Slette denne note?",
          L"Udfører versionsoverførsel",
          L"Sletningsoperation fuldført",
          L"Post ikke fundet",
          L"Arkivering mislykkedes",
          L"Post fundet",
          L"Rediger noteindgang",
          L"Fuldført",
          L"Tom tekstfejl",
          L"Tilføj noteindgang",
          L"Indgangen findes allerede",
          L"请输入新的文本编辑器名称",
          L"文本编辑器名修改成功",
          L"文本编辑器名修改失败",
          L"请输入新的笔记名称：",
          L"命名冲突，现有笔记已经存在"
          /*setlang*/};
      language_pack = setlanguage;
      break;
    }
    case japanese_JP: {
      struct LANGUNAGE_SUPPORT setlanguage = {
          L"無効な文字が含まれています。有効な文字のみを使用できます。例:",
          L"バージョン",
          L"無効なコマンドラインです。次の方法で実行できます:",
          japanese_JP_help,
          L"現在のコマンドパラメータはありません。ヘルプファイルを表示するには"
          L"、\"mytips -help\"コマンドを使用してください。",
          L"このノートを削除しますか？",
          L"バージョン更新操作を実行しています",
          L"削除操作が完了しました",
          L"エントリが見つかりません",
          L"保存に失敗しました",
          L"エントリが見つかりました",
          L"ノートのエントリを変更します",
          L"完了",
          L"空のテキストエラー",
          L"ノートのエントリを追加します",
          L"エントリはすでに存在しています",
          L"请输入新的文本编辑器名称",
          L"文本编辑器名修改成功",
          L"文本编辑器名修改失败",
          L"请输入新的笔记名称：",
          L"命名冲突，现有笔记已经存在"
          /*setlang*/};
      language_pack = setlanguage;
      break;
    }
  }
  /*未编写区域，将会在之后支持*/
  return;
}