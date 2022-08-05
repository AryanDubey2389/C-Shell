#include "prompt.h"
#include "headers.h"
int fin1_len3(char** fin1)
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
void rev_l(char* str)
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
void listing_l(char* path, int flg,int k,char** fin1)
{
    char cuur[1000], afg[1000];
    getcwd(cuur,1000);
    struct dirent *direc, *direc_temp;
    int len_fin1 = fin1_len3(fin1);  
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
    int temp_val = 0;
    if(strcmp(path,">") == 0 || (strcmp(path,"<") == 0 || strcmp(path,">>") == 0))
    {
        temp_val = 1;
        path = ".";
    }
    DIR* dh = opendir(path);
    DIR* dr = opendir(path);
    if(dh == NULL)
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
        rev_l(split2);
        rev_l(split1);
        // printf("split2 -> %s\n",split2);
        // printf("split1 -> %s\n",split1);

        if(strlen(split1) == 0)
            strcpy(split1,".");
        DIR* dl = opendir(split1);
        // printf("dl -> %d\n",dl);
        struct dirent **namelist1;
        int tester = 0;
        while ((direc = readdir(dl)) != NULL)
        {
            // printf("dname -> %s\n",direc->d_name);
            if(strcmp(direc->d_name,split2) == 0)
                tester = 1;
        }
        if(flg1 == 0)
        {
            // printf("fin -> %s\n",fin1[itr+1]);
            int fd = open(fin1[itr+1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
            int org;
            org = dup(1);
            dup2(fd,STDOUT_FILENO);
            // if(<0)
            // {
            //     printf("Failed to duplicate file descriptor\n");
            // }
            
            close(fd);
            if(tester == 1)
            {
                char exct_time[1000] = "";
                struct stat fs;
                int val1 = stat(path,&fs);
                int sz = fs.st_size;
                int dir_flg = S_ISDIR(fs.st_mode);
                int hard_links = fs.st_nlink;
                strftime(exct_time, 20, "%b %d %H:%M ", localtime(&(fs.st_mtime)));
                printf((dir_flg) ? "d" : "-");
	        	printf((fs.st_mode & S_IRUSR) ? "r" : "-");
	        	printf((fs.st_mode & S_IWUSR) ? "w" : "-");
	        	printf((fs.st_mode & S_IXUSR) ? "x" : "-");
	        	printf((fs.st_mode & S_IRGRP) ? "r" : "-");
	        	printf((fs.st_mode & S_IWGRP) ? "w" : "-");
	        	printf((fs.st_mode & S_IXGRP) ? "x" : "-");
	        	printf((fs.st_mode & S_IROTH) ? "r" : "-");
	        	printf((fs.st_mode & S_IWOTH) ? "w" : "-");
	        	printf((fs.st_mode & S_IXOTH) ? "x" : "-");
                printf(" %3d %5s %5s",hard_links,getpwuid(fs.st_uid)->pw_name,getpwuid(fs.st_gid)->pw_name);
                printf(" %5d %5s %s",sz,exct_time,split2);
                printf("\n");
                dup2(org,STDOUT_FILENO);
                // printf("%s\n",path);
            }
            else
            {
                dup2(org,STDOUT_FILENO);
                if(dl == NULL)
                    printf("Wrong Directory\n");
                else
                    printf("Wrong File Name\n");
            }

        }
        else if(flg1 == 1)
        {
            int fd = open(fin1[itr+1], O_RDONLY);
            int org;
            org = dup(0);
            dup2(fd,STDIN_FILENO);
            close(fd);
            if(fd < 0)
            {
                printf("File does not exist\n");
                return;
            }
            if(tester == 1)
            {
                char exct_time[1000] = "";
                struct stat fs;
                int val1 = stat(path,&fs);
                int sz = fs.st_size;
                int dir_flg = S_ISDIR(fs.st_mode);
                int hard_links = fs.st_nlink;
                strftime(exct_time, 20, "%b %d %H:%M ", localtime(&(fs.st_mtime)));
                printf((dir_flg) ? "d" : "-");
	        	printf((fs.st_mode & S_IRUSR) ? "r" : "-");
	        	printf((fs.st_mode & S_IWUSR) ? "w" : "-");
	        	printf((fs.st_mode & S_IXUSR) ? "x" : "-");
	        	printf((fs.st_mode & S_IRGRP) ? "r" : "-");
	        	printf((fs.st_mode & S_IWGRP) ? "w" : "-");
	        	printf((fs.st_mode & S_IXGRP) ? "x" : "-");
	        	printf((fs.st_mode & S_IROTH) ? "r" : "-");
	        	printf((fs.st_mode & S_IWOTH) ? "w" : "-");
	        	printf((fs.st_mode & S_IXOTH) ? "x" : "-");
                printf(" %3d %5s %5s",hard_links,getpwuid(fs.st_uid)->pw_name,getpwuid(fs.st_gid)->pw_name);
                printf(" %5d %5s %s",sz,exct_time,split2);
                printf("\n");
                // printf("%s\n",path);
            }
            else
            {
                if(dl == NULL)
                    printf("Wrong Directory\n");
                else
                    printf("Wrong File Name\n");
            }
            dup2(org,STDIN_FILENO);
        }
        else if(flg1 == 2)
        {
            int fd = open(fin1[itr+1], O_CREAT | O_RDWR | O_APPEND, 0644);
            int org;
            org = dup(1);
            dup2(fd,STDOUT_FILENO);
            // if(<0)
            // {
            //     printf("Failed to duplicate file descriptor\n");
            // }
            
            close(fd);
            if(tester == 1)
            {
                char exct_time[1000] = "";
                struct stat fs;
                int val1 = stat(path,&fs);
                int sz = fs.st_size;
                int dir_flg = S_ISDIR(fs.st_mode);
                int hard_links = fs.st_nlink;
                strftime(exct_time, 20, "%b %d %H:%M ", localtime(&(fs.st_mtime)));
                printf((dir_flg) ? "d" : "-");
	        	printf((fs.st_mode & S_IRUSR) ? "r" : "-");
	        	printf((fs.st_mode & S_IWUSR) ? "w" : "-");
	        	printf((fs.st_mode & S_IXUSR) ? "x" : "-");
	        	printf((fs.st_mode & S_IRGRP) ? "r" : "-");
	        	printf((fs.st_mode & S_IWGRP) ? "w" : "-");
	        	printf((fs.st_mode & S_IXGRP) ? "x" : "-");
	        	printf((fs.st_mode & S_IROTH) ? "r" : "-");
	        	printf((fs.st_mode & S_IWOTH) ? "w" : "-");
	        	printf((fs.st_mode & S_IXOTH) ? "x" : "-");
                printf(" %3d %5s %5s",hard_links,getpwuid(fs.st_uid)->pw_name,getpwuid(fs.st_gid)->pw_name);
                printf(" %5d %5s %s",sz,exct_time,split2);
                printf("\n");
                dup2(org,STDOUT_FILENO);
                // printf("%s\n",path);
            }
            else
            {
                dup2(org,STDOUT_FILENO);
                if(dl == NULL)
                    printf("Wrong Directory\n");
                else
                    printf("Wrong File Name\n");
            }

        }
        else if(flg1 == -1)
        {
            if(tester == 1)
            {
                char exct_time[1000] = "";
                struct stat fs;
                int val1 = stat(path,&fs);
                int sz = fs.st_size;
                int dir_flg = S_ISDIR(fs.st_mode);
                int hard_links = fs.st_nlink;
                strftime(exct_time, 20, "%b %d %H:%M ", localtime(&(fs.st_mtime)));
                printf((dir_flg) ? "d" : "-");
	        	printf((fs.st_mode & S_IRUSR) ? "r" : "-");
	        	printf((fs.st_mode & S_IWUSR) ? "w" : "-");
	        	printf((fs.st_mode & S_IXUSR) ? "x" : "-");
	        	printf((fs.st_mode & S_IRGRP) ? "r" : "-");
	        	printf((fs.st_mode & S_IWGRP) ? "w" : "-");
	        	printf((fs.st_mode & S_IXGRP) ? "x" : "-");
	        	printf((fs.st_mode & S_IROTH) ? "r" : "-");
	        	printf((fs.st_mode & S_IWOTH) ? "w" : "-");
	        	printf((fs.st_mode & S_IXOTH) ? "x" : "-");
                printf(" %3d %5s %5s",hard_links,getpwuid(fs.st_uid)->pw_name,getpwuid(fs.st_gid)->pw_name);
                printf(" %5d %5s %s",sz,exct_time,split2);
                printf("\n");
                // printf("%s\n",path);
            }
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
        struct stat fs;
        int val = stat(path,&fs),size = 0;
        if(flg1 == 0)
        {
            // printf("fin -> %s\n",fin1[itr+1]);
            // prntf("%s:\n",path);
            int fd = open(fin1[itr+1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
            chdir(path);
            int org;
            org = dup(1);
            dup2(fd,STDOUT_FILENO);
            // // if(<0)
            // // {
            // //     printf("Failed to duplicate file descriptor\n");
            // // }
            close(fd);
            if(k)
                printf("%s:\n",path);
            while((direc_temp = readdir(dr)) != NULL)
            {
                struct stat fs1;
                char newpath[1000] = "./";
                if (flg && direc_temp->d_name[0] == '.')
	        		continue;
                strcat(newpath,direc_temp->d_name);
                int val1 = stat(newpath,&fs1);
                size += fs1.st_blocks;

            }
            printf("total %d\n",size/2);
            while ((direc = readdir(dh)) != NULL)
            {
                char newpath[1000] = "./",exct_time[1000] = "";
                if (flg && direc->d_name[0] == '.')
	        		continue;
                // printf("name -> %s\n",direc->d_name);
                strcat(newpath,direc->d_name);
                // printf("newpath -> %s\n",newpath);
                struct stat fs;
                int val1 = stat(newpath,&fs);
                int dir_flg = S_ISDIR(fs.st_mode);
                int sz = fs.st_size;
                int hard_links = fs.st_nlink;
                strftime(exct_time, 20, "%b %d %H:%M ", localtime(&(fs.st_mtime)));
                printf((dir_flg) ? "d" : "-");
	        	printf((fs.st_mode & S_IRUSR) ? "r" : "-");
	        	printf((fs.st_mode & S_IWUSR) ? "w" : "-");
	        	printf((fs.st_mode & S_IXUSR) ? "x" : "-");
	        	printf((fs.st_mode & S_IRGRP) ? "r" : "-");
	        	printf((fs.st_mode & S_IWGRP) ? "w" : "-");
	        	printf((fs.st_mode & S_IXGRP) ? "x" : "-");
	        	printf((fs.st_mode & S_IROTH) ? "r" : "-");
	        	printf((fs.st_mode & S_IWOTH) ? "w" : "-");
	        	printf((fs.st_mode & S_IXOTH) ? "x" : "-");
                printf(" %3d %5s %5s",hard_links,getpwuid(fs.st_uid)->pw_name,getpwuid(fs.st_gid)->pw_name);
                printf(" %5d %5s %s",sz,exct_time,direc->d_name);
                printf("\n");
            }
            dup2(org,STDOUT_FILENO);
        }
        else if(flg1 == 1)
        {
            int org;
            org = dup(0);
            int fd = open(fin1[itr+1], O_RDONLY);
            dup2(fd,STDIN_FILENO);
            close(fd);
            if(fd<0)
            {
                printf("File does not exist\n");
                return;
            }
            chdir(path);
            if(k)
                printf("%s:\n",path);
            while((direc_temp = readdir(dr)) != NULL)
            {
                struct stat fs1;
                char newpath[1000] = "./";
                if (flg && direc_temp->d_name[0] == '.')
	        		continue;
                strcat(newpath,direc_temp->d_name);
                int val1 = stat(newpath,&fs1);
                size += fs1.st_blocks;

            }
            printf("total %d\n",size/2);
            while ((direc = readdir(dh)) != NULL)
            {
                char newpath[1000] = "./",exct_time[1000] = "";
                if (flg && direc->d_name[0] == '.')
	        		continue;
                // printf("name -> %s\n",direc->d_name);
                strcat(newpath,direc->d_name);
                // printf("newpath -> %s\n",newpath);
                struct stat fs;
                int val1 = stat(newpath,&fs);
                int dir_flg = S_ISDIR(fs.st_mode);
                int sz = fs.st_size;
                int hard_links = fs.st_nlink;
                strftime(exct_time, 20, "%b %d %H:%M ", localtime(&(fs.st_mtime)));
                printf((dir_flg) ? "d" : "-");
	        	printf((fs.st_mode & S_IRUSR) ? "r" : "-");
	        	printf((fs.st_mode & S_IWUSR) ? "w" : "-");
	        	printf((fs.st_mode & S_IXUSR) ? "x" : "-");
	        	printf((fs.st_mode & S_IRGRP) ? "r" : "-");
	        	printf((fs.st_mode & S_IWGRP) ? "w" : "-");
	        	printf((fs.st_mode & S_IXGRP) ? "x" : "-");
	        	printf((fs.st_mode & S_IROTH) ? "r" : "-");
	        	printf((fs.st_mode & S_IWOTH) ? "w" : "-");
	        	printf((fs.st_mode & S_IXOTH) ? "x" : "-");
                printf(" %3d %5s %5s",hard_links,getpwuid(fs.st_uid)->pw_name,getpwuid(fs.st_gid)->pw_name);
                printf(" %5d %5s %s",sz,exct_time,direc->d_name);
                printf("\n");
            }
            dup2(org,STDIN_FILENO);
        }
        else if(flg1 == 2)
        {
            int fd = open(fin1[itr+1], O_CREAT | O_RDWR | O_APPEND, 0644);
            chdir(path);
            int org;
            org = dup(1);
            dup2(fd,STDOUT_FILENO);
            // // if(<0)
            // // {
            // //     printf("Failed to duplicate file descriptor\n");
            // // }
            close(fd);
            if(k)
                printf("%s:\n",path);
            while((direc_temp = readdir(dr)) != NULL)
            {
                struct stat fs1;
                char newpath[1000] = "./";
                if (flg && direc_temp->d_name[0] == '.')
	        		continue;
                strcat(newpath,direc_temp->d_name);
                int val1 = stat(newpath,&fs1);
                size += fs1.st_blocks;

            }
            printf("total %d\n",size/2);
            while ((direc = readdir(dh)) != NULL)
            {
                char newpath[1000] = "./",exct_time[1000] = "";
                if (flg && direc->d_name[0] == '.')
	        		continue;
                // printf("name -> %s\n",direc->d_name);
                strcat(newpath,direc->d_name);
                // printf("newpath -> %s\n",newpath);
                struct stat fs;
                int val1 = stat(newpath,&fs);
                int dir_flg = S_ISDIR(fs.st_mode);
                int sz = fs.st_size;
                int hard_links = fs.st_nlink;
                strftime(exct_time, 20, "%b %d %H:%M ", localtime(&(fs.st_mtime)));
                printf((dir_flg) ? "d" : "-");
	        	printf((fs.st_mode & S_IRUSR) ? "r" : "-");
	        	printf((fs.st_mode & S_IWUSR) ? "w" : "-");
	        	printf((fs.st_mode & S_IXUSR) ? "x" : "-");
	        	printf((fs.st_mode & S_IRGRP) ? "r" : "-");
	        	printf((fs.st_mode & S_IWGRP) ? "w" : "-");
	        	printf((fs.st_mode & S_IXGRP) ? "x" : "-");
	        	printf((fs.st_mode & S_IROTH) ? "r" : "-");
	        	printf((fs.st_mode & S_IWOTH) ? "w" : "-");
	        	printf((fs.st_mode & S_IXOTH) ? "x" : "-");
                printf(" %3d %5s %5s",hard_links,getpwuid(fs.st_uid)->pw_name,getpwuid(fs.st_gid)->pw_name);
                printf(" %5d %5s %s",sz,exct_time,direc->d_name);
                printf("\n");
            }
            dup2(org,STDOUT_FILENO);
        }
        else if(flg1 == -1)
        {
            chdir(path);
            if(k)
                printf("%s:\n",path);
            while((direc_temp = readdir(dr)) != NULL)
            {
                struct stat fs1;
                char newpath[1000] = "./";
                if (flg && direc_temp->d_name[0] == '.')
	        		continue;
                strcat(newpath,direc_temp->d_name);
                int val1 = stat(newpath,&fs1);
                size += fs1.st_blocks;

            }
            printf("total %d\n",size/2);
            while ((direc = readdir(dh)) != NULL)
            {
                char newpath[1000] = "./",exct_time[1000] = "";
                if (flg && direc->d_name[0] == '.')
	        		continue;
                // printf("name -> %s\n",direc->d_name);
                strcat(newpath,direc->d_name);
                // printf("newpath -> %s\n",newpath);
                struct stat fs;
                int val1 = stat(newpath,&fs);
                int dir_flg = S_ISDIR(fs.st_mode);
                int sz = fs.st_size;
                int hard_links = fs.st_nlink;
                strftime(exct_time, 20, "%b %d %H:%M ", localtime(&(fs.st_mtime)));
                printf((dir_flg) ? "d" : "-");
	        	printf((fs.st_mode & S_IRUSR) ? "r" : "-");
	        	printf((fs.st_mode & S_IWUSR) ? "w" : "-");
	        	printf((fs.st_mode & S_IXUSR) ? "x" : "-");
	        	printf((fs.st_mode & S_IRGRP) ? "r" : "-");
	        	printf((fs.st_mode & S_IWGRP) ? "w" : "-");
	        	printf((fs.st_mode & S_IXGRP) ? "x" : "-");
	        	printf((fs.st_mode & S_IROTH) ? "r" : "-");
	        	printf((fs.st_mode & S_IWOTH) ? "w" : "-");
	        	printf((fs.st_mode & S_IXOTH) ? "x" : "-");
                printf(" %3d %5s %5s",hard_links,getpwuid(fs.st_uid)->pw_name,getpwuid(fs.st_gid)->pw_name);
                printf(" %5d %5s %s",sz,exct_time,direc->d_name);
                printf("\n");
            }
        }
    }
    chdir(cuur);
}