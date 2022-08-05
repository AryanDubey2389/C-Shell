#include "prompt.h"
#include "headers.h"
void ini_history(char** fin1, int len_fin1, char** all_history,int idx)
{
    int itr, flg1 = -1;
    // printf("fin[%d] -> %s\n",idx,fin1[idx]);

    // printf("hi\n");
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
    // printf("fin[%d] -> %s\n",idx,fin1[idx]);
    idx++;       
    // printf("fin[%d] -> %s\n",idx,fin1[idx]);
    if(flg1 == 0)
    {
        int fd = open(fin1[itr+1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
        int org;
        org = dup(0);
        dup2(fd,STDOUT_FILENO);
        if(fin1[idx] == NULL || strcmp(fin1[idx],">") == 0)
        {
            for(int i = 9;i >= 0; i--)
                printf("%s",all_history[i]);
        }
        else
        {
            int end_point = atoi(fin1[idx]);
            for(int i = end_point-1;i >= 0; i--)
                printf("%s",all_history[i]);
        }
        close(fd);
        dup2(org,STDOUT_FILENO);
    }
    else if(flg1 == 1)
    {
        int fd = open(fin1[itr+1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
        int org;
        // org = dup(1);
        // dup2(fd,STDIN_FILENO);
        if(fin1[idx] == NULL || strcmp(fin1[idx],"<") == 0)
        {
            for(int i = 9;i >= 0; i--)
                printf("%s",all_history[i]);
        }
        else
        {
            int end_point = atoi(fin1[idx]);
            for(int i = end_point-1;i >= 0; i--)
                printf("%s",all_history[i]);
        }
        close(fd);
        // dup2(org,STDIN_FILENO);
    }
    else if(flg1 == 2)
    {
        int fd = open(fin1[itr+1], O_CREAT | O_RDWR | O_APPEND, 0644);
        int org;
        org = dup(0);
        dup2(fd,STDOUT_FILENO);
        if(fin1[idx] == NULL || strcmp(fin1[idx],">") == 0)
        {
            for(int i = 9;i >= 0; i--)
                printf("%s",all_history[i]);
        }
        else
        {
            int end_point = atoi(fin1[idx]);
            for(int i = end_point-1;i >= 0; i--)
                printf("%s",all_history[i]);
        }
        close(fd);
        dup2(org,STDOUT_FILENO);
    }
    else if(flg1 == -1)
    {    
        if(fin1[idx] == NULL)
        {
            for(int i = 9;i >= 0; i--)
                printf("%s",all_history[i]);
        }
        else
        {
            int end_point = atoi(fin1[idx]);
            // printf("end -> %d\n",end_point);
            for(int i = end_point - 1;i >= 0; i--)
                printf("%s",all_history[i]);
        }
    }
}