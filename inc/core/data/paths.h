#ifndef PATHS_H
#define PATHS_H

#define MAX_PATH_SIZE 64
#define MAX_NAME_SIZE 32
#define MAX_EXT_SIZE 8

typedef struct {
    char path[MAX_PATH_SIZE];
    char name[MAX_NAME_SIZE];
    char ext[MAX_EXT_SIZE];
} path_t;

void getPathNameExt(path_t *fpath, char* path);

void setPathNameExt(path_t *fpath, char* path, char* name, char* ext);

#endif /* end of include guard: PATHS_H */
