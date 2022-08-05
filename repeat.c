#include "prompt.h"
#include "headers.h"
int repeat(char** fin1,int len_fin1,int idx,char homepath[1000], char prevpath[1000][900], int curr)
{
     int itr, flg1 = -1;
    for(int j = 0; j < len_fin1; j++)
    {
        // printf("fin1[%d] -> %s\n",j,fin1[j]);
        if(strcmp(fin1[j],">") == 0)
        {
            itr = j;
            flg1 = 0; 
        }
        else if(strcmp(fin1[j],"<") == 0)
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
    if(flg1 == 0)
    {
        int fd = open(fin1[itr+1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
        int org;
        org = dup(0);
        dup2(fd,STDOUT_FILENO);
        // if(<0)
        // {
        //     printf("Failed to duplicate file descriptor\n");
        // }
        close(fd);
        int k = 0;
        while(fin1[k]!=NULL)
            k++;            
        if(fin1[idx+1] == NULL)
        {
            printf("Wrong Parameters\n");
            return -1;
        }
        idx++;
        int end_point = atoi(fin1[idx]);
        if((end_point == 0 && fin1[idx][0] != '0'))
        {
            printf("Wrong Parameter\n");
            return -1;
        }
        idx++;
        if(fin1[idx+1] == NULL)
        {
            printf("Wrong Parameter\n");
            return -1;
        }
        else if(strcmp(fin1[idx], "cd") == 0)
        {
            for(int i = 0; i < end_point; i++)
                command_cd(fin1,homepath,prevpath,curr,idx);
        }
        else if(strcmp(fin1[idx], "echo") == 0)
        {
            for(int i = 0; i < end_point; i++)
                command_echo(fin1,idx);
        }
        else if(strcmp(fin1[idx], "ls") == 0)
        {
            for(int i = 0; i < end_point; i++)
                command_ls(fin1,homepath,idx);
        }
        else if(strcmp(fin1[idx], "pwd") == 0)
        {
            for(int i = 0; i < end_point; i++)
                command_pwd(fin1);
        }
        else
        {
            for(int i = 0; i < end_point; i++)
                command_exec(fin1,idx);   
        }
        dup2(org,STDOUT_FILENO);
    }
    else if(flg1 == -1)
    {
        // printf("hi\n");
        int k = 0;
        while(fin1[k]!=NULL)
            k++;            
        if(fin1[idx+1] == NULL)
        {
            printf("Wrong Parameters\n");
            return -1;
        }
        idx++;
        int end_point = atoi(fin1[idx]);
        if((end_point == 0 && fin1[idx][0] != '0'))
        {
            printf("Wrong Parameter\n");
            return -1;
        }
        idx++;
        if(fin1[idx+1] == NULL)
        {
            printf("Wrong Parameter\n");
            return -1;
        }
        else if(strcmp(fin1[idx], "cd") == 0)
        {
            for(int i = 0; i < end_point; i++)
                command_cd(fin1,homepath,prevpath,curr,idx);
        }
        else if(strcmp(fin1[idx], "echo") == 0)
        {
            for(int i = 0; i < end_point; i++)
                command_echo(fin1,idx);
        }
        else if(strcmp(fin1[idx], "ls") == 0)
        {
            for(int i = 0; i < end_point; i++)
                command_ls(fin1,homepath,idx);
        }
        else if(strcmp(fin1[idx], "pwd") == 0)
        {
            for(int i = 0; i < end_point; i++)
                command_pwd(fin1);
        }
        else
        {
            for(int i = 0; i < end_point; i++)
                command_exec(fin1,idx);   
        }
    }
    return 0;
            
}