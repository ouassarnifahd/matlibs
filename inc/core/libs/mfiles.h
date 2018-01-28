#ifndef MFILES_H
#define MFILES_H

typedef struct Mat_file *file_t;

file_t file_import(char* path);

file_t file_new(char* fname, const void* data, uint32_t size);

void file_export(file_t mfile);

void file_delete(file_t mfile);

#endif /* end of include guard: MFILES_H */
