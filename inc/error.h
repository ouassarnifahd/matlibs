#ifndef ERROR_H
#define ERROR_H

#define BUFFER_SIZE 1024

#define LOGFILE_PATH "debug/logfile.mlb"

char out_buf[128];
char out_str[128];

static FILE* logfile = NULL;

#define log(str) \
    logfile = fopen(LOGFILE_PATH, "a"); \
    fprintf(logfile, "%s\n", str); fflush(logfile); \
    fclose(logfile); logfile = NULL;

#define error(MSG, ...) \
    sprintf(out_str, "[ERROR] (%s:%s:%i) ", __FILE__, __func__, __LINE__); \
    sprintf(out_buf, MSG, ##__VA_ARGS__); strcat(out_str, out_buf); \
    fprintf(stderr, "%s\n", out_str); fflush(stderr); \
    log(out_str); exit(EXIT_FAILURE);

#define alloc_check(PTR) { if((PTR) == NULL) { error("Out of Memory!"); } }

#define warning(MSG, ...) \
    sprintf(out_str, "[WARNING] (%s:%s:%i) ", __FILE__, __func__, __LINE__); \
    sprintf(out_buf, MSG, ##__VA_ARGS__); strcat(out_str, out_buf); \
    fprintf(stdout, "%s\n", out_str); fflush(stdout); log(out_str);

#define debug(MSG, ...) \
    sprintf(out_str, "[DEBUG] (%s:%s:%i) ", __FILE__, __func__, __LINE__); \
    sprintf(out_buf, MSG, ##__VA_ARGS__); strcat(out_str, out_buf); \
    fprintf(stdout, "%s\n", out_str); fflush(stdout); log(out_str);

#endif /* end of include guard: ERROR_H */
