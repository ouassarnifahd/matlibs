#ifndef MFILES_H
#define MFILES_H

#include "data/alloc.h"
#include "data/liste.h"
#include "data/md5.h"

#define MAX_PATH_SIZE 64
#define MAX_NAME_SIZE 32
#define MAX_EXT_SIZE 8

#define MAX_FILES 20

#define HEADER_BEGIN "MLB." // 0x4D, 0x49, 0x2E
#define HEADER_SIZE (4 + 2 + (16 + 4) + 8)
#define HEADER_END "MATLIBS." // 0x4D, 0x41, 0x54, 0x4C, 0x49, 0x42, 0x53, 0x2E

#define MAX_FILE_SIZE MAX_MEMORY + HEADER_SIZE

#define SAVE_DIR "lib/"
#define DEFAULT_EXT ".mlb"

typedef struct {
    char path[MAX_PATH_SIZE];
    char name[MAX_NAME_SIZE];
    char ext[MAX_EXT_SIZE];
} path_t;

typedef struct Mat_file {
    path_t fpath;
    uint32_t fsize;
    void* fdata;
    md5sum_t fchecksum;
    FILE* fptr;
}* file_t;

static TList files_Opened = {
    0, sizeof(file_t),
    NULL, NULL, NULL, -1
};

file_t file_import(char* path);

file_t file_new(char* fname, const void* data, uint32_t size);

void file_export(file_t mfile);

void file_delete(file_t mfile);

#endif /* end of include guard: MFILES_H */
