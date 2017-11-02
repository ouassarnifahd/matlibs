#ifndef ERROR_H
#define ERROR_H

#include <time.h>

#define BUFFER_SIZE 128

#define LOGFILE_PATH "./debug/logfile.mlb"

char out_buf[BUFFER_SIZE];
char out_str[BUFFER_SIZE];
char log_str[BUFFER_SIZE];

static FILE* logfile = NULL;

#define init_log() \
    logfile = fopen(LOGFILE_PATH, "w"); \
    if (!logfile) { \
        fprintf(stderr, "\033[0;31m[ERROR]\033[0m '%s' wont open!\n", LOGFILE_PATH); \
        exit(EXIT_FAILURE); \
    } \
    time_t now; now = time(NULL); \
    fprintf(logfile, "###########################################################\n"); \
    fprintf(logfile, "# Compiled on %s at %s\n", __DATE__, __TIME__); \
    fprintf(logfile, "# Executed on %s", ctime(&now)); \
    fprintf(logfile, "###########################################################\n\n"); \
    fflush(logfile); fclose(logfile); logfile = NULL

#define log(str) \
    logfile = fopen(LOGFILE_PATH, "a"); \
    if (!logfile) { \
        fprintf(stderr, "\033[0;31m[ERROR]\033[0m '%s' wont open!\n", LOGFILE_PATH); \
        exit(EXIT_FAILURE); \
    } \
    fprintf(logfile, "%s\n", str); fflush(logfile); fclose(logfile); logfile = NULL

#define error(MSG, ...) \
    sprintf(out_str, "\033[0;31m[ERROR]\033[0m (%s:%s:%i) ", __FILE__, __func__, __LINE__); \
    sprintf(log_str, "[ERROR] (%s:%s:%i) ", __FILE__, __func__, __LINE__); \
    sprintf(out_buf, MSG, ##__VA_ARGS__); strcat(out_str, out_buf); \
    strcat(log_str, out_buf); fprintf(stderr, "%s\n", out_str); \
    fflush(stderr); log(log_str); exit(EXIT_FAILURE)

#define alloc_check(PTR) { if((PTR) == NULL) { error("Out of Memory!"); } }

#define warning(MSG, ...) \
    sprintf(out_str, "\033[1;33m[WARNING]\033[0m (%s:%s:%i) ", __FILE__, __func__, __LINE__); \
    sprintf(log_str, "[WARNING] (%s:%s:%i) ", __FILE__, __func__, __LINE__); \
    sprintf(out_buf, MSG, ##__VA_ARGS__); strcat(out_str, out_buf); \
    strcat(log_str, out_buf); fprintf(stdout, "%s\n", out_str); \
    fflush(stdout); log(log_str)

#define debug(MSG, ...) \
    sprintf(out_str, "\033[0;35m[DEBUG]\033[0m (%s:%s:%i) ", __FILE__, __func__, __LINE__); \
    sprintf(log_str, "[DEBUG] (%s:%s:%i) ", __FILE__, __func__, __LINE__); \
    sprintf(out_buf, MSG, ##__VA_ARGS__); strcat(out_str, out_buf); \
    strcat(log_str, out_buf); fprintf(stdout, "%s\n", out_str); \
    fflush(stdout); log(log_str)

#endif /* end of include guard: ERROR_H */
