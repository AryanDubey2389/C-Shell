#include "prompt.h"
#include "headers.h"
#define R 3000005 
int flag = -1,fg_proc,shellpid;
int id = 1;
int maxi = 0;
int max(int a, int b)
{
    if(a > b)
        return a;
    else
        return b;
}
int input_taking()
{
    struct timeval tv;
    tv.tv_sec = 0;
    tv.tv_usec = 0;
    fd_set fds;
    FD_ZERO(&fds);
    FD_SET(STDIN_FILENO,&fds);
    select(STDIN_FILENO+1,&fds,NULL,NULL,&tv);
    return FD_ISSET(STDIN_FILENO,&fds);
}
void handle_ctrlz(int signum) 
{
    // int pid = getpid();
    // printf("fg -> %d\n",fg_proc);
    // if (pid != shellpid) {
    //     return;
    // }
    // if (fg_proc == -1) {
        return;
}
struct process_details list[1000];
int min[1000];
void sort_details()
{
    int i, j;
    struct process_details temp;
    // printf("id -> %d\n",id);
    for (i = 1; i < id; i++)
    {
        for (j = 1; j < id -i; j++)
        {
            // printf("hlo\n");/
            if (strcmp(list[j].name,list[j + 1].name) > 0)
            {
                temp = list[j];
                // printf("list[%d].name -> %s\n",j,list[j].name);
                // printf("list[%d].name -> %s\n",j+1,list[j+1].name);  
                list[j] = list[j + 1];
                list[j + 1] = temp;
            } 
        }
    }
}
void details(char** name, int pid, int id1)
{
    // printf("[%d] ",id1);
    list[id1].id1 = id1;
    char str[1000] = "";
    int i = 0;
    while(strcmp(name[i],"&") != 0 || name[i] == NULL) 
    {
        if(i == 0)
            strcpy(str,name[i]);
        else
        {
            strcat(str," ");
            strcat(str,name[i]);
        }
        i++;
        if(name[i] == NULL)
            break;
    }
    // printf("lst -> %s\n",str);
    strcpy(list[id1].name,str);
    list[id1].pid = pid;    
}
void removing_process(int kill_num,int proc_index)
{
    // printf("\nkill -> %d\nid -> %d\n",kill_num,id);
    min[list[kill_num].id1]--;
    if(proc_index == id -1)
    {
        id--;
    }
    else
    {
        for(int i = proc_index; i < id; i++)
        {
            // printf("list[%d] -> %s\nlist[%d] -> %s\n",i,list[i].name,i+1,list[i+1].name);
            list[i].id1 = list[i+1].id1;
            strcpy(list[i].name,list[i+1].name);
            list[i].pid = list[i+1].pid;
        }
        // printf("list[%d] -> %s\nid -> %d pid -> %d\n",kill_num,list[kill_num].name,list[kill_num].id1,list[kill_num].pid);
        id--;
    }

    // printf("hlo");
}
char** exec_arr(char arr[100][100][100], char** args,int len, int itr1)
{   
    for(int i = 0; i < len; i++)
    {
        args[i] = (char*)malloc(sizeof(char)*1000);
        strcpy(args[i],arr[itr1][i]);
        // printf("arr -> %s\n",args[i]);
    }
    args[len] = NULL;
    // for(int i = 0; i < len; i++)
    // {
    //     args[i] = (char*)malloc(sizeof(char)*1000);
    //     printf("arr ->")
    // }
    return args;
}
int fin1_len1(char** fin1)
{
    int len_fin1 = 0;       
    for(int j = 0; ; j++)
    {
        if(fin1[j] == NULL)
            break;
        len_fin1++;
    }
    return len_fin1;
}
void handle_signal(int sig)
{
    int status;
    int val = waitpid(-1,&status,WNOHANG);
    if(val > 0)
    {
        int err = WIFEXITED(status), err1 = WIFSIGNALED(status), err2 = WIFSTOPPED(status);
        if(err == 1)
        {
            flag = 0;
            fprintf(stderr,"Process with PID %d exited normally\n",val);
        }
        else if(err1 == 1)
        {
            flag = 0;
            fprintf(stderr,"Process with PID %d exited abnormally\n",val);
        }
        else if(err2 == 1)
        {
            flag = 0;
            fprintf(stderr,"Process with PID %d stopped\n",val);
        }
    }
}
void removing_space(char str1[1000], char arr[1000],char* delim)
{
    char var[100][1000] = {};
    char *token = strtok(arr, delim);
    int i = 0;
    while(token != NULL )
    {
        strcat(var[i],token); 
        token = strtok(NULL, delim);
        i++;
    }
    for(int j = 0; j < i; j++)
    {
        strcat(str1,var[j]);
        if(j != i - 1)
            strcat(str1," ");
    }
}
void sys_info(char* temp, char homepath[1000])
{
    char path[1000];
    struct utsname uts;
    uname(&uts);
    char *buf;
    buf=(char *)malloc(10*sizeof(char));
    getlogin_r(buf,10);
    printf("<%s@%s:",buf,uts.nodename);
    int flg = 0;
    if(strlen(homepath) > strlen(temp))
        printf("%s>", getcwd(path, 100));
    else
    {
        for(int i = 0; i < strlen(homepath); i++)
        {
            if(homepath[i] != temp[i])
                flg = 1;
        }
        if(!flg)
        {
            printf("~");
            for(int i = strlen(homepath); i <= strlen(temp); i++)
                printf("%c",temp[i]);
            printf(">");
        }
        else
        {
            printf("%s>", getcwd(path, 100));
        }
    }
}
char* rel_path(char temp[1000], char homepath[1000], char int_path[1000])
{
    char path[1000];
    int flg = 0;
    if(strlen(homepath) > strlen(temp))
        return getcwd(path, 100);
    else
    {
        for(int i = 0; i < strlen(homepath); i++)
        {
            if(homepath[i] != temp[i])
                flg = 1;
        }
        if(!flg)
        {
            int_path[0] = '~';
            for(int i = strlen(homepath); i <= strlen(temp); i++)
                int_path[i+1-strlen(homepath)] = temp[i];
            return int_path;
        }
        else
        {
            return getcwd(path, 100);
        }
    }
}
void reversestr(char* str)
{
    char ch;
    long long int len = strlen(str);
    for(long long int i=0;i<len/2;i++)
    {
        ch = str[len-i-1];
        str[len-i-1]=str[i];
        str[i]=ch;
    }
}
char** get_array(char b[1000], char** fin)
{
    char* token = strtok(b, " ");
    int i = 0;
    fin = (char**)malloc(sizeof(char) * 1000 * 100); 
    while(token != NULL )
    {
        // fin[i] = (char *)malloc(1000*sizeof(char));
        fin[i] = token; 
        token = strtok(NULL, " ");
        // printf("fin -> %s\n",fin[i]);
        i++;
    }
    fin[i] = NULL;
    return fin;
}
void command_echo(char** fin1, int i)
{  
    i++;
    int len_fin1 = fin1_len1(fin1);  
    int itr;
    int flg = -1;
    int org = dup(0);
    for(int j = 0; j < len_fin1; j++)
    {
        // printf("fin1[%d] -> %s\n",j,fin1[j]);
        if(strcmp(fin1[j],">") == 0)
        {
            itr = j;
            flg = 0; 
            // redirection(fin1);
        }
        else if(strcmp(fin1[j],"<") == 0)
        {
            itr = j;
            flg = 1; 
        }
        else if(strcmp(fin1[j],">>") == 0)
        {
            itr = j;
            flg = 2; 
        }
    }
    if(flg == 0)
    {
        // printf("Welcome bro\n");
        int fd = open(fin1[itr+1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
        dup2(fd,STDOUT_FILENO);
        // if(<0)
        // {
        //     printf("Failed to duplicate file descriptor\n");
        // }
        close(fd);
        // printf("i -> %d     itr -> %d\n",i,itr);
        while( i < itr )
        {
            // printf("hi\n");
            printf("%s ",fin1[i]);
            i++;
        }
        printf("\n");
        dup2(org,STDOUT_FILENO);
    }
    if(flg == 1)
    {
        // printf("Welcome bro\n");
        int fd = open(fin1[itr+1], O_RDONLY);
        // dup2(fd,STDOUT_FILENO);
        if(fd<0)
        {
            printf("File does not exist\n");
            return;
        }
        close(fd);
        // printf("i -> %d     itr -> %d\n",i,itr);
        while( i < itr )
        {
            // printf("hi\n");
            printf("%s ",fin1[i]);
            i++;
        }
        printf("\n");
        dup2(org,STDOUT_FILENO);
    }
    else if(flg == 2)
    {
        int fd = open(fin1[itr+1], O_CREAT | O_RDWR | O_APPEND, 0644);
        dup2(fd,STDOUT_FILENO);
        // if(<0)
        // {
        //     printf("Failed to duplicate file descriptor\n");
        // }
        close(fd);
        // printf("i -> %d     itr -> %d\n",i,itr);
        while( i < itr )
        {
            // printf("hi\n");
            printf("%s ",fin1[i]);
            i++;
        }
        printf("\n");
        dup2(org,STDOUT_FILENO);
    }
    else if(flg == -1)
    {
        while(fin1[i] != NULL )
        {
            if(fin1[i+1] != NULL)
                printf("%s ",fin1[i]);
            else
                printf("%s",fin1[i]);
            i++;
        }
        printf("\n");
    }
    
}
void command_pwd(char** fin1)
{
    char path[1000];
    getcwd(path, 1000);
    int itr;
    int len_fin1 = fin1_len1(fin1); 
    int flg = -1;
    int org = dup(0);
    for(int j = 0; j < len_fin1; j++)
    {
        // printf("fin1[%d] -> %s\n",j,fin1[j]);
        if(strcmp(fin1[j],">") == 0)
        {
            itr = j;
            flg = 0; 
            // redirection(fin1);
        }
        else if(strcmp(fin1[j],"<") == 0)
        {
            itr = j;
            flg = 1; 
        }
        else if(strcmp(fin1[j],">>") == 0)
        {
            itr = j;
            flg = 2; 
        }
    }
    if(flg == 0)
    {
        // printf("Welcome bro\n");
        int fd = open(fin1[itr+1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
        dup2(fd,STDOUT_FILENO);
        // if(<0)
        // {
        //     printf("Failed to duplicate file descriptor\n");
        // }
        close(fd);
        // printf("i -> %d     itr -> %d\n",i,itr);
        printf("%s\n",path);
    }
    else if(flg == 1)
    {
        // printf("Welcome bro\n");
        int fd = open(fin1[itr+1], O_RDONLY);
        // dup2(fd,STDOUT_FILENO);
        if(fd<0)
        {
            printf("File does not exist\n");
            return;
        }
        close(fd);
        // printf("i -> %d     itr -> %d\n",i,itr);
        printf("%s\n",path);
    }
    else if(flg == 2)
    {
        int fd = open(fin1[itr+1], O_CREAT | O_RDWR | O_APPEND, 0644);
        dup2(fd,STDOUT_FILENO);
        // if(<0)
        // {
        //     printf("Failed to duplicate file descriptor\n");
        // }
        close(fd);
        // printf("i -> %d     itr -> %d\n",i,itr);
        printf("%s\n",path);
    }
    else if(flg == -1)
    {
        printf("%s\n",path);
    }
    dup2(org,STDOUT_FILENO);
    // printf("aa gye screen par\n");
}
char** get_args(char** fin1,char** args, int i)
{
    int j = 0;
    while(fin1[i]!=NULL)
    {
        args[j] = fin1[i];
        i++;
        j++;
    }
    return args;
}
void command_exec(char** fin1, int i, int flg)
{
    int itr=0, flg1 = -1, cnt = 0;
    char** red_arr = (char**)malloc(sizeof(char)*100 * 100);
    char** red_arr1 = (char**)malloc(sizeof(char)*100 * 100);
    red_arr[itr] = (char*)malloc(sizeof(char)*100);
    red_arr1[cnt] = (char*)malloc(sizeof(char)*100);
    red_arr[itr];
    char str[1000] = "";
    for(int j = 0; j < fin1_len1(fin1); j++) 
    {
        // printf("fin1[%d] -> %s\n",j,fin1[j]);
        if(strcmp(fin1[j],">") == 0 || ((strcmp(fin1[j],"<") == 0 || strcmp(fin1[j],">>") == 0)))
        {
            red_arr[itr] = (char*)malloc(sizeof(char)*100);
            // if(itr == 0)
                // strcpy(red_arr[itr],str);
            // else
                strcpy(red_arr[itr],str);
            itr++;
            strcpy(str,"");
            strcpy(red_arr1[cnt],fin1[j]);
            cnt++;
            red_arr1[cnt] = (char*)malloc(sizeof(char)*100);
            continue;
        }
        if(strcmp(str,"") == 0)
            strcpy(str,fin1[j]);
        else
        {
            strcat(str," ");
            strcat(str,fin1[j]);
        }
    }
    red_arr[itr] = (char*)malloc(sizeof(char)*100);
    // red_arr[itr] = "";
    strcpy(red_arr[itr],str);
    itr++;
    red_arr[itr] = NULL;
    // for(int j = 0; j <= itr; j++)
    //     printf("red_arr[%d] -> %s\n",j,red_arr[j]);
    // for(int j = 0; j < cnt; j++)
    //     printf("red_arr1[%d] -> %s\n",j,red_arr1[j]);
    int inside_loop = 0;
    for(int j = 0; j < cnt; j++)
    {
        inside_loop = 1;
        if(strcmp(red_arr1[j],"<") == 0)
        {
            // printf("red -> %s\n",red_arr[j+1]);
            int org;
            org = dup(0);
            char** args;
            args = (char**)malloc(sizeof(char) * 1000 * 100);
            char **fin_temp = (char**)malloc(sizeof(char) * 1000 * 100); 
            int ind = 0;
            fin_temp = get_array(red_arr[j],fin_temp);
            args = get_args(fin_temp,args,i);
            int k = 0;
            while(args[i]!=NULL)
            {
                // printf("args[%d] -> %s\n",i,args[i]);
                i++;
            }
            // printf("args[%d] -> %s\n",i,args[i]);
            int forkReturn = -1;
            if(flg)
                forkReturn=fork();
            if(strcmp(args[i-1],"&") != 0)
            {
                // printf("hlo\n");
                if(forkReturn == 0 || flg == 0)
                {
                    // printf("file = %s\n",red_arr[j+1]);
                    int fd = open(red_arr[j+1], O_RDONLY, 0644);
                    dup2(fd,STDIN_FILENO);
                    int fd2[100], fd2_cnt = 0;
                    // printf("red -> %d\n",cnt);
                    while(j < cnt && cnt != 1)
                    {
                        j++;
                        // printf("red -> %d\n",j);
                        if(strcmp(red_arr1[j],">") == 0)
                        {
                            // printf("red1 -> %s\n",red_arr[j+1]);
                            fd2[fd2_cnt] = open(red_arr[j+1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
                            dup2(fd2[fd2_cnt],STDOUT_FILENO);
                            close(fd2[fd2_cnt]);
                            fd2_cnt++;
                        }  
                        else if(strcmp(red_arr1[j],"<") == 0)
                        {
                            fd2[fd2_cnt] = open(red_arr[j+1], O_RDONLY, 0644);
                            if(fd2[fd2_cnt] < 0)
                            {
                                printf("File does not exist\n");
                                // sys_info(getcwd(mainpath, 1000), homepath);
                                return;

                            }
                            dup2(fd2[fd2_cnt],STDIN_FILENO);
                            close(fd2[fd2_cnt]);
                            fd2_cnt++;
                        }
                        else if(strcmp(red_arr1[j],">>") == 0)
                        {
                            fd2[fd2_cnt] = open(red_arr[j+1], O_CREAT | O_RDWR | O_APPEND, 0644);
                            dup2(fd2[fd2_cnt],STDOUT_FILENO);
                            close(fd2[fd2_cnt]);
                            fd2_cnt++;
                        }
                    }
                    // perror("hli hi\n");
                    // int fd2 = open("g.txt", O_CREAT|O_RDWR, 0644);
                    // dup2(fd2,STDOUT_FILENO);
                    close(fd);
                    execvp(args[0],args);
                }
                else
                {
                    wait(NULL);
                    // printf("Reach here\n");
                }
                break;
            }
            else
            {
                args[i-1] = NULL;
                // char* as[] = {"cat"};
                if(forkReturn == 0 || flg == 0)
                {
                    printf("%d\n",getpid()); 
                    setpgid(0,0);  
                    execvp(args[0],args);
                }
                sleep(1);
            }
            // dup2(org,STDIN_FILENO);
        }
        else if(strcmp(red_arr1[j],">") == 0)
        {
            // printf("red -> %s\n",red_arr[j+1]);
            
            int org;
            org = dup(1);
            char** args;
            args = (char**)malloc(sizeof(char) * 1000 * 100);
            char **fin_temp = (char**)malloc(sizeof(char) * 1000 * 100); 
            int ind = 0;
            fin_temp = get_array(red_arr[j],fin_temp);
            args = get_args(fin_temp,args,i);
            int k = 0;
            while(args[i]!=NULL)
            {
                // printf("args[%d] -> %s\n",i,args[i]);
                i++;
            }
            // printf("args[%d] -> %s\n",i,args[i]);
            int forkReturn = -1;
            if(flg)
                forkReturn=fork();
            if(strcmp(args[i-1],"&") != 0)
            {
                // printf("hlo\n");
                if(forkReturn == 0 || flg == 0)
                {
                    int fd = open(red_arr[j+1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
                    dup2(fd,STDOUT_FILENO);
                    int fd2[100], fd2_cnt = 0;
                    // printf("red -> %d\n",cnt);
                    while(j < cnt)
                    {
                        j++;
                        // printf("red -> %d\n",j);
                        if(strcmp(red_arr1[j],">") == 0)
                        {
                            // printf("red1 -> %s\n",red_arr[j+1]);
                            fd2[fd2_cnt] = open(red_arr[j+1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
                            dup2(fd2[fd2_cnt],STDOUT_FILENO);
                            close(fd2[fd2_cnt]);
                            fd2_cnt++;
                        }  
                        else if(strcmp(red_arr1[j],"<") == 0)
                        {
                            fd2[fd2_cnt] = open(red_arr[j+1], O_RDONLY, 0644);
                            dup2(fd2[fd2_cnt],STDIN_FILENO);
                            close(fd2[fd2_cnt]);
                            fd2_cnt++;
                        }
                        else if(strcmp(red_arr1[j],">>") == 0)
                        {
                            fd2[fd2_cnt] = open(red_arr[j+1], O_CREAT | O_RDWR | O_APPEND, 0644);
                            dup2(fd2[fd2_cnt],STDOUT_FILENO);
                            close(fd2[fd2_cnt]);
                            fd2_cnt++;
                        }
                    }
                    // perror("hli hi\n");
                    // int fd2 = open("g.txt", O_CREAT|O_RDWR, 0644);
                    // dup2(fd2,STDOUT_FILENO);
                    close(fd);
                    execvp(args[0],args);
                }
                else
                {
                    wait(NULL);
                }
                break;
            }
            else
            {
                args[i-1] = NULL;
                // char* as[] = {"cat"};
                if(forkReturn == 0 || flg == 0)
                {
                    printf("%d\n",getpid()); 
                    setpgid(0,0);  
                    execvp(args[0],args);
                }
                sleep(1);
            }
            // dup2(org,STDOUT_FILENO);
        }
        else if(strcmp(red_arr1[j],">>") == 0)
        {
            
            int org;
            org = dup(1);
            char** args;
            args = (char**)malloc(sizeof(char) * 1000 * 100);
            char **fin_temp = (char**)malloc(sizeof(char) * 1000 * 100); 
            int ind = 0;
            fin_temp = get_array(red_arr[j],fin_temp);
            args = get_args(fin_temp,args,i);
            int k = 0;
            while(args[i]!=NULL)
            {
                // printf("args[%d] -> %s\n",i,args[i]);
                i++;
            }
            // printf("args[%d] -> %s\n",i,args[i]);
            int forkReturn = -1;
            if(flg)
                forkReturn=fork();
            if(strcmp(args[i-1],"&") != 0)
            {
                // printf("hlo\n");
                if(forkReturn == 0 || flg == 0)
                {
                    int fd = open(red_arr[j+1], O_CREAT | O_RDWR | O_APPEND, 0644);
                    dup2(fd,STDOUT_FILENO);
                    int fd2[100], fd2_cnt = 0;
                    // printf("red -> %d\n",cnt);
                    while(j < cnt)
                    {
                        j++;
                        // printf("red -> %d\n",j);
                        if(strcmp(red_arr1[j],">") == 0)
                        {
                            // printf("red1 -> %s\n",red_arr[j+1]);
                            fd2[fd2_cnt] = open(red_arr[j+1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
                            dup2(fd2[fd2_cnt],STDOUT_FILENO);
                            close(fd2[fd2_cnt]);
                            fd2_cnt++;
                        }  
                        else if(strcmp(red_arr1[j],"<") == 0)
                        {
                            fd2[fd2_cnt] = open(red_arr[j+1], O_RDONLY, 0644);
                            dup2(fd2[fd2_cnt],STDIN_FILENO);
                            close(fd2[fd2_cnt]);
                            fd2_cnt++;
                        }
                        else if(strcmp(red_arr1[j],">>") == 0)
                        {
                            fd2[fd2_cnt] = open(red_arr[j+1], O_CREAT | O_RDWR | O_APPEND, 0644);
                            dup2(fd2[fd2_cnt],STDOUT_FILENO);
                            close(fd2[fd2_cnt]);
                            fd2_cnt++;
                        }
                    }
                    // perror("hli hi\n");
                    // int fd2 = open("g.txt", O_CREAT|O_RDWR, 0644);
                    // dup2(fd2,STDOUT_FILENO);
                    close(fd);
                    // printf("hi\n");
                    execvp(args[0],args);
                }
                else
                {
                    wait(NULL);
                }
                break;
            }
            else
            {

                args[i-1] = NULL;
                // char* as[] = {"cat"};
                if(forkReturn == 0 || flg == 0)
                {
                    printf("%d\n",getpid()); 
                    setpgid(0,0);  
                    execvp(args[0],args);
                }
                sleep(1);
            }
        }
    }
    if(!inside_loop)
    {
        char** args;
        args = (char**)malloc(sizeof(char) * 1000 * 100);
        args = get_args(fin1,args,i);
        int k = 0;
        while(args[i]!=NULL)
        {
            i++;
        }
        int forkReturn = -1;
        if(flg)
            forkReturn = fork();
            // printf("fork here now = %d\n",forkReturn);
        if(strcmp(args[i-1],"&") != 0)
        {
            fg_proc = forkReturn;
            // printf("hlo\n");
            if(forkReturn == 0 || flg == 0)
            {
                // if(flg)
                    setpgid(0, 0);
                    // tcsetpgrp(STDIN_FILENO,0);
                    execvp(args[0],args);
                // else
                //     execvp(fin1[0],fin1);
            }
            else
            {

                signal(SIGTTIN, SIG_IGN);
                signal(SIGTTOU, SIG_IGN);
                // TODO: Error handling here
                setpgid(forkReturn, 0);
                tcsetpgrp(STDIN_FILENO, forkReturn);

                int w_st;
                waitpid(-1, &w_st, WUNTRACED);

                tcsetpgrp(STDIN_FILENO, getpgrp());

                signal(SIGTTIN, SIG_DFL);
                signal(SIGTTOU, SIG_DFL);
                
                if (WIFSTOPPED(w_st)) {
                    details(args,forkReturn,id++);
                    // sort_details();
                    // IT WAS STOPPED, NOT TERMINATED
                    // int child_id = store_process(FG_CHILD_PID, FG_CHILD_PNAME);
                    // printf("[%d] %s %d suspended\n", child_id, FG_CHILD_PNAME, FG_CHILD_PID);
                }
            }
        }
        else if(strcmp(args[i-1],"&")== 0)
        {
            int send_id = max(id,maxi);
            // printf("s_id -> %d\nid -> %d",send_id,id);
            if(send_id < maxi)
                details(args,forkReturn,id++);
            else{
                while(id <= maxi)
                    id++;
                details(args,forkReturn,id++);
            }
            if(flg)
                args[i-1] = NULL;
            if(forkReturn == 0 || flg == 0)
            {
                printf("%d\n",getpid()); 
                setpgid(0,0);  
                // if(flg)
                    execvp(args[0],args);
                // else
                //     execvp(fin1[0],fin1);
            }
            sleep(1);
        }
    }
}
int prompt(char arr[1000],char homepath[1000], char prevpath[1000][900], int curr, int shell_id) 
{
    shellpid = shell_id;

    struct utsname uts;
    uname(&uts);
    char *buf;
    char prev_temp[1000], mainpath[1000];
    if(strcmp(arr,"\n") == 0)
    {
        sys_info(getcwd(mainpath, 1000), homepath);
        return curr;
    }
    getcwd(prev_temp,1000);
    buf=(char *)malloc(10*sizeof(char));
    getlogin_r(buf,10);
    // char* semi = strtok(a,";");
    int count = 0;
    for(int i = 0; i < strlen(arr); i++)
    {
        if(arr[i] == ';')
            count++;
    }
    char temp_arr[1000][900] = {};
    char *divi = strtok(arr,";");
    int i = 0;
    char history_path[1000] = "";
    strcpy(history_path,homepath);
    strcat(history_path,"/history.txt");
    while(divi != NULL )
    {
        strcat(temp_arr[i],divi); 
        divi = strtok(NULL, ";");
        i++;
    }
    temp_arr[count][strlen(temp_arr[count]) - 1] = '\0';
    int ans = 0;
    char **all_history = (char**)malloc(sizeof(char) * 1000 * 100); 
    all_history = store_history(arr,history_path);
    for(int j = 0; j <= count; j++)
    {        
        flag = -1;
        // strcpy(temp_arr[j],arr);
        char str[1000] = "", str1[1000] = "", path[1000];
        removing_space(str1,temp_arr[j],"\t");
        removing_space(str,str1," ");
        char** fin;
        fin = (char**)malloc(sizeof(char) * 1000 * 100);
        char a[1000],b[1000];
        int idx = 0;
        strcpy(a,str);
        strcpy(b,a);
        int len_fin1 = 0;
        char** fin1 = get_array(b,fin);
        for(int i = 0; ; i++)
        {
            if(fin1[i] == NULL)
                break;
            len_fin1++;
        }            
        int tot_pipes = 0;
        for(int i = 0; i < len_fin1; i++)
        {
            if(strcmp(fin1[i],"|") == 0)
                tot_pipes++; 
        }
        int cd_len = strlen(a);
        char* token = strtok(str, " ");
        if(tot_pipes > 0)
        {
            char pipe_cd[100][100][100] = {};
            int itr1 = 0,itr2 = 0,temp_tot = 0,len_arr[1000];
            for(int i = 0; i < len_fin1; i++)
            {
                if(strcmp(fin1[i],"|") == 0)
                {
                    len_arr[itr1] = itr2;
                    // printf("len_arr[%d] -. %d",itr1,itr2);
                    itr1++;
                    itr2 = 0;
                    temp_tot++;
                    continue;
                }
                if(temp_tot == tot_pipes && itr2 == 0)
                {
                    itr2 = 0;
                }
                // perror("");
                strcat(pipe_cd[itr1][itr2],fin1[i]); 
                // printf("pipe_cd[%d][%d] -> %s\n",itr1,itr2,pipe_cd[itr1][itr2]);
                itr2++;
            }
            len_arr[itr1] = itr2;
            // printf("len_arr[%d] -. %d",itr1,itr2);
            int fd = dup(0);
            int std_in = dup(0);
            int std_out = dup(1);
            int fdarr[2];
            int cnt = 0;
            // int l1 = len_arr[itr1];
            // printf("len -> %d\n",len_arr[0]);
            char** args = (char**)malloc(sizeof(char)*100*100);
            for(int i = 0; i <= itr1; i++)
            {
                pipe(fdarr);
                int fork_output = fork();
                if(fork_output==0)
                {
                    close(fdarr[0]);
                    dup2(fd,STDIN_FILENO);
                    dup2(fdarr[1],STDOUT_FILENO);
                    if(strcmp(pipe_cd[i][0],"ls") == 0)
                    {
                        args = exec_arr(pipe_cd,args,len_arr[i],i);
                        // printf("Enter here\n");
                        command_ls(args,homepath,0);
                        // execvp(args[0],args);
                        // for(int j=0;j<=5;j++)
                        // {
                        //     printf("%d\n",j);
                        // }
                        // printf("after execution\n");
                        // execvp(arr1[0],arr1);
                        exit(0);
                    }
                    else if(strcmp(pipe_cd[i][0],"echo") == 0)
                    {
                        args = exec_arr(pipe_cd,args,len_arr[i],i);
                        command_echo(args,0);
                        exit(0);
                    }
                    else if(strcmp(pipe_cd[i][0],"pwd") == 0)
                    {
                        args = exec_arr(pipe_cd,args,len_arr[i],i);
                        command_pwd(args);
                        exit(0);
                    }
                    else if(strcmp(pipe_cd[i][0],"pinfo") == 0)
                    {
                        args = exec_arr(pipe_cd,args,len_arr[i],i);
                        int val = pinfo(args,len_arr[i],idx,path,homepath,mainpath,curr,1,-1,1);
                        // perror("hi");
                        // printf("val -> %d\n",val);
                        if(val != 0)
                        {
                            dup2(std_out,STDOUT_FILENO);
                            sys_info(getcwd(mainpath, 1000), homepath);
                            return curr;
                        }
                        exit(0);
                    }
                    else if((strcmp(pipe_cd[i][0],"history") == 0))
                    {
                        args = exec_arr(pipe_cd,args,len_arr[i],i);
                        // for(int k = 0; k <= len_arr[i]; k++)
                        // {
                        //     printf("args[%d] -> %s\n",k,args[k]);
                        // }
                        ini_history(args, len_arr[i], all_history,0);
                        exit(0);
                    }
                    else
                    {
                        if(i == itr1)
                        {
                            // printf("hi\n");
                            dup2(std_out,STDOUT_FILENO);
                            close(fdarr[1]);
                        }
                        args = exec_arr(pipe_cd,args,len_arr[i],i);
                        // for(int k = 0; k <= len_arr[i]; k++)
                        // {
                        //     printf("args[%d] -> %s\n",k,args[k]);
                        // }
                        char inp[10000];
                        command_exec(args,0,0);
                        // execvp(args[0],args);
                        if(i != itr1)
                            exit(0);
                        close(fdarr[1]);
                    }
                }
                else
                {
                    close(fdarr[1]);
                    wait(NULL);
                    // printf("return\n");
                    dup2(fdarr[0],fd);
                    
                }
            }
        }
        else if(strcmp(fin1[0],"ls") == 0)
        {
            command_ls(fin1,homepath,0);     
        }
        else if(strcmp(fin1[idx],"cd") == 0)
        {
            // perror("hi\n");
            command_cd(fin1,homepath,prevpath,curr,0); 
            strcpy(prevpath[curr],getcwd(prev_temp,1000));
            curr++;
        }
        else if(strcmp(fin1[idx],"echo") == 0)
        {
            command_echo(fin1,0);
        }
        else if(strcmp(fin1[idx],"pwd") == 0)
        {
            command_pwd(fin1);
        }
        else if(strcmp(fin1[idx],"pinfo") == 0)
        {
            int val = pinfo(fin1,len_fin1,idx,path,homepath,mainpath,curr,1,-1,0);
            if(val != 0)
            {
                sys_info(getcwd(mainpath, 1000), homepath);
                return curr;
            }
        }
        else if(strcmp(fin1[idx], "repeat") == 0)
        {
            int val = repeat(fin1,len_fin1,idx,homepath,prevpath,curr);
            if(val != 0)
            {
                sys_info(getcwd(mainpath, 1000), homepath);
                return curr;
            }
        }
        else if(strcmp(fin1[idx],"history") == 0)
        {
            // printf("fin1[%d] -> %s\n",idx,fin1[idx]);
            ini_history(fin1, len_fin1, all_history,idx);
        }
        else if(strcmp(fin1[idx],"jobs") == 0)
        {
            sort_details();
            idx++;
            if(fin1[idx] == NULL)
            {
                for(int itr1 = 1; itr1 < id; itr1++)
                {
                    int val = pinfo(fin1,len_fin1,idx,path,homepath,mainpath,curr,0,list[itr1].pid,0);
                    if(val == 1)
                    {
                        printf("Running ");
                        printf("[%d] %s [%d]\n",list[itr1].id1,list[itr1].name,list[itr1].pid);
                    }
                    else if(val == 0)
                    {
                        printf("Stopped ");
                        printf("[%d] %s [%d]\n",list[itr1].id1,list[itr1].name,list[itr1].pid);
                    }
                    // printf("val -> %d\n",val);
                }
            }
            else if(strcmp(fin1[idx],"-r") == 0)
            {
                for(int itr1 = 1; itr1 < id; itr1++)
                {
                    int val = pinfo(fin1,len_fin1,idx,path,homepath,mainpath,curr,0,list[itr1].pid,0);
                    if(val == 1)
                        printf("[%d] Running %s [%d]\n",list[itr1].id1,list[itr1].name,list[itr1].pid);
                }
            }
            else if(strcmp(fin1[idx],"-s") == 0)
            {
                for(int itr1 = 1; itr1 < id; itr1++)
                {
                    int val = pinfo(fin1,len_fin1,idx,path,homepath,mainpath,curr,0,list[itr1].pid,0);
                    // printf("id -> %d\n",id);
                    if(val == 0)
                    {
                        // printf("val -> %d\n",val);
                        printf("[%d] Stopped %s [%d]\n",list[itr1].id1,list[itr1].name,list[itr1].pid);
                    }
                }
            }
        }
        else if(strcmp(fin1[idx],"sig") == 0)
        {
            if(len_fin1 < 3)
            {
                printf("Wrong Format\n");
                sys_info(getcwd(mainpath, 1000), homepath);
                return curr;
            }
            idx++;
            int process_num = atoi(fin1[idx]), process_id = -1,proc_index;
            for(int itr1 = 1; itr1 < id; itr1++)
            {
                if(list[itr1].id1 == process_num)
                {
                    proc_index = itr1;
                    process_id = list[itr1].pid;
                }
            }
            if(process_id == -1)
            {
                printf("Could not find the process to kill\n");
                sys_info(getcwd(mainpath, 1000), homepath);
                return curr;
            }
            idx++;
            int sig_name = atoi(fin1[idx]);
            // printf("proc_id = %d\n sig_id = %d",process_id,sig_name);
            removing_process(process_num,proc_index);
            kill(process_id,sig_name);
        }
        else if(strcmp(fin1[idx],"fg") == 0)
        {
            idx++;
            int job_num = atoi(fin1[idx]),child_pid;
            char pname[1000];
            for(int itr1 = 0; itr1 < id; itr1++)
            {
                if(list[itr1].id1 == job_num)
                {
                    child_pid = list[itr1].pid;
                    strcpy(pname,list[itr1].name);
                }
            }
            printf("Brings [%d] %s to the foreground\n", job_num, pname);
            int w_st;
            signal(SIGTTIN, SIG_IGN);
            signal(SIGTTOU, SIG_IGN);
            tcsetpgrp(STDIN_FILENO, child_pid);
            kill(child_pid, SIGCONT);
            waitpid(child_pid, &w_st, WUNTRACED);
            tcsetpgrp(STDIN_FILENO, getpgrp());
            signal(SIGTTIN, SIG_DFL);
            signal(SIGTTOU, SIG_DFL);

        }
        else if(strcmp(fin1[idx],"bg") == 0)
        {
            idx++;
            int job_num = atoi(fin1[idx]),child_pid;
            char pname[1000];
            for(int itr1 = 0; itr1 < id; itr1++)
            {
                if(list[itr1].id1 == job_num)
                {
                    child_pid = list[itr1].pid;
                    strcpy(pname,list[itr1].name);
                }
            }
            // printf("ch -> %d\n",child_pid);
            if (kill(child_pid, SIGCONT) < 0) {
                perror("Could not run background process");
            }
            else
                printf("Changes the state of [%d] %s to running(in the # background)\n", job_num,pname);
        }
        else if(strcmp(fin1[idx],"baywatch") == 0)
        {
            int temp = atoi(fin1[2]),time1 = 10;
            // printf("temp -> %d",temp);
            if(strcmp(fin1[3],"interrupt") == 0)
            {
                char proc[1000] = "/proc/interrupts",inp[1000] = "";
                FILE* fd;
                for(int itr1 = 0; itr1 <= 7; itr1++)
                    printf("CPU%d\t",itr1);
                printf("\n");
                while(1)
                {
                    char c;
                    sleep(temp);
                    if(input_taking())
                    {
                        c = getc(stdin);
                    }
                    fd = fopen(proc,"r");
                    fgets(inp,1000,fd);
                    for(int i = 0; i <=16; i++ )
                    {
                        fscanf(fd,"%s",inp);
                    }
                    for(int i = 0; i <=7; i++ )
                    {
                        fscanf(fd,"%s",inp);
                        printf("%s\t",inp);
                    }
                    printf("\n");
                    // printf("c-> %c\n",c);
                    if(c == 'q')
                    {
                        // sys_info(getcwd(mainpath, 1000), homepath);
                        return curr;
                    }
                }
            }
            else if(strcmp(fin1[3],"newborn") == 0)
            {
                char proc[1000] = "/proc/loadavg",inp[1000] = "";
                FILE* fd;
                while(1)
                {
                    char c;
                    sleep(temp);
                    if(input_taking())
                    {
                        c = getc(stdin);
                    }
                    fd = fopen(proc,"r");
                    fgets(inp,1000,fd);
                    int itr = 0;
                    char* token = strtok(inp," ");
                    
                    char *token1 = (char *)malloc(sizeof(char)*1000);
                    while(token!=NULL)
                    {
                        token1 = token;
                        token = strtok(NULL," ");
                    }
                    printf("%s",token1);
                    // }
                    // printf("\n");
                    // printf("c-> %c\n",c);
                    if(c == 'q')
                    {
                        // sys_info(getcwd(mainpath, 1000), homepath);
                        return curr;
                    }
                }
            }
            else if(strcmp(fin1[3],"dirty") == 0)
            {
                char proc[1000] = "/proc/meminfo",inp[1000] = "";
                FILE* fd;
                while(1)
                {
                    // printf("hi\n");
                    char c;
                    sleep(temp);
                    if(input_taking())
                    {
                        c = getc(stdin);
                    }
                    fd = fopen(proc,"r");
                    fgets(inp,1000,fd);
                    while(1)
                    {
                        fscanf(fd,"%s",inp);
                        if(strcmp(inp,"Dirty:") == 0)
                            break;
                    }
                    fscanf(fd,"%s",inp);
                    printf("%s\t",inp);
                    fscanf(fd,"%s",inp);
                    printf("%s\t",inp);
                    printf("\n");
                    // printf("c-> %c\n",c);
                    if(c == 'q')
                    {
                        // sys_info(getcwd(mainpath, 1000), homepath);
                        return curr;
                    }
                }
            }
        }
        else if(strcmp(fin1[idx],"replay") == 0)
        {
            int interval,period,temp_itr = 0;
            char** temp_fin = (char**)malloc(sizeof(char)*100*100);
            for(int itr1 = 0; itr1 < len_fin1; itr1++)
            {
                if(strcmp(fin1[itr1],"-command") == 0)
                {
                    itr1++;
                    while(1)
                    {
                        temp_fin[temp_itr] = (char*)malloc(sizeof(char)*100);
                        stpcpy(temp_fin[temp_itr],fin1[itr1]);
                        temp_itr++;
                        if(strcmp(fin1[itr1+1],"-interval") == 0)
                            break;
                        itr1++;
                    }
                }
                else if(strcmp(fin1[itr1],"-interval") == 0)
                {
                    itr1++;
                    interval = atoi(fin1[itr1]);
                }
                else if(strcmp(fin1[itr1],"-period") == 0)
                {
                    // printf("fin1[i] -> ",itr1,fin1[i])
                    itr1++;
                    period = atoi(fin1[itr1]);
                }
            }
            // printf("temp -> %d\n",temp_itr);
            temp_fin[temp_itr] = NULL;
            temp_itr++;
            // printf("interval -> %d\nperiod -> %d\n",interval,period);

            // for(int itr1 = 0; itr1 < temp_itr; itr1++)
                // printf("temp_fin[%d] -> %s\n",itr1,temp_fin[itr1]);
            // printf("hi\n");
            if(strcmp(temp_fin[0], "cd") == 0)
            {
                
                for(int i = 0;i < period/interval; i++)
                {
                    command_cd(temp_fin,homepath,prevpath,curr,0);
                }
            }
            else if(strcmp(temp_fin[0], "echo") == 0)
            {
                int l;
                // perror("hi");
                for(int i = 0; i < period/interval; i++)
                {
                    sleep(interval);
                    command_echo(temp_fin,0);
                }
            }
            else if(strcmp(temp_fin[0], "ls") == 0)
            {
                for(int i = 0;i < period/interval ; i++)
                {
                    sleep(interval);
                    command_ls(temp_fin,homepath,0);
                }
            }
            else if(strcmp(temp_fin[0], "pwd") == 0)
            {
                for(int i = 0;i < period/interval ; i++)
                {
                    sleep(interval);
                    command_pwd(temp_fin);
                }
            }
            else if(strcmp(temp_fin[0],"pinfo") == 0)
            {
                for(int i = 0;i < period/interval ; i++)
                {
                    sleep(interval);
                    int val = pinfo(temp_fin,temp_itr,0,path,homepath,mainpath,curr,1,-1,1);
                    if(val != 0)
                    {
                        sys_info(getcwd(mainpath, 1000), homepath);
                        return curr;
                    }
                }
            }
            else
            {
                for(int i = 0;i < period/interval ; i++)
                {
                    sleep(interval);
                    command_exec(temp_fin,0,1);   
                }
            }
        }
        else
        {
            flag = -1;
            command_exec(fin1,0,1);            
        }
    }
    signal(SIGCHLD,handle_signal);
    signal(SIGINT,handle_signal);
    signal(SIGTSTP,handle_ctrlz);
    if(flag == -1)
        sys_info(getcwd(mainpath, 1000), homepath);
    else
    {
        sleep(1);
        sys_info(getcwd(mainpath, 1000), homepath);
    }
    return curr;
}
