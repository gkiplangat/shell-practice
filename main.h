#ifndef MAIN_H
#define MAIN_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <wait.h>
#include <fcntl.h>
#include <dirent.h>
#include <signal.h>


extern char **environ;
void _print_string(char *str);
void prompt_user(void);
char *user_input(void);
int _string_length(char *s);
char *_concat_strings(char *dest, char *src);
char **_string_tokens(char *str);
int _execute(char **tokens, char *args);
void _printenv(void);
int _write_char(char c);
int _compare_strings(char *s1, char *s2);
int _executeBuiltIn(char **tokens);
int _isBuiltIn(char *str);
int custom_atoi(char *s);
void _kill(char *lineptr, char *tmp, char **tok);
void _exit_shell(char **tokens, char *line);
void ctrlc(int signum);
int check_for_delim(char c, const char *delim);
char *_tokenize_string(char *src, const char *delim);
char *_copy_string(char *dest, char *src);
ssize_t get_line(char **str);
int handle_path(char **tokens);
int if_file_exists(char *s);
char *path_builder(char **tokens);
int execute2(char **tokens, char *path, char *args);
char *var_build(char *var_name, char *var_value);
int _setenv(char *var_name, char *var_value);
int _unsetenv(char *var_name);
char *_duplicate_string(char *str);

#endif
