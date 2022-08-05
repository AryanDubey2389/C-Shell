#include "prompt.h"
#include "headers.h"
void command_cd(char** fin1, char homepath[1000], char prevpath[1000][900], int curr, int idx)
{
    // perror("hlo\n");
    char path[1000] = "";
    idx++;
    int cnt = 0;
    char temp[1000] = "";
    getcwd(path, 1000);
    strcpy(temp,path);
    // printf("fin1[%d] -> %s\n",idx-1,fin1[idx-1]);
    if(idx==1)
    {
        while(fin1[cnt] != NULL)
        {
            cnt++;
        }
    }
    int flg = chdir(fin1[idx]);  
    chdir(temp);
    // printf("flg -> %d\n",flg);
    if(fin1[idx] == NULL || strcmp(fin1[idx],"~") == 0)
    {
        chdir(homepath);
    }
    else if(strcmp(fin1[idx],"-") == 0)
    {
        chdir(prevpath[curr-2]);
        printf("%s\n",prevpath[curr-2]);
    }
    else if(cnt > 2)
    {
        printf("Space Between Path : Wrong Parameters\n");
        chdir(temp);
    }
    else if(flg == 0)
    {
        chdir(fin1[idx]);
    }
    else if(flg != 0)
    {
        perror("");
    }
}