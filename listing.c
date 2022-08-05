#include "prompt.h"
#include "headers.h"
int fin1_len2(char** fin1)
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
void rev(char* str)
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
void listing(char* path, int flg,int k,char** fin1)
{
    struct dirent *direc;
    struct dirent **namelist;
    int len_fin1 = fin1_len2(fin1);  
    int itr;
    int flg1 = -1;
    
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
    // printf("path -> %s\n",path);
    int temp_val = 0;
    if(strcmp(path,">") == 0 || (strcmp(path,"<") == 0 || strcmp(path,">>") == 0))
    {
        temp_val = 1;
        path = ".";
    }
    DIR *dh = opendir(path);
    DIR *dr = opendir(path);
    if(dr == NULL)
    {
        int i,flg = 0,j;
        char split1[1000] = "", split2[1000] = "";
        for(i = strlen(path)-1; i >= 0; i--)
        {
            if(path[i] == '/' && flg == 0)
            {
                j = i;
                flg = 1;
            }
            if(flg == 0)
                split2[strlen(path)-1-i] = path[i];
            else if(flg == 1)
                split1[j-i] = path[i];
        }
        rev(split2);
        rev(split1);
        if(strlen(split1) == 0)
            strcpy(split1,".");
        DIR* dl = opendir(split1);
        struct dirent **namelist1;
        int tester = 0;
        while ((direc = readdir(dl)) != NULL)
        {
            if(strcmp(direc->d_name,split2) == 0)
                tester = 1;
        }
        if(flg1 == 0)
        {
        //     printf("Welcome bro\n");
        //     printf("fin -> %s\n",fin1[itr+1]);
            // printf("%s\n",path);
            int fd = open(fin1[itr+1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
            int org;
            org = dup(0);
            dup2(fd,STDOUT_FILENO);
            // if(<0)
            // {
            //     printf("Failed to duplicate file descriptor\n");
            // }
            close(fd);
            // printf("i -> %d     itr -> %d\n",i,itr);
            // printf("Aryan Dubey");
            if(tester == 1)
                printf("%s\n",path);
            else
            {
                if(dl == NULL)
                    printf("Wrong Directory\n");
                else
                    printf("Wrong File Name\n");
            }
            dup2(org,STDOUT_FILENO);
        }
        else if(flg1 == 1)
        {
            int fd = open(fin1[itr+1], O_RDONLY);
            int org;
            // org = dup(0);
            // dup2(fd,STDOUT_FILENO);
            if(fd<0)
            {
                printf("File does not exist\n");
                return;
            }
            close(fd);
            // printf("i -> %d     itr -> %d\n",i,itr);
            // printf("Aryan Dubey");
            if(tester == 1)
                printf("%s\n",path);
            else
            {
                if(dl == NULL)
                    printf("Wrong Directory\n");
                else
                    printf("Wrong File Name\n");
            }
            // dup2(org,STDOUT_FILENO);
        }
        else if(flg1 == 2)
        {
            int fd = open(fin1[itr+1], O_CREAT | O_RDWR | O_APPEND, 0644);
            int org;
            org = dup(0);
            dup2(fd,STDOUT_FILENO);
            // if(<0)
            // {
            //     printf("Failed to duplicate file descriptor\n");
            // }
            close(fd);
            // printf("i -> %d     itr -> %d\n",i,itr);
            // printf("Aryan Dubey");
            if(tester == 1)
                printf("%s\n",path);
            else
            {
                if(dl == NULL)
                    printf("Wrong Directory\n");
                else
                    printf("Wrong File Name\n");
            }
            dup2(org,STDOUT_FILENO);
        }
        else if(flg1 == -1)
        {
            if(tester == 1)
                printf("%s\n",path);
            else
            {
                if(dl == NULL)
                    printf("Wrong Directory\n");
                else
                    printf("Wrong File Name\n");
            }
        }
    }
    else
    {
        if(flg1 == 0)
        {
            int org = dup(1);
            int fd = open(fin1[itr+1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
            dup2(fd,STDOUT_FILENO);
            close(fd);
            if(k)
                printf("%s:\n",path);
            int val = scandir(path, &namelist, NULL, alphasort);
            for(int i = 0; i < val; i++)
	        {
	        	if (flg && namelist[i]->d_name[0] == '.')
	        		continue;
	        	printf("%s\n", namelist[i]->d_name);
	        }
            dup2(org,STDOUT_FILENO);
        }
        else if(flg1 == 1)
        {
            // printf("hi\n");
            int org = dup(0);
            int fd = open(fin1[itr+1], O_RDONLY);
            dup2(fd,STDIN_FILENO);
            close(fd);
            if(fd<0)
            {
                printf("File does not exist\n");
                return;
            }
            if(k)
                printf("%s:\n",path);
            int val = scandir(path, &namelist, NULL, alphasort);
            for(int i = 0; i < val; i++)
	        {
	        	if (flg && namelist[i]->d_name[0] == '.')
	        		continue;
	        	printf("%s\n", namelist[i]->d_name);
	        }
            dup2(org,STDIN_FILENO);
        }
        else if(flg1 == 2)
        {
            int fd = open(fin1[itr+1], O_CREAT | O_RDWR | O_APPEND, 0644);
            int org = dup(1);
            dup2(fd,STDOUT_FILENO);
            close(fd);
            if(k)
                printf("%s:\n",path);
            int val = scandir(path, &namelist, NULL, alphasort);
            for(int i = 0; i < val; i++)
	        {
	        	if (flg && namelist[i]->d_name[0] == '.')
	        		continue;
	        	printf("%s\n", namelist[i]->d_name);
	        }
            dup2(org,STDOUT_FILENO);
        }
        else if(flg1 == -1)
        {
            if(k)
                printf("%s:\n",path);
            int val = scandir(path, &namelist, NULL, alphasort);
            for(int i = 0; i < val; i++)
	        {
	        	if (flg && namelist[i]->d_name[0] == '.')
	        		continue;
	        	printf("%s\n", namelist[i]->d_name);
	        }
        }
    }
    
}