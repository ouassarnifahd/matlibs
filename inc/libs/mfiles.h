#ifndef MFILES_H
#define MFILES_H

#include "liste.h"

#define MAX_PATH_SIZE 512

#define MAX_FILES 20

#define Kio 1ull << 10
#define MAX_FILE_SIZE 100 * Kio

#define SAVE_DIR "lib/"

typedef struct Mat_file {
    char fpath[MAX_PATH_SIZE];
    char* fname;
    size_t fsize;
    void* fdata;
    FILE* fptr;
}* file_t;

static TList files_Opened = {
    MAX_FILES, sizeof(file_t),
    NULL, NULL, NULL, -1
};

file_t file_import(char* path);

file_t file_new(file_t mfile, const void* data, size_t size);

void file_export(file_t mfile);

void file_delete(file_t mfile);

#endif /* end of include guard: MFILES_H */
