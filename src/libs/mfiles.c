#include "libs/mfiles.h"

/** Data binary structure!
* HEADER(0x30) = [ BEGIN(0x8) + startData(0xX) + [ md5Data(0x10) + sizeData(0xY) ] + END(0x8)]
*/

static const struct { char *ext; char *filetype; } extensions [] = {
    {".mlb", "matlib library" },
    {".plt", "plot/data"      },
    {".png", "plot/png"       },
    {0,0}
};

static void setPathNameExt(path_t *fpath, char* path, char* name, char* ext) {
    #ifdef DEBUG_CONTEXT
    debug("String copy function!");
    #endif
    size_t lpath = 0, lname = 0;
    for (size_t i = 0; i < MAX_PATH_SIZE && path[i] != '\0'; i++) {
        fpath->path[i] = path[i];
        lpath = i + 1;
    }
    for (size_t i = 0; i < MAX_NAME_SIZE && name[i] != '\0'; i++) {
        fpath->name[i] = name[i];
        fpath->path[lpath + i] = name[i];
        lname = i + 1;
    }
    for (size_t i = 0; i < MAX_EXT_SIZE  && ext[i]   != '\0'; i++) {
        fpath->ext[i] = ext[i];
        fpath->path[lpath + lname + i] = ext[i];
    }
}

static void getPathNameExt(path_t *fpath, char* path) {
    #ifdef DEBUG_CONTEXT
    debug("String copy function!");
    #endif
    size_t lpath = 0, lname = 0;
    for (size_t i = 0; i < MAX_PATH_SIZE; i++) {
        fpath->path[i] = path[i];
        if (path[i] == '/') {
            lpath = i + 1;
            break;
        }
    }
    for (size_t i = 0; i < MAX_NAME_SIZE && path[lpath + i] != '.'; i++) {
        fpath->name[i] = path[lpath + i];
        lname = i + 1;
    }
    for (size_t i = 0; i < MAX_EXT_SIZE  && path[lpath + lname + i] != '\0'; i++) {
        fpath->ext[i] = path[lpath + lname + i];
    }
}

file_t file_new(char* fname, const void* data, size_t size) {
    #ifdef DEBUG_CONTEXT
    debug("Entering function!");
    #endif
    file_t new = malloc(sizeof(struct Mat_file));
    alloc_check(new);
    #ifdef DEBUG_MALLOC
    debug("Memory allocation 'file_t': %zu Octets", sizeof(struct Mat_file));
    #endif
    setPathNameExt(&new->fpath, SAVE_DIR, fname, DEFAULT_EXT);
    new->fsize.size = size;
    if (size < MAX_FILE_SIZE) {
        new->fdata = malloc(size);
        alloc_check(new->fdata);
        #ifdef DEBUG_MALLOC
        debug("Memory allocation 'void*': %zu Octets", size);
        #endif
        memcpy(new->fdata, data, size);
    } else {
        error("Max file size exceeded!");
    }
    md5_check(new->fdata, new->fsize.size, new->fchecksum);
    new->fptr = NULL;
    #ifdef DEBUG_CONTEXT
    debug("leaving function!\n");
    #endif
    return new;
}

void file_delete(file_t mfile) {
    #ifdef DEBUG_CONTEXT
    debug("Entering function!");
    #endif
    if (mfile) {
        if (mfile->fdata) {
            free(mfile->fdata);
            #ifdef DEBUG_FREE
            debug("Memory freed (void*)");
            #endif
            mfile->fdata = NULL;
        }
        if (mfile->fptr) {
            fclose(mfile->fptr);
            mfile->fptr = NULL;
        }
        #ifdef DEBUG_FREE
        debug("Memory freed (file_t)");
        #endif
        free(mfile);
        mfile = NULL;
    }
    #ifdef DEBUG_CONTEXT
    debug("leaving function!\n");
    #endif
}

static size_t getLastSignificantByte(sizem_t usize) {
    size_t size = sizeof(size_t);
    for (size_t i = 0; i < sizeof(size_t) - 1; i += 2) {
        if (usize.mem[i] == 0 && usize.mem[i + 1] == 0) {
            size--;
        }
        printf("%hhx, %hhx, ", usize.mem[i], usize.mem[i + 1]);
    }
    printf("\n");
    return (size < 8)? ((size < 4)? 4: 8): 8;
}

void file_export(file_t mfile) {
    #ifdef DEBUG_CONTEXT
    debug("Entering function!");
    #endif
    mfile->fptr = fopen(mfile->fpath.path, "wb");
    if (mfile->fptr) {
        size_t sizeofSizeD = getLastSignificantByte(mfile->fsize);
        printf("%zu\n", sizeofSizeD);
        size_t hsize = HEADER_SIZE(sizeofSizeD);
        fwrite(HEADER_BEGIN, 1, 4, mfile->fptr);
        fwrite(&hsize, 1, 2, mfile->fptr);
        fwrite(mfile->fchecksum, 1, 16, mfile->fptr);
        fwrite(&mfile->fsize, 1, sizeofSizeD, mfile->fptr);
        fwrite(HEADER_END, 1, 8, mfile->fptr);
        fwrite(mfile->fdata, 1, mfile->fsize.size, mfile->fptr);
        fclose(mfile->fptr);
        mfile->fptr = NULL;
    } else {
        error("Can't open the file '%s'!", mfile->fpath.path);
    }
    #ifdef DEBUG_CONTEXT
    debug("leaving function!\n");
    #endif
}

file_t file_import(char* path) {
    #ifdef DEBUG_CONTEXT
    debug("Entering function!");
    #endif
    file_t import = malloc(sizeof(struct Mat_file));
    alloc_check(import);
    #ifdef DEBUG_MALLOC
    debug("Memory allocation 'file_t': %zu Octets", sizeof(struct Mat_file));
    #endif
    getPathNameExt(&import->fpath, path);
    import->fptr = fopen(path, "rb");
    if (import->fptr) {
        fread(import->fchecksum, 1, 16, import->fptr);
        fread(&import->fsize.size, 1, sizeof(size_t), import->fptr);
        import->fdata = malloc(import->fsize.size);
        alloc_check(import->fdata);
        #ifdef DEBUG_MALLOC
        debug("Memory allocation 'void*': %zu Octets", import->fsize.size);
        #endif
        fread(import->fdata, 1, import->fsize.size, import->fptr);
        fclose(import->fptr);
        import->fptr = NULL;
    } else {
        error("Can't open the file '%s'!", path);
    }
    md5sum_t testsum;
    bool test = 1;
    md5_check(import->fdata, import->fsize.size, testsum);
    for (size_t i = 0; i < 16 && test; i++) {
        test = testsum[i] == import->fchecksum[i];
    }
    if (!test) {
        warning("The file '%s' maybe corrupted!", path);
    }
    #ifdef DEBUG_CONTEXT
    debug("leaving function!\n");
    #endif
    return import;
}

#ifdef DEBUG
int main(int argc, char const *argv[]) {
    #if defined (__x86_64__)
        debug("64-bit architecture!\n");
    #elif defined (__i386__)
        warning("32-bit architecture!\n");
    #else
        error("Incompatible architecture!");
    #endif
    char data[Kio];
    file_t sdata = file_new("helloworld", data, Kio);
    file_export(sdata);
    file_delete(sdata);
    // file_t fstr = file_import("lib/helloworld.mlb");
    // file_delete(fstr);
    debug("FY!");
    return 0;
}
#endif
