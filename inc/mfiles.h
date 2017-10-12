#ifndef MFILES_H
#define MFILES_H

#define MAX_PATH_SIZE 512

#define DEFAULT_DIR "lib/"

typedef struct Mat_file {
    char fpath[MAX_PATH_SIZE];
    size_t fsize;
    void* fdata;
    FILE* fptr;
}* file_t;

file_t file_import(char* path);

file_t file_new(file_t mfile, const void* data, size_t size);

void file_export(file_t mfile);

void file_delete(file_t mfile);

#endif /* end of include guard: MFILES_H */
