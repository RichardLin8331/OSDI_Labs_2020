#ifndef R_SHELL_H
#define R_SHELL_H


void shell_run();
int parse_command(char * cmd);
void execute_command(int cmd_num);

#endif