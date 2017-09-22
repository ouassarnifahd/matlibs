#ifndef SYSTEM_H
#define SYSTEM_H

char help[] = "usage: function <parameters...>";

int Mat_add(char **args);
int Mat_sub(char **args);
int Mat_mult(char **args);
int Mat_help(char **args);
int Mat_exit(char **args);

char *builtin_commands[] = {
    "add",
    "sub",
    "mult",
    "help",
    "exit"
};

// Hey you whats this! :p ==> void* (*f) (void* , void (*g)(void*));

int (*builtin_functions[]) (char **) = {
    &Mat_add,
    &Mat_sub,
    &Mat_mult,
    &Mat_help,
    &Mat_exit
};

void* interpreter(char* command);

#endif /* end of include guard: SYSTEM_H */
