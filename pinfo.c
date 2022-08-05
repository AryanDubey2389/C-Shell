#include "prompt.h"
#include "headers.h"
int pinfo(char** fin1, int len_fin1, int idx, char path[1000],char homepath[1000], char mainpath[1000], int curr, int jobs, int job_id, int ppe)
{
    // printf("fin[0] -> %s\n",fin1[0]);
    // printf("fin[1] -> %s\n",fin1[1]);
    int itr, flg1 = -1,j = 0;
    // printf("len -> %d\n",len_fin1);
    // // {
        // printf("fin1[%d] -> %s\n",j,fin1[j]);
    if(!ppe)
    {
        for(int j = 0; j < len_fin1;j++)
        {
            // printf("fin1[%d] -> %s\n",j,fin1[j]);
            if(strcmp(fin1[j],">") == 0)
            {
                itr = j;
                flg1 = 0; 
            }
            if(strcmp(fin1[j],"<") == 0)
            {
                itr = j;
                flg1 = 1; 
            }
            else if(strcmp(fin1[j],">>") == 0)
            {
                itr = j;
                flg1 = 2; 
            }
        }
    }
        // perror("hi");
    // }
    // return 1;
    // perror("hlo");
    char curr_path[1000] = "", str[10000] = "";
    int pid1;
    // perror("fin[0] ->");
    // perror("fin[1] ->");
    getcwd(path,1000);
    strcpy(curr_path,path);

    if(len_fin1 == 1 || flg1 != -1)
       pid1 = getpid();
    else
       pid1 = atoi(fin1[1]); 
    if(!jobs)
    {
        // printf("ji\n");
        pid1 = job_id;
    }
    // printf("pid1 -> %d\n",pid1);
    // printf("jobid -> %d\n",job_id);
    // perror("hi");

    char proc[1000] = "/proc/",pid_string[1000] = "", buf[10000] = "";
    sprintf(pid_string,"%d",pid1);
    strcat(proc,pid_string);
    // printf("proc -> %s\n",proc);
    DIR* d = opendir(proc);
    if(d == NULL)
    {   
        // perror("");
        if(jobs)
            printf("The process with pid %d is not found\n",pid1);
        chdir(curr_path);
        // closedir(d);
        return -1;
    }
    int fd1;
    char filename[1000] = "";
    if(flg1!=-1)
    {
        fd1 = (flg1 !=2) ? open(fin1[itr+1], O_WRONLY | O_CREAT | O_TRUNC, 0644) : open(fin1[itr+1], O_CREAT | O_RDWR | O_APPEND, 0644);
        strcpy(filename,fin1[itr+1]);
    }
    int fd5 = open(filename,O_RDONLY);

    char temp_proc[1000] = "";
    strcpy(temp_proc,proc);
    chdir(proc);
    char pid_status[1000][900] = {};
    FILE* fd = fopen("status","r");
    int temp_flg = 0;
    int cnt1 = 0;
    while(1)
    {
        // printf("hi\n");
        fscanf(fd,"%s",pid_status[cnt1]);
        if(strcmp(pid_status[cnt1],"VmSize:") == 0)
        {
            temp_flg = 1;
            break;
        }
        cnt1++;
        if(cnt1 > 200)
            break;
    }
    if(temp_flg == 0)
    {
        if(jobs)
            printf("The process with pid %d is not found\n",pid1);
        chdir(curr_path);
        return -1;
    }
    
    if(flg1 == 0)
    {
        
        int org;
        org = dup(0);
        dup2(fd1,STDOUT_FILENO);
        // if(<0)
        // {
        //     printf("Failed to duplicate file descriptor\n");
        // }
        close(fd1);
            printf("pid -- %d\n",pid1);
        fscanf(fd,"%s",pid_status[++cnt1]);
            printf("memory -> %s ",pid_status[cnt1]);
        fscanf(fd,"%s",pid_status[++cnt1]);
            printf("%s\n",pid_status[cnt1]);
        int first, proc_stat[1000];
        char second[1000];
        char third;
        FILE* fd_in = fopen("./stat","r"); 
        fscanf(fd_in,"%d %s %c",&first,second,&third);
        for(int i = 4; i <=8; i++ )
        {
            fscanf(fd_in,"%d",&proc_stat[i]);
        }
        
        FILE* fd_in1 = fopen("./exe","r");
        readlink("./exe", buf, 10000);
        char int_path[1000];
        strcpy(int_path,rel_path(buf,homepath,int_path));
            printf("Executible Path -> %s\n",int_path);
            printf("Process Status -> %c",third);
        if(proc_stat[5] == proc_stat[8])
            printf("+\n");
        else
            printf("\n");
        chdir(curr_path);
        dup2(org,STDOUT_FILENO);
    }
    else if(flg1 == 1)
    {
        // printf("file -> %s\n",filename);
        
        if(fd5 < 0)
        {
            printf("File not found\n");
            chdir(curr_path);
            return -1;
        }
        if(jobs)
            printf("pid -- %d\n",pid1);
        fscanf(fd,"%s",pid_status[++cnt1]);
        if(jobs)
            printf("memory -> %s ",pid_status[cnt1]);
        fscanf(fd,"%s",pid_status[++cnt1]);
        if(jobs)
            printf("%s\n",pid_status[cnt1]);
        int first, proc_stat[1000];
        char second[1000];
        char third;
        FILE* fd_in = fopen("./stat","r"); 
        fscanf(fd_in,"%d %s %c",&first,second,&third);
        for(int i = 4; i <=8; i++ )
        {
            fscanf(fd_in,"%d",&proc_stat[i]);
        }
        
        FILE* fd_in1 = fopen("./exe","r");
        readlink("./exe", buf, 10000);
        char int_path[1000];
        strcpy(int_path,rel_path(buf,homepath,int_path));
        if(jobs)
            printf("Executible Path -> %s\n",int_path);
        if(jobs)
            printf("Process Status -> %c",third);
        if(!jobs)
        {
            chdir(curr_path);
            if(third == 'R')
                return 1;
            else
                return 0;
        }
        if(proc_stat[5] == proc_stat[8])
            printf("+\n");
        else
            printf("\n");
        chdir(curr_path);
    }
    else if(flg1 == 2)
    {
        int org;
        org = dup(0);
        dup2(fd1,STDOUT_FILENO);
        close(fd1);
        printf("pid -- %d\n",pid1);
        fscanf(fd,"%s",pid_status[++cnt1]);
        printf("memory -> %s ",pid_status[cnt1]);
        fscanf(fd,"%s",pid_status[++cnt1]);
        printf("%s\n",pid_status[cnt1]);
        int first, proc_stat[1000];
        char second[1000];
        char third;
        FILE* fd_in = fopen("./stat","r"); 
        fscanf(fd_in,"%d %s %c",&first,second,&third);
        for(int i = 4; i <=8; i++ )
        {
            fscanf(fd_in,"%d",&proc_stat[i]);
        }
        
        FILE* fd_in1 = fopen("./exe","r");
        readlink("./exe", buf, 10000);
        char int_path[1000];
        strcpy(int_path,rel_path(buf,homepath,int_path));
        printf("Executible Path -> %s\n",int_path);
        printf("Process Status -> %c",third);
        if(proc_stat[5] == proc_stat[8])
            printf("+\n");
        else
            printf("\n");
        chdir(curr_path);
        dup2(org,STDOUT_FILENO);
    }
    else if(flg1 == -1)
    {
        // printf("jobs -> %d\n",jobs);
        if(jobs)
            printf("pid -- %d\n",pid1);
        fscanf(fd,"%s",pid_status[++cnt1]);
        if(jobs)
            printf("memory -> %s ",pid_status[cnt1]);
        fscanf(fd,"%s",pid_status[++cnt1]);
        if(jobs)
            printf("%s\n",pid_status[cnt1]);
        int first, proc_stat[1000];
        char second[1000];
        char third;
        FILE* fd_in = fopen("./stat","r"); 
        fscanf(fd_in,"%d %s %c",&first,second,&third);
        for(int i = 4; i <=8; i++ )
        {
            fscanf(fd_in,"%d",&proc_stat[i]);
        }
        
        FILE* fd_in1 = fopen("./exe","r");
        readlink("./exe", buf, 10000);
        char int_path[1000];
        strcpy(int_path,rel_path(buf,homepath,int_path));
        if(jobs)
            printf("Executible Path -> %s\n",int_path);
        if(jobs)
            printf("Process Status -> %c",third);
        if(!jobs)
        {
            chdir(curr_path);
            if(third == 'T')
                return 0;
            else
                return 1;
        }
        if(proc_stat[5] == proc_stat[8])
            printf("+\n");
        else
            printf("\n");
        chdir(curr_path);
    }
    return 0;
}