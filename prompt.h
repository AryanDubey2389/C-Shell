#ifndef __PROMPT_H
#define __PROMPT_H

int prompt();
void listing();
void listing_l();
void command_cd();
void command_ls();
char** store_history();
void redirection();
void ini_history();
int repeat();
int pinfo();
void command_echo();
void command_pwd();
void command_exec();
char* rel_path();
struct process_details {
   char name[50];
   int id1; 
   int pid;
};
void details();
// int id = 1;
#endif
