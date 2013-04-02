#include "kvs_error.h"

unsigned int kvs_errno = KVS_NO_ERROR;

const char * const kvs_errlist[KVS_MAX_ERRNO + 1] = {
    N_("No error"), 				/*KVS_NO_ERROR 0*/
    N_("Index file open error"), 	/*KVS_INDEX_OPEN_ERROR 1*/
    N_("Metadata file open error"), /*KVS_META_OPEN_ERROR 2*/
    N_("Index file read error"),    /*KVS_INDEX_READ_ERROR 3*/
    N_("Metadata file read error"), /*KVS_META_READ_ERROR 4*/
    N_("Index file write error"),   /*KVS_INDEX_WRITE_ERROR 5*/
    N_("Metadata file write error"), /*KVS_META_WRITE_ERROR 6*/
    N_("Bad magic number"),			 /*KVS_BAD_MAGIC_NUMBER 7*/
    N_("Medadata file can't be write"),   /*KVS_META_CANT_BE_WRITER 8*/
    N_("Index file can't be write"),	  /*KVS_INDEX_CANT_BE_WRITER 9*/
    N_("Index file can't be reader"),     /*KVS_INDEX_CANT_BE_READER 10*/
    N_("Metadata file can't be reader"),  /*KVS_META_CANT_BE_READER 11*/
    N_("Index/Metadata reader can't store"),/*KVS_INDEX_READER_CANT_STORE 12*/
    N_("Index/Metadata reader can't store"), /*KVS_META_READER_CANT_STORE 13*/
    N_("Index/Metadata reader can't delete"),/*KVS_INDEX_READER_CANT_DELETE 14*/
    N_("Index/Metadata reader can't delete"),/*KVS_META_READER_CANT_DELETE 15*/
    N_("Index reader can't compact"),/*KVS_INDEX_READER_CANT_COMPACTION 16*/
    N_("Meta reader can't compact"),/*KVS_META_READER_CANT_COMPACTION 17*/
    N_("Index reader can't update"),/*KVS_INDEX_READER_CANT_UPDATE 18*/
    N_("Meta reader can't update"),/*KVS_META_READER_CANT_UPDATE 19*/
    N_("Index item not found"),/*KVS_INDEX_ITEM_NOT_FOUND 20*/
    N_("Metadata item not found"),/*KVS_META_ITEM_NOT_FOUND 21*/
    N_("Index file illeagal data"),/*KVS_INDEX_ILLEAGAL_DATA 22*/
    N_("Meta file illeagal data"),/*KVS_META_ILLEAGAL_DATA 23*/
    N_("Index file has no enough space"),/*KVS_INDEX_NO_SPACE 24*/
    N_("Meta file has no enough space"),/*KVS_META_NO_SPACE 25*/
    N_("Malloc memory error"),/*KVS_MALLOC_SERROR 26*/
    N_("Create index file error"),/*KVS_INDEX_CREAT_ERROR 27*/
    N_("Create metadata file error"),/*KVS_META_CREAT_ERROR 28*/
    N_("Fail to check index file"),/*KVS_INDEX_FILE_CHECK_ERROR 29*/
    N_("Fail to check metadata file"),/*KVS_META_FILE_CHECK_ERROR 30*/
    N_("Fail to allocate inode"),/*KVS_INODE_MALLOC_ERROR 31*/
    N_("Fail to allocate bnode"),/*KVS_BNODE_MALLOC_ERROR 32*/
    N_("Invalid argument."),/*KVS_INVALID_ARGUMENT 33*/
    N_("Function not implemented"),/*KVS_NO_SYSCALL 34*/
    N_("Index key has existed"),/*KVS_INDEX_EXIST 35*/
    N_("Index has reached maximum level"),/*KVS_INDEX_MAX_LEVEL 36*/
    N_("Index key hasn't existed"),/*KVS_INDEX_NOT_EXIST 37*/
    N_("File has existed"),/*KVS_FS_ENTRY_EXIST 38*/
    N_("File hasn't existed"),/*KVS_FS_ENTRY_NOEXIST 39*/
    N_("Directory entry is full"),/*KVS_FS_ENTRY_FULL 40*/
    N_("Unknown error"),/*KVS_UNKNOWN_ERROR 41*/
    N_("File ino han't existed"),/*KVS_FS_INO_NOEXIST 42*/
    N_("File Directory isn't empty"),/*KVS_FS_DIR_NOEMPTY 43*/
    N_("File isn't directory"),/*KVS_FS_NO_DIR 44 */
    N_("Root can't delete"),/*KVS_FS_ROOT 45 */
    N_("File entry isn't directory"),/*KVS_FS_NODIR 46*/
    };

    
const char * kvs_strerror(unsigned int error)
{
    if((((int) error) < KVS_MIN_ERRNO) || ((int)error > KVS_MAX_ERRNO))
        return _("Unknown error");
    else
        return _(kvs_errlist[(int)error]);
}
